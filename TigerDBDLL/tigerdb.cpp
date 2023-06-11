///////////////////////////////////////////////////////////////////////////////
//
//	TIGERDB.CPP - declarations for the Geographic Databasenames
//
//	Copyright (c) 1992-1996, Object-Based Technologies, Topsham, ME, USA.
//	All rights reserved.
///////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include <assert.h>
#include <afxdb.h>

#include "tigerdb.hpp"
#include "distname.h"

const int MAX_TIGER_LINES		= 700;

TigerDB::TigerDB(CDatabase *rDB) : GeoDB( 0 )
{
	this->nLines = 0;
  this->lines = new Chain[ MAX_TIGER_LINES ];
  assert( this->lines != 0 );
	this->db = rDB/*new CDatabase*/;
  assert( this->db != 0 );
#ifdef SAVE_FOR_NOW
	this->db->SetQueryTimeout( 60 * 10 );
	//this->db->Open( _T("TigerData"), FALSE, TRUE, _T("ODBC;UID=guest;PWD="), FALSE ); // Access MDB
	this->db->Open(_T("TigerBase"), FALSE, TRUE, _T("ODBC;UID=guest;PWD="), FALSE);  // SQL Server
	this->db->SetSynchronousMode( TRUE );
#endif

	this->names = new DistNames( this->db );
  assert( this->names != 0 );
	this->names->nameParam = "";
	this->names->m_strFilter = _T("(NAME = ?)");
	this->names->Open( CRecordset::forwardOnly, 0, CRecordset::readOnly );
	while( ! this->names->IsEOF() )
		this->names->MoveNext();

	this->nameById = new DistNames( this->db );
  assert( this->nameById != 0 );
	this->nameById->idParam = 0;
	this->nameById->m_strFilter = _T("(ID = ?)");
	this->nameById->Open( CRecordset::forwardOnly, 0, CRecordset::readOnly );
	while( ! this->nameById->IsEOF() )
		this->nameById->MoveNext();
}

TigerDB::~TigerDB()
{
  if( this->lines != 0 )
    delete [] this->lines;

	if( this->IsOpen() )
	{
		this->Close();
	}

	assert( this->names != 0 );
	delete this->names;

	assert( this->nameById != 0 );
	delete this->nameById;
/*
	assert( this->db != 0 );
	delete this->db;
*/
}

int TigerDB::Close( void )
{
	assert( this->names != 0 );
	if( this->names->IsOpen() )
	{
		this->names->Close();
	}

	assert( this->nameById != 0 );
	if( this->nameById->IsOpen() )
	{
		this->nameById->Close();
	}
/*
	assert( this->db != 0 );
	if( this->db->IsOpen() )
	{
		this->db->Close();
	}
*/
	return( this->GeoDB::Close() );
}

DbObject *TigerDB::CreateDbObject( DbObject::ClassCode code )
{
  switch( code )
  {
    DbObject *object;

    default :
		  return( this->GeoDB::CreateDbObject( code ) );
      break;


    case DB_TIGER_LINE :    	
      if( this->nLines < MAX_TIGER_LINES )
		  {
	    	object = (DbObject *)&this->lines[ this->nLines ];
	    	this->nLines++;
	    	return( object );
      }
      break;

		case DB_TIGER_POLY:
			object = new TigerDB::Polygon;
			return object;
			break;

		case DB_TIGER_EdgePolyLink:
			object = new TigerDB::EdgePolyLink;
			return object;
			break;
  }

  return( 0 );
}

void TigerDB::DeleteDbObject( DbObject::ClassCode code, DbObject *dbo )
{
  DbObject *object = dbo;

  switch( code )
  {
    default :
		  this->GeoDB::DeleteDbObject( code, dbo );
      break;

    case DB_TIGER_LINE :    	
      assert( this->nLines > 0 );
      if( this->nLines > 0 )
		  {
	    	--this->nLines;
      }
      break;       
  }
}
/*
TigerDB::Chain::Chain() {
	this->nNames = 0;
	this->code = 0;
}

TigerDB::Chain::~Chain() {

}
*/