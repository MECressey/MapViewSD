//#include "stdafx.h"
#include "pch.h"
#include <string.h>

#include "tigerdb.hpp"
#include "tgrtypes.h"
#include "distname.h"
#include "tstring.h"

void TigerDB::Chain::GetName( TigerDB::Name *out, int index ) const
{
  TigerDB *db = (TigerDB *)((DbObject *)this)->database();
//	const TigerDB::Chain::TName &name = this->names[ index ];
	FieldDef *def;

//						long nameId;	do later
	if( this->names[ index ].prefixCode == 0 ||
			( def = TigerGetPrefix(	this->names[ index ].prefixCode	) ) == 0 )
		out->prefix[ 0 ] = '\0';
	else
	{
		::strcpy/*_tcscpy_s*/(out->prefix, TString(def->abbrev));
	}

	if( this->names[ index ].suffixCode == 0 )
		out->suffix[ 0 ] = '\0';
	else
	{
		out->suffix[ 0 ] = '\0';		// do later
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

TigerDB::Chain::Chain( void ) : GeoDB::Line( DB_TIGER_LINE )
{
  this->code = 0;
  this->nNames = 0;
	this->tlid = 0;
	this->epl_poly.init();
}

TigerDB::Chain::~Chain( void )
{
}

void TigerDB::Chain::Compress( void *obj )
{
  char *to = (char *)obj;
	unsigned char buffer[40];

	this->Line::Compress( to );
	to += this->Line::DiskSize();

	buffer[ 0 ] = this->code;
	buffer[ 1 ] = this->nNames;

  ::memcpy(to, buffer, 2);
  to += 2;

	for( int i = 0; i < this->nNames;  i++ )
	{
		unsigned long val = ((1L << 24 ) - 1) & this->names[ i ].nameId;

		::memcpy( buffer, &val, 3 );
		buffer[ 3 ] = this->names[ i ].typeCode;

		buffer[ 4 ] = (this->names[ i ].prefixCode << 4) | 
				(((1 << 4) - 1) & this->names[ i ].suffixCode);

	  ::memcpy(to, buffer, 5 );
	  to += 5;
	}
	::memcpy(to, &this->tlid, sizeof(long));	// TLID
	to += sizeof(long);
	to = this->epl_poly.store(to);
}

void TigerDB::Chain::Decompress( void *obj, int size )
{
  char *from = (char *)obj;
  
	this->Line::Decompress( from, size );
	from += this->Line::DiskSize();

	this->code = *from++;
	this->nNames = *from++;
  size -= 2;

	for( int i = 0; i < this->nNames;  i++ )
	{
		unsigned long val;

		::memcpy( &val, from, 3 );
		this->names[ i ].nameId = ((1L << 24 ) - 1) & val;
		from += 3;

		this->names[ i ].typeCode = *from++;

		this->names[ i ].prefixCode = *from++;
		this->names[ i ].suffixCode = ((1 << 4) - 1) & this->names[ i ].prefixCode;
		this->names[ i ].prefixCode = this->names[ i ].prefixCode >> 4;

		size -= 5;
	}
	this->tlid = *(long*)from;  // TLID
	from += sizeof(long);
	from = this->epl_poly.fetch(from);
}

unsigned TigerDB::Chain::DiskSize( void )
{
  unsigned size = this->Line::DiskSize();

	size += 2 + ( this->nNames * 5 );
	size += sizeof(long); // TLID

	size += this->epl_poly.size();

	return( size );
}

void TigerDB::Chain::SetName( TigerDB::Name lineNames[], int count )
{
  TigerDB *db = (TigerDB *)((DbObject *)this)->database();

	if( count > 5 )
		count = 5;

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
			names[ i ].nameId = db->names->m_id;
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
#ifdef SAVE_FOR_NOW

void TigerDB::Chain::SetName( Name names[], int count )
{
	if( count > 5 )
		count = 5;

	this->nNames = count;
	for( int i = 0; i < count; i++ )
	{
		TigerDB::Chain::Name name;

		int code;

		if( ::strlen( names[ i ].prefix ) != 0 )
		{
			name.prefixCode = TigerGetPrefixCode( names[ i ].prefix ); 
		}

		if( ::strlen( names[ i ].type ) != 0 )
		{
			name.typeCode = TigerGetTypeCode( names[ i ].type ); 
		}

//	I will be getting the id of the name
		char name[ 41 ];

		if( ::strlen( names[ i ].suffix ) != 0 )
		{
		}
	}
}

#endif
