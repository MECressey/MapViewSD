//
//	TigerLine.cpp - implementation for the TigerDB::Chain class using the NodeEdgePoly class library.
//  Copyright(C) 2024 Michael E. Cressey
//
//	This program is free software : you can redistribute it and /or modify it under the terms of the
//	GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
//	implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along with this program.
//  If not, see https://www.gnu.org/licenses/
//
#include "pch.h"
#include <string.h>
#include <assert.h>

#include "tigerdb.hpp"
#include "tgrtypes.h"
#include "distname.h"
#include "tstring.h"
#include "HASHTABL.HPP"

void TigerDB::Chain::GetName( TigerDB::Name *out, int index ) const
{
  TigerDB *db = (TigerDB *)((DbObject *)this)->database();
	FieldDef *def;

	if( this->names[ index ].prefixCode == 0 ||
			(def = TigerGetPrefix(this->names[ index ].prefixCode)) == 0)
		out->prefix[ 0 ] = '\0';
	else
	{
		::strcpy/*_tcscpy_s*/(out->prefix, TString(def->abbrev));
	}

	if( this->names[ index ].suffixCode == 0 )
		out->suffix[ 0 ] = '\0';
	else
	{
		out->suffix[ 0 ] = '\0';
	}

	db->nameById->idParam = this->names[ index ].nameId;
	db->nameById->Requery();
	if( db->nameById->IsEOF() )
	{
		out->name[ 0 ] = _T('\0');
	}
	else
	{
		::strcpy/*_tcscpy_s*/(out->name, TString(db->nameById->m_name));
		while (! db->nameById->IsEOF())
			db->nameById->MoveNext();
	}

	if( this->names[ index ].typeCode == 0 ||
			( def = TigerGetType(	this->names[ index ].typeCode	) ) == 0 )
		out->type[ 0 ] = '\0';
	else
	{
		::strcpy/*_tcscpy_s*/(out->type, TString(def->abbrev));
	}
}

TigerDB::Chain::Chain( void ) : GeoDB::Edge()
{
  this->nNames = 0;
}

TigerDB::Chain::~Chain( void )
{
}

void TigerDB::Chain::Init(void)
{
	this->GeoDB::Edge::Init();
	this->nNames = 0;
}

void TigerDB::Chain::Compress( void *obj )
{
  char *to = (char *)obj;
	unsigned char buffer[40];

	this->Edge::Compress( to );
	to += this->Edge::DiskSize();

	*to = this->nNames;
  to += 1;

	for( int i = 0; i < this->nNames;  i++ )
	{
		::memcpy( buffer, &this->names[i].nameId, sizeof(unsigned short));
		buffer[2] = this->names[ i ].typeCode;

		buffer[3] = (this->names[ i ].prefixCode << 4) | 	(((1 << 4) - 1) & this->names[ i ].suffixCode);

	  ::memcpy(to, buffer, 4);
	  to += 4;
	}
}

void TigerDB::Chain::Decompress( void *obj, int size )
{
  char *from = (char *)obj;
  
	this->Edge::Decompress( from, size );

	unsigned diskSize = this->Edge::DiskSize();
	from += diskSize;
	size -= diskSize;

	//this->code = *from++;
	this->nNames = *from++;
  size -= 1/*2*/;

	for( int i = 0; i < this->nNames;  i++ )
	{
		::memcpy(&this->names[i].nameId, from, sizeof(unsigned short));
		from += sizeof(unsigned short);

		this->names[ i ].typeCode = *from++;

		this->names[ i ].prefixCode = *from++;
		this->names[ i ].suffixCode = ((1 << 4) - 1) & this->names[ i ].prefixCode;
		this->names[ i ].prefixCode = this->names[ i ].prefixCode >> 4;

		size -= 4;
	}
}

unsigned TigerDB::Chain::DiskSize( void )
{
  unsigned size = this->Edge::DiskSize();

	size += 2 + (this->nNames * 4);
	return( size );
}

void TigerDB::Chain::SetName( TigerDB::Name lineNames[], int count )
{
  TigerDB *db = (TigerDB *)((DbObject *)this)->database();

	if( count > (sizeof(names) / sizeof(names[0])))		// Ignore any names larger than the list
		count = (sizeof(names) / sizeof(names[0]));

	this->nNames = count;
	for( int i = 0; i < count; i++ )
	{
		int code;

		db->names->nameParam = lineNames[ i ].name;
		db->names->Requery();
		if( db->names->IsEOF() )
		{
			this->names[ i ].nameId = 0;
		}
		else
		{
			names[ i ].nameId = (unsigned short)db->names->m_id;
			while (! db->names->IsEOF())
				db->names->MoveNext();
		}

		if( ::strlen( lineNames[ i ].type ) == 0 ||
				( code = TigerGetTypeCode( TString(lineNames[ i ].type) ) ) < 0 )
			this->names[ i ].typeCode = 0;
		else
		{
			this->names[ i ].typeCode = code;
		}

		if( ::strlen/*_tcslen*/(lineNames[i].prefix) == 0 ||
				( code = TigerGetPrefixCode( TString(lineNames[ i ].prefix) ) ) < 0 )
			names[ i ].prefixCode = 0;
		else
		{
			names[ i ].prefixCode = code;
		}

		names[ i ].suffixCode = 0;
	}
}

int TigerDB::Chain::is_equal(DbObject *dbo)
{
	return this->dbAddress() == dbo->dbAddress();
}

long int TigerDB::Chain::hashKey(int nBits)
{
	return HashTable::HashDK(nBits, this->userId/*GetTLID()*/);
}

