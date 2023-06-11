/******************************************************************************
*
*   SETOWNER.CPP - code for the Singly-linked Network Set Class.
*
*   Copyright (c) 1992-1995, Object-Based Technologies, Topsham, ME, USA.
*   All rights reserved.
*
******************************************************************************/
#include <assert.h>

#include "sets.hpp"
#include "dboerr.h"
/*
unsigned SetSllMemberOP::description = SET_OWNER_PTR;

unsigned SetDllMemberOP::description = SET_PRIOR_PTR | SET_OWNER_PTR;
*/
#define SNP_FORMAT	    "%s - NULL pointer\n"

DbObject::Id SetSllMemberOP::getOwnerPtr( void )
{
  return( this->owner );
}


void SetSllMemberOP::setOwnerPtr( DbObject::Id ptr )
{
  this->owner = ptr;
}


#define ROUTINE_NAME	    "SetSllMemberOP::getOwner"

int SetSllMemberOP::getOwner(
  DbObject /*FAR*/ *member,
  ObjHandle &owner_of_set,
  SetRelation /*FAR*/ *setd
)
{
  if( this->owner == 0L )
  {
#ifdef DEBUG
    printf( SNP_FORMAT, ROUTINE_NAME ); ???? !!!!!
#endif
    return( ~DBO_NO_ERR );
  }

  assert( member != 0 );

  return( member->database()->Read( this->owner, owner_of_set ) );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	    "SetSllMemberOP::getPrior"

int SetSllMemberOP::getPrior(
  DbObject /*FAR*/ **member,
  SetRelation /*FAR*/ *setd
)
{
  DbObject *object;
  DbObject::Id mem_recnr;
  int error;

  if( this->owner == 0L )
  {
#ifdef DEBUG
    printf( SNP_FORMAT, ROUTINE_NAME );
#endif
    return( ~DBO_NO_ERR );
  }

  object = *member;
  assert( object != 0 );

  mem_recnr = object->dbAddress();

/*
*   Get owner and then go down the set until the previous is encounted
*/
  if( ( error = object->database()->Read( this->owner, member ) ) == DBO_NO_ERR )
  {
    SetOperations *set;
/*
*   Go down set looking to set if next member was the one we
*   started with.
*/
    object = *member;
    assert( object != 0 );

    set = setd->ownerSetOperations( object );

    if( set->next == mem_recnr )
      return( ~DBO_NO_ERR );

    if( ( error = set->getNext( member, setd ) ) == DBO_NO_ERR )
    {
      do
      {
    	object = *member;
    	assert( object != 0 );

		set = setd->memberSetOperations( object );
      }
      while( set->next != mem_recnr &&
             ( error = set->getNext( member, setd ) ) == DBO_NO_ERR );    
    }

    if( error == ~DBO_NO_ERR )
      error = DBO_NO_ERR;
  }

  return( error );
}


DbObject::Id SetDllMemberOP::getOwnerPtr( void )
{
  return( this->owner );
}


void SetDllMemberOP::setOwnerPtr( DbObject::Id ptr )
{
  this->owner = ptr;
}

#undef ROUTINE_NAME
#define ROUTINE_NAME	    "SetDllMemberOP::getOwner"

int SetDllMemberOP::getOwner(
  DbObject /*FAR*/ *member,
  ObjHandle &owner_of_set,
  SetRelation /*FAR*/ *setd
)
{
  if( this->owner == 0L )
  {
#ifdef DEBUG
    printf( SNP_FORMAT, ROUTINE_NAME ); ???
#endif
    return( ~DBO_NO_ERR );
  }

  assert( member != 0 );

  return( member->database()->Read( this->owner, owner_of_set ) );
}
