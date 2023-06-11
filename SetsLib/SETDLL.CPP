/******************************************************************************
*
*   SETDLL.CPP - code for the Singly-linked Network Set Class.
*
*   Copyright (c) 1992-1995, Object-Based Technologies, Topsham, ME, USA.
*   All rights reserved.
*
******************************************************************************/
#include <assert.h>
#include "sets.hpp"
#include "dboerr.h"

#include "dab.hpp"

#define SNP_FORMAT	    "%s - 0 pointer\n"
/*
unsigned SetDllOwner::description = SET_PRIOR_PTR;

unsigned SetDllMember::description = SET_PRIOR_PTR;
*/
#define ROUTINE_NAME	    "SetDllOwner::getPrior"

int
SetDllOwner::getPrior(
  DbObject /*FAR*/ **owner,
  SetRelation /*FAR*/ *setd
)
{
  DbObject::Id recnr;
  DbObject *object;

  if( ( recnr = this->prev ) == DAB::NULL_REC )
  {
	assert( recnr != DAB::NULL_REC );
    return( ~DBO_NO_ERR );
  }

  object = *owner;
  assert( object != 0 );

  if( recnr != object->dbAddress() )
      return( object->database()->Read( recnr, owner ) );

  return( ~DBO_NO_ERR );
}


void SetDllOwner::setPrevPtr( DbObject::Id recnr )
{
  this->prev = recnr;
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	    	"SetDllMember::getPrior"

int SetDllMember::getPrior(
  DbObject /*FAR*/ **member,
  SetRelation /*FAR*/ *setd
)
{
  DbObject *object;
  DbObject::Id recnr;
  int error;

  if( ( recnr = this->prev ) == DAB::NULL_REC )
  {
	assert( recnr != DAB::NULL_REC );
    return( ~DBO_NO_ERR );
  }

  object = *member;
  assert( object != 0 );

  {
    DbObject::ClassCode class_code = object->getClassCode();

    if( ( error = object->database()->Read( recnr, member ) ) == DBO_NO_ERR )
    {
      object = *member;
      assert( class_code == object->getClassCode() );
      if( class_code != object->getClassCode() )
    	error = ~DBO_NO_ERR;
    }
  }

  return( error );
}


void SetDllMember::setPrevPtr( DbObject::Id recnr )
{
  this->prev = recnr;
}
