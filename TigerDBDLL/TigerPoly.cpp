#include "pch.h"
#include <assert.h>

#include "tigerdb.hpp"

TigerDB::Polygon::Polygon(void) : GeoDB::Poly/*SpatialObj*/(/*DB_TIGER_POLY, AREA*/)
{
	//this->code = 0;
	//this->area = 0.0;
	//this->poly_epl.init();
	this->GeoDB::Poly::Init();
	memset(this->name, '\0', sizeof(this->name));
}

TigerDB::Polygon::~Polygon(void)
{
}

unsigned TigerDB::Polygon::DiskSize(void)
{
	unsigned size = this->GeoDB::Poly::DiskSize();
	/*
	size += sizeof(this->code);
	size += sizeof(this->area);
	size += this->poly_epl.size();
	size += sizeof(Iv2);  // Need to store MBR because it is expensive to calculate it
	*/
	size += sizeof(this->name);

	return(size);
}

void TigerDB::Polygon::Compress(void* obj)
{
	char* to = (char*)obj;
	//unsigned char buffer[40];

	this->GeoDB::Poly::Compress(to);
	to += this->GeoDB::Poly::DiskSize();

	memcpy(to, this->name, sizeof(this->name));
	//buffer[0] = this->code;
	/*
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
	*/
}

void TigerDB::Polygon::Decompress(void* obj, int size)
{
	char* from = (char*)obj;

	this->GeoDB::Poly::Decompress(from, size);
	from += this->GeoDB::Poly::DiskSize();

	memcpy(this->name, from, sizeof(this->name));
/*
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
	*/
}

void TigerDB::Polygon::SetName(std::string name)
{
	size_t len = name.length();

	if (len > sizeof(this->name))
		len = sizeof(this->name) - 1;

	::strncpy_s(this->name, name.c_str(), len);
	this->name[len] = '\0';

}

std::string TigerDB::Polygon::GetName() const
{
	std::string str(this->name);

	return str;
}

/*
int TigerDB::Polygon::Level(int* maxl)
{
	*maxl = 10;
	return(1);
}

int TigerDB::Polygon::AddEdge(ObjHandle& eh, unsigned char dir)
{
	TigerDB* db = (TigerDB*)this->database();
	int err;

	ObjHandle epl;
	if ((err = db->NewObject(DB_TIGER_EdgePolyLink, epl)) != 0)
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
*/
#ifdef SAVE_FOR_NOW
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

		ObjHandle eo/* = epl*/;
		//err = EDGE_POLY.getNext(eo);
		err = EDGE_POLY.getOwner(epl, eo);
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

int TigerDB::Polygon::matchPoly(ObjHandle &poly, std::vector<TigerDB::DirLineId>& polyLines, int start, int end)
{
	int err;
	ObjHandle epl = poly;
	int total = 0,
		nFound = 0;
	while ((err = POLY_EDGE.getNext(epl)) == 0)
	{
		ObjHandle eo;
		err = EDGE_POLY.getOwner(epl, eo);
		TigerDB::Chain* edge = (TigerDB::Chain*)eo.Lock();
		long tlid = edge->userId/*GetTLID()*/;
		eo.Unlock();

		for (int i = end; --i >= start; )
		{
			DirLineId& lineId = polyLines[i];
			if (tlid == lineId.tlid)
			{
				nFound++;
				break;
			}
		}
		total++;
	}
	if (nFound == 0)
		return 0;
	double percent = (double)nFound / total;

	return (int)(percent * 100 + 0.5);
	//	return false;
}
#endif
/*
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
	*/