/******************************************************************************
*
*   SETSLL.HPP - code for the Singly-linked Network Set Class.
*
*   Copyright (c) 1992-1995, Object-Based Technologies, Topsham, ME, USA.
*   All rights reserved.
*
******************************************************************************/
#include <assert.h>

#include "sets.hpp"
#include "dboerr.h"
/*
unsigned SetSllOwner::description = SET_DEFAULT_PTR;
unsigned SetSllMember::description = SET_DEFAULT_PTR;
*/
#define ROUTINE_NAME	    "SetSllOwner::getPrior"

int SetSllOwner::getPrior(
  DbObject /*FAR*/ **member,
  SetRelation /*FAR*/ *setd
)
{
  int error;

  if( ( error = this->getNext( member, setd ) ) == DBO_NO_ERR )
  {
    DbObject::Id prior_recnr;
    SetOperations *set;
    DbObject *object;

    do
    {
      object = *member;
      assert( object != 0 );

      set = setd->memberSetOperations( object );

      prior_recnr = object->dbAddress();
    }
    while( ( error = set->getNext( member, setd ) ) == DBO_NO_ERR );

    if( error == ~DBO_NO_ERR )
    {
      object = *member;
      assert( object != 0 );

      error = object->database()->Read( prior_recnr, member );
    }
  }

  return( error );
}


#undef  ROUTINE_NAME
#define ROUTINE_NAME	    "SetSllOwner::getOwner"

int SetSllOwner::getOwner(
  DbObject *member,
  ObjHandle &owner,
  SetRelation *setd
)
{
  owner = member;

  return( DBO_NO_ERR );
}
