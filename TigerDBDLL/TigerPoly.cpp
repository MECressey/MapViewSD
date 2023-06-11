#include "pch.h"
#include <assert.h>

#include "tigerdb.hpp"

TigerDB::Polygon::Polygon(void) : GeoDB::SpatialObj(DB_TIGER_POLY, AREA)
{
	this->code = 0;
	this->area = 0.0;
	this->poly_epl.init();
	this->SpatialObj::Init();
}

TigerDB::Polygon::~Polygon(void)
{
}

unsigned TigerDB::Polygon::DiskSize(void)
{
	unsigned size = this->SpatialObj::DiskSize();

	size += sizeof(this->code);
	size += sizeof(this->area);
	size += this->poly_epl.size();
	size += sizeof(Iv2);  // Need to store MBR because it is expensive to calculate it

	return(size);
}

void TigerDB::Polygon::Compress(void* obj)
{
	char* to = (char*)obj;
	//unsigned char buffer[40];

	this->SpatialObj::Compress(to);
	to += this->SpatialObj::DiskSize();

	//buffer[0] = this->code;

	::memcpy(to, &this->code, 1);
	to += 1;

	::memcpy(to, &this->area, sizeof(this->area));
	to += sizeof(this->area);
	to = this->poly_epl.store(to);

	// Compress MBR
	memcpy(to, &this->mbr.x.low, sizeof(this->mbr.x.low));
	to += sizeof(this->mbr.x.low);
	memcpy(to, &this->mbr.x.high, sizeof(this->mbr.x.high));
	to += sizeof(this->mbr.x.high);
	memcpy(to, &this->mbr.y.low, sizeof(this->mbr.y.low));
	to += sizeof(this->mbr.y.low);
	memcpy(to, &this->mbr.y.high, sizeof(this->mbr.y.high));
	to += sizeof(this->mbr.y.high);
}

void TigerDB::Polygon::Decompress(void* obj, int size)
{
	char* from = (char*)obj;

	this->SpatialObj::Decompress(from, size);
	from += this->SpatialObj::DiskSize();

	this->code = *from++;
	this->area = *(double *)from;
	from += sizeof(this->area);
	size -= 9;

	from = this->poly_epl.fetch(from);

	// MBR
	memcpy(&this->mbr.x.low, from, sizeof(this->mbr.x.low));
	from += sizeof(this->mbr.x.low);
	memcpy(&this->mbr.x.high, from, sizeof(this->mbr.x.high));
	from += sizeof(this->mbr.x.high);
	memcpy(&this->mbr.y.low, from, sizeof(this->mbr.y.low));
	from += sizeof(this->mbr.y.low);
	memcpy(&this->mbr.y.high, from, sizeof(this->mbr.y.high));
	from += sizeof(this->mbr.y.high);
}


int TigerDB::Polygon::Level(int* maxl)
{
	*maxl = 13;
	return(1);
}

int TigerDB::Polygon::AddEdge(ObjHandle& eh, unsigned char dir)
{
	TigerDB* db = (TigerDB*)this->database();
	int err;

	ObjHandle epl;
	if ((err = db->NewObject(DB_TIGER_EdgePolyLink, epl/*, id*/)) != 0)
		return err;

	EdgePolyLink* edgePolyLink = (EdgePolyLink*)epl.Lock();
	edgePolyLink->SetCode(TigerDB::HYDRO_PerennialLakeOrPond);
	edgePolyLink->SetDir(dir);
	edgePolyLink->write();

	err = POLY_EDGE.insertAfter(edgePolyLink, this);

	Chain* edge = (Chain*)eh.Lock();
	err = EDGE_POLY.insertAfter(edgePolyLink, edge);
	eh.Unlock();
	epl.Unlock();

	return 0;
}

int TigerDB::Polygon::GetPts(ObjHandle &poly, XY_t pts[])
{
	ObjHandle epl = poly;
	int err;
	int count = 0;
	while ((err = POLY_EDGE.getNext(epl)) == 0)
	{
		EdgePolyLink* edgePolyLink = (EdgePolyLink*)epl.Lock();
		unsigned char dir = edgePolyLink->GetDir();
		epl.Unlock();

		ObjHandle eo = epl;
		err = EDGE_POLY.getNext(eo);
		Chain *edge = (Chain*)eo.Lock();
		int nPts = edge->GetNumPts();
		XY_t sPt, ePt;
		edge->GetNodes(&sPt, &ePt);
		edge->Get(&pts[count]);
		eo.Unlock();
/**/		if (dir != 1)  // Reverse the points
	  {
			int startPos = count;
			int endPos = count + nPts - 1;
			while (startPos < endPos)
			{
				XY_t temp = pts[startPos];
				pts[startPos] = pts[endPos];
				pts[endPos] = temp;
				startPos++;
				endPos--;
			}
		}

		count += nPts - 1;
/**/
/*
		bool equals;
		if (count > 0)
		{
			if (dir)
				equals = pts[count] == sPt;
			else
				equals = pts[count] == ePt;
			assert(equals);
		}
		if (dir)
		{
			pts[count++] = sPt;
			pts[count] = ePt;
		}
		else
		{
			pts[count++] = ePt;
			pts[count] = sPt;
		}
*/
	}
	return ++count;
}

TigerDB::EdgePolyLink::EdgePolyLink(void) : DbObject(DB_TIGER_EdgePolyLink)
{
	this->code = 0;
	this->dir = 0;
	this->poly_edge.init();
	this->edge_poly.init();
}

TigerDB::EdgePolyLink::~EdgePolyLink(void)
{
}

unsigned TigerDB::EdgePolyLink::DiskSize(void)
{
	unsigned size = this->DbObject::size();

	size += sizeof(this->code);
	size += sizeof(this->dir);
	size += this->poly_edge.size();
	size += this->edge_poly.size();

	return(size);
}

void TigerDB::EdgePolyLink::Compress(void* obj)
{
	char* to = (char*)obj;
	unsigned char buffer[40];

	to = this->DbObject::store(to);

	buffer[0] = this->code;
	buffer[1] = this->dir;

	::memcpy(to, buffer, 2);
	to += 2;

	to = this->poly_edge.store(to);
	to = this->edge_poly.store(to);
}

void TigerDB::EdgePolyLink::Decompress(void* obj, int size)
{
	char* from = (char*)obj;

	from = this->DbObject::fetch(from);

	this->code = *from++;
	this->dir = *from++;

	from = this->poly_edge.fetch(from);
	from = this->edge_poly.fetch(from);
}

SetRelation POLY_EDGE(
	DB_TIGER_POLY, offsetof(TigerDB::Polygon, poly_epl),
	SetSllOwner::description,
	DB_TIGER_EdgePolyLink, offsetof(TigerDB::EdgePolyLink, poly_edge),
	SetSllMember::description);

SetRelation EDGE_POLY(
	DB_TIGER_LINE, offsetof(TigerDB::Chain, epl_poly),
	SetSllOwner::description,
	DB_TIGER_EdgePolyLink, offsetof(TigerDB::EdgePolyLink, edge_poly),
	SetSllMember::description);