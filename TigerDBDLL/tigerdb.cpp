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
#include "GNISName.h"

using namespace NodeEdgePoly;

const int MAX_TIGER_LINES		= 700;

TigerDB::TigerDB(CDatabase *rDB) : GeoDB(600, 800, 0, 500)
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

	this->nameByFeatureId = new GNISName(this->db);
	this->nameByFeatureId->idParam = 0;
	this->nameByFeatureId->m_strFilter = _T("(feature_id = ?)");
	this->nameByFeatureId->Open(CRecordset::forwardOnly, 0, CRecordset::readOnly);
	while (!this->nameByFeatureId->IsEOF())
		this->nameByFeatureId->MoveNext();
}

TigerDB::~TigerDB()
{
	if (this->IsOpen())
	{
		this->Close();
	}

	if( this->lines != 0 )
    delete [] this->lines;

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
	DbObject* object = 0;
	switch( code )
  {
    default :
		  return( this->GeoDB::CreateDbObject( code ) );
      break;

		case DB_EDGE:
    //case DB_TIGER_LINE :    
			object = new Chain;
			this->nLines++;
#ifdef SAVE_FOR_NOW
      if( this->nLines < MAX_TIGER_LINES )
		  {
	    	object = (DbObject *)&this->lines[ this->nLines ];
	    	this->nLines++;
	    	return( object );
      }
#endif
      break;

		//case DB_TIGER_POLY:
		case DB_POLY:
			object = new TigerDB::Polygon;
			//return object;
			break;

		case DB_POINT:
			object = new TigerDB::GNISFeature;
#ifdef SAVE_FOR_NOW
			static int nPoints = 0;  // Temp
			if (nPoints++ < 100)
			{
				object = new TigerDB::GNISFeature;
				return object;
			}
#endif
			break;
  }

  return( object );
}

void TigerDB::DeleteDbObject( DbObject::ClassCode code, DbObject *dbo )
{
  DbObject *object = dbo;

  switch( code )
  {
    default :
		  this->GeoDB::DeleteDbObject( code, dbo );
      break;

		  case DB_EDGE : 
    //case DB_TIGER_LINE :    	
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