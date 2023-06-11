/******************************************************************************
*
*   SETS.CPP - code for the Network Set base class and SetRelation classes.
*
*   Copyright (c) 1992-1995, Object-Based Technologies, Topsham, ME, USA.
*   All rights reserved.
*
******************************************************************************/
#include <stdio.h>
#include <assert.h>
#include "sets.hpp"
#include "dboerr.h"

#define DEBUG_ONIS  "%s - object not member or owner of this set\n"
#define DEBUG_OIN  "%s - object is NULL\n"
#define DEBUG_PNM  "%s - position not member or owner of this set\n"
#define DEBUG_IOO  "%s - invalid operation on owner\n"
#define DEBUG_IOM  "%s - invalid operation on member\n"
#define DEBUG_ONO  "%s - object is not the owner of this set\n"


inline int SetRelation::member_has_priorPtr( void )
{
  return( this->member_ptrs & SetOperations::PRIOR_PTR );
}

inline int SetRelation::owner_has_priorPtr( void )
{
  return( this->owner_ptrs & SetOperations::PRIOR_PTR );
}

inline int SetRelation::member_has_ownerPtr( void )
{
  return( this->member_ptrs & SetOperations::OWNER_PTR );
}


#define ROUTINE_NAME	"SetOperations::setPrevPtr"

void SetOperations::setPrevPtr( DbObject::Id recnr )
{
//  The base class has no prior pointer to set
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetOperations::setOwnerPtr"

void SetOperations::setOwnerPtr( DbObject::Id recnr )
{
//  The base class has no owner pointer to set
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetOperations::getOwnerPtr"

DbObject::Id SetOperations::getOwnerPtr( void )
{
  return( 0L );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetOperations::getNext"

int SetOperations::getNext(
  DbObject **member,	    	// I/O: current member/next member (if TRUE)
  SetRelation *setd 	    	// I: set relation object
)
{
  DbObject *dbo;
  int error;

//	Object not in set
  if( this->next == 0L )
  {
    return( DBO_SET_ONIS );
  }

//  Should never happen
  dbo = *member;
  assert( dbo != 0 );

//  Read in next member
  if( ( error = dbo->database()->Read( this->next, member ) ) != DBO_NO_ERR )
    return( error );
    
  dbo = *member;

//  Object is not the owner
  if( dbo->getClassCode() != setd->owner_class )
  {
#ifdef DEBUG
//	Because of inheritance we may have the base class's member code
    if( dbo->getClassCode() != setd->member_class )
    {
      printf( DEBUG_ONIS, ROUTINE_NAME );
      return( ~DBO_NO_ERR );
    }
#endif
    return( DBO_NO_ERR );
  }
  
//  Object is the owner - end of the set has been reached.
  return( ~DBO_NO_ERR );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetOperations::getPrior"

int SetOperations::getPrior(
  DbObject **member,	    	// I/O: current member/previous member
  SetRelation *setd 	    	// I: set relation object
)
{
  DbObject *object;
  DbObject::Id mem_recnr;
  int error;

  object = *member;
  assert( object != 0 );

  mem_recnr = object->dbAddress();

//	Go to the end of the set and the owner is reached
  SetOperations *set = this;
  while( ( error = set->getNext( &object, setd ) ) == DBO_NO_ERR )
  {
    assert( object != 0 );

    set = setd->memberSetOperations( object );
  }

  if( error != ~DBO_NO_ERR )
    return( error );

  assert( object != 0 );
//	Skip owner and continue down set looking to set if next member was
//	the one we started with.

  set = setd->ownerSetOperations( object );
  while( set->next != mem_recnr &&
	( error = set->getNext( &object, setd ) ) == DBO_NO_ERR )
  {
    assert( object != 0 );
    set = setd->memberSetOperations( object );
  }

//	It is not an error if the prior object is the owner
  if( error == ~DBO_NO_ERR &&
      object->getClassCode() == setd->owner_class )
  {
    error = DBO_NO_ERR;
  }

  *member = object;

  return( error );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetOperations::getOwner"

int SetOperations::getOwner(
  DbObject *member, 	    	// I: member of set
  ObjHandle &owner,	    	// O: handle to owner
  SetRelation *setd 	    	// I: set relation object
)
{
  SetOperations *set;
  DbObject *object = member;
  int error;

//	Go to the end of the set - owner is found
  set = this;
  while( ( error = set->getNext( &object, setd ) ) == DBO_NO_ERR )
  {
    assert( object != 0 );

    set = setd->memberSetOperations( object );
  }

  if( error == ~DBO_NO_ERR )
  {
    owner = object;
    error = DBO_NO_ERR;
  }

  return( error );
}


/****************************** Set Relation Class ***************************/

#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::getNext"

int SetRelation::getNext(
  ObjHandle &member	    	// I/O: current member in, next member out
)
{
  SetOperations *set;
  DbObject *object;

//  Get pointer to the database object
  object = member.get();
  assert( object != 0 );

//  Get pointer to set operations object
  {
    DbObject::ClassCode class_code;

    if( ( class_code = object->getClassCode() ) == this->owner_class )
    {
      set = this->ownerSetOperations( object );

//  Empty set:
      if( set->next == object->dbAddress() || set->next == 0L )
		return( ~DBO_NO_ERR );
    }
//	Cannot check class code for member because of inheritance
    else //if( ( class_code = object->getClassCode() ) == this->member_class )
    {
      set = this->memberSetOperations( object );
    }
/*    else
    {
#ifdef DEBUG
      printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
      return( ~DBO_NO_ERR );
    }
*/
  }

//  Get next in set
  {
    int ret_val = set->getNext( &object, this );

    assert( object != 0 );
    member = object;

    return( ret_val );
  }
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::getPrior"

int SetRelation::getPrior(
  ObjHandle &member	    	// I/O: current member in, prior member out
)
{
  SetOperations *set;
  DbObject *object;

//  Get pointer to database object
  object = member.get();
  assert( object != 0 );

//  Get pointer to set operations object
  {
    DbObject::ClassCode class_code;

    if( ( class_code = object->getClassCode() ) == this->owner_class )
    {
      set = this->ownerSetOperations( object );
    }
//	Cannot check member code because of inheritance
    else //if( class_code == this->member_class )
    {
      set = this->memberSetOperations( object );
    }
/*    else
    {
#ifdef DEBUG
      printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
      return( ~DBO_NO_ERR );
    }
*/
  }

//  Get prior in set (call virtual function)
  {
    int ret_val = set->getPrior( &object, this );

    assert( object != 0 );
    member = object;

    return( ret_val );
  }
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::getLast"

int SetRelation::getLast(
  DbObject *object,        	// I: owner or member in set
  ObjHandle &last    	// O: last in set
)
{
  DbObject::ClassCode class_code;
  SetOperations *set;
  int error;

  assert( object != 0 );

//  Get a pointer to the set operations object
  if( ( class_code = object->getClassCode() ) == this->owner_class )
  {
    set = this->ownerSetOperations( object );

    if( set->next == 0L || set->next == object->dbAddress() )
      return( ~DBO_NO_ERR );

//  If owner has a prior pointer, one read returns the last member of set
    if( this->owner_has_priorPtr() )
    {
      if( ( error = set->getPrior( &object, this ) ) == DBO_NO_ERR )
      {
    	last = object;
      }

      return( error );
    }
  }
  else //if( class_code == this->member_class )
  {
    set = this->memberSetOperations( object );
    if( set->next == 0L )
      return( ~DBO_NO_ERR );
  }
/*  else
  {
#ifdef DEBUG
    printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
    return( ~DBO_NO_ERR );
  }
*/

//  Go to the end of the set, keeping the record number of the prior member
  {
    DbOM *dbom = object->database();
    DbObject::Id prior_recnr = object->dbAddress();

    while( ( error = set->getNext( &object, this ) ) == DBO_NO_ERR )
    {
	  assert( object != 0 );

      set = this->memberSetOperations( object );
      prior_recnr = object->dbAddress();
    }

//  Read the last member
    if( error == ~DBO_NO_ERR )
      error = dbom->Read( prior_recnr, last );

    return( error );
  }
}


#undef ROUTINE_NAME
#define ROUTINE_NAME 	"SetRelation::delink"

int SetRelation::delink(
  DbObject *dbo	    	    	// I: member (or owner?) in set
)
{
  DbObject::ClassCode class_code;
  SetOperations *set;
  DbObject::Id prior_recnr;
  ObjHandle handle;
  int error = DBO_NO_ERR;

  assert( dbo != 0 );

  dbo->lock();

//  Get the pointer to the set operations object
//
//  ??? What does it mean to delink the Owner ???
//
  if( ( class_code = dbo->getClassCode() ) == this->owner_class )
  {
    set = this->ownerSetOperations( dbo );
//
//  Empty set case
//
    if( set->next == 0L || set->next == dbo->dbAddress() )
    {
      goto RETURN;
    }
  }
  else //if( class_code == this->member_class )
  {
    set = this->memberSetOperations( dbo );
//
//  Not in a set
//
    if( set->next == 0L )
    {
      goto RETURN;
    }
  }
/*  else
  {
#ifdef DEBUG
    printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
    error = ~DBO_NO_ERR;
    goto RETURN;
  }
*/
//  Get the prior member and call its adjust next pointer.
  {
    SetOperations *prev_set;
    DbObject *prev_member = dbo;
    
    if( ( error = set->getPrior( &prev_member, this ) ) > DBO_NO_ERR )
      goto RETURN;
    
    assert( prev_member != 0 );
	handle = prev_member;
	
//  Get the pointer to the set operations object of the previous member
    if( ( class_code = prev_member->getClassCode() ) == this->owner_class )
    {
      prev_set = this->ownerSetOperations( prev_member );
    }
    else //if( class_code == this->member_class )
    {
      prev_set = this->memberSetOperations( prev_member );
    }
/*    else
    {
      error = ~DBO_NO_ERR;
      goto RETURN;
    }
*/

//  Re-set the prior member's next pointer and save it's record number
    prev_set->next = set->next;
    prior_recnr = prev_member->dbAddress();
    if( prev_member->attachedToDB() &&
        ( error = prev_member->write() ) != DBO_NO_ERR )
      goto RETURN;
  }

//
//  Get the next member and call its adjust prior pointer (only if the set
//  has prior pointers)
//
  if( this->member_has_priorPtr() || this->owner_has_priorPtr() )
  {
    DbObject *next_member = dbo;
    SetOperations *next_set;

    if( ( error = set->getNext( &next_member, this ) ) > DBO_NO_ERR )
      goto RETURN;

    assert( next_member != 0 );
/*	handle = next_member;*/

//  next object in set is the owner
    if( ( class_code = next_member->getClassCode() ) == this->owner_class )
    {
//  If the owner class has a prior pointer, re-set it
      if( this->owner_has_priorPtr() )
      {
		next_set = this->ownerSetOperations( next_member );
    	next_set->setPrevPtr( prior_recnr );
		if( next_member->attachedToDB() &&
		    ( error = next_member->write() ) != DBO_NO_ERR )
          goto RETURN;
      }
    }
//  next object in set is a member
    else //if( class_code == this->member_class )
    {
//  If the member object has a prior pointer, re-set it
      if( this->member_has_priorPtr() )
      {
		next_set = this->memberSetOperations( next_member );
		next_set->setPrevPtr( prior_recnr );
		if( next_member->attachedToDB() &&
	        ( error = next_member->write() ) != DBO_NO_ERR )
          goto RETURN;
      }
    }
/*    else
    {
#ifdef DEBUG
      printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
      error = ~DBO_NO_ERR;
      goto RETURN;
    }
*/
  }

//  Re-set the delinked member's pointers
  set->next = 0L;
  set->setPrevPtr( 0L );
  set->setOwnerPtr( 0L );
  if( dbo->attachedToDB() )
    error = dbo->write();

RETURN :
  dbo->Release();
  return( error );  
}


#undef ROUTINE_NAME
#define ROUTINE_NAME    "SetRelation::insertAfter"


int SetRelation::insertAfter(
  DbObject *new_dbo,	    	// I: new member to be inserted
  DbObject *pos_dbo 	    	// I: position object (owner or member)
)
{
  DbObject::ClassCode class_code;
  int error = DBO_NO_ERR;

  assert( new_dbo != 0 && pos_dbo != 0 );

  class_code = new_dbo->getClassCode();
/*  if( class_code != this->member_class )
  {
#ifdef DEBUG
    if( class_code == this->owner_class )
    {
      printf( DEBUG_IOO, ROUTINE_NAME );
    }
    else
    {
      printf( DEBUG_ONIS, ROUTINE_NAME );
    }
#endif
    return( ~DBO_NO_ERR );
  }
*/
// Delink the object if it belongs to another set.
  if( ( error = this->delink( new_dbo ) ) > DBO_NO_ERR )
    return( error );

  new_dbo->lock();

//  Only can insert a member object
  {
    SetOperations *new_set,
    	    	  *pos_set;
    int get_next_member = FALSE;

    new_set = this->memberSetOperations( new_dbo );

    pos_dbo->lock();

    if( ( class_code = pos_dbo->getClassCode() ) == this->owner_class )
    {
      pos_set = this->ownerSetOperations( pos_dbo );

//  Empty set cases:
      if( pos_set->next == 0L )
      {
        pos_set->next = pos_dbo->dbAddress();
		pos_set->setPrevPtr( new_dbo->dbAddress() );
      }
      else if( pos_set->next == pos_dbo->dbAddress() )
      {
		pos_set->setPrevPtr( new_dbo->dbAddress() );
      }
      else
      {
    	get_next_member = this->member_has_priorPtr();
      }
    }
//  Get the position set object and determine whether it is the owner or member
    else //if( class_code == this->member_class )
    {
      pos_set = this->memberSetOperations( pos_dbo );

//  Next object in chain may be a member or it may be the owner
      if( this->member_has_priorPtr() || this->owner_has_priorPtr() )
        get_next_member = TRUE;
    }
/*    else
    {
#ifdef DEBUG
      printf( DEBUG_PNM, ROUTINE_NAME );
#endif
      error = ~DBO_NO_ERR;
      goto RETURN2;
    }
*/
//  Get next member object and set its prior pointer (if necessary)
    if( get_next_member )
    {
      SetOperations *next_set;
      DbObject *next_dbo = pos_dbo;

      if( ( error = pos_set->getNext( &next_dbo, this ) ) > DBO_NO_ERR )
        goto RETURN2;
      
      assert( next_dbo != 0 );

      if( ( class_code = next_dbo->getClassCode() ) == this->owner_class )
      {
    	if( this->owner_has_priorPtr() )
    	{
		  next_set = this->ownerSetOperations( next_dbo );
          next_set->setPrevPtr( new_dbo->dbAddress() );
		  if( next_dbo->attachedToDB() &&
			( error = next_dbo->write() ) != DBO_NO_ERR )
		    goto RETURN2;
		}
      }
//  Next object in set may be member or owner - set its prior pointer
      else //if( class_code == this->member_class )
      {
    	if( this->member_has_priorPtr() )
    	{
		  next_set = this->memberSetOperations( next_dbo );
		  next_set->setPrevPtr( new_dbo->dbAddress() );
		  if( next_dbo->attachedToDB() &&
			( error = next_dbo->write() ) != DBO_NO_ERR )
		    goto RETURN2;
		}
      }
/*      else
      {
#ifdef DEBUG
	printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
		error = ~DBO_NO_ERR;
        goto RETURN2;
      }
*/
    }

//  Set the forward pointers in both the new member and the position object
    new_set->next = pos_set->next;
    new_set->setPrevPtr( pos_dbo->dbAddress() );

    pos_set->next = new_dbo->dbAddress();
    if( pos_dbo->attachedToDB() &&
        ( error = pos_dbo->write() ) != DBO_NO_ERR )
      goto RETURN2;

//  If set has an owner pointer, set it appropriately.
    if( this->member_has_ownerPtr() )
    {
      DbObject::Id owner_recnr;
      
      if( pos_dbo->getClassCode() == this->owner_class )
    	owner_recnr = pos_dbo->dbAddress();
      else
    	owner_recnr = pos_set->getOwnerPtr();

      new_set->setOwnerPtr( owner_recnr );
    }

    if( new_dbo->attachedToDB() &&
        ( error = new_dbo->write() ) != DBO_NO_ERR )
      goto RETURN2;

    error = DBO_NO_ERR;

RETURN2 :
    pos_dbo->Release();
  }

//RETURN :
  new_dbo->Release();

  return( error );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME   	"SetRelation::insertBefore"

int SetRelation::insertBefore(
  DbObject *new_dbo,	    	// I: member to be inserted
  DbObject *pos_dbo    	    	// I: position object (owner or member)
)
{
  DbObject::ClassCode class_code;
  int error = DBO_NO_ERR;

  assert( new_dbo != 0 && pos_dbo != 0 );

  if( ( class_code = new_dbo->getClassCode() ) != this->member_class )
  {
#ifdef DEBUG
    if( class_code == this->owner_class )
    {
      printf( DEBUG_IOO, ROUTINE_NAME );
    }
    else
    {
      printf( DEBUG_ONIS, ROUTINE_NAME );
    }
#endif
    return( ~DBO_NO_ERR );
  }

// Delink the object if it belongs to another set.
  if( ( error = this->delink( new_dbo ) ) > DBO_NO_ERR )
    goto RETURN;

  new_dbo->lock();

//  Only can insert a member object
  {
    SetOperations *new_set,
    	    	  *pos_set;
    int get_prior_member = FALSE;

    new_set = this->memberSetOperations( new_dbo );

    pos_dbo->lock();

    if( ( class_code = pos_dbo->getClassCode() ) == this->owner_class )
    {
      pos_set = this->ownerSetOperations( pos_dbo );

//  Empty set cases:
      if( pos_set->next == 0L ||
          pos_set->next == pos_dbo->dbAddress() )
      {
        pos_set->next = new_dbo->dbAddress();
        pos_set->setPrevPtr( new_dbo->dbAddress() );

    	if( this->owner_has_priorPtr() && pos_dbo->attachedToDB() )
		  if( ( error = pos_dbo->write() ) != DBO_NO_ERR )
		    goto RETURN2;
      }
      else if( pos_set->next == pos_dbo->dbAddress() )
      {
        pos_set->next = new_dbo->dbAddress();
        pos_set->setPrevPtr( new_dbo->dbAddress() );
    	if( pos_dbo->attachedToDB() &&
		    ( error = pos_dbo->write() ) != DBO_NO_ERR )
		  goto RETURN2;
      }
      else
      {
    	get_prior_member = TRUE;
      }
    }
//  Get the set object of the positioner
    else //if( class_code == this->member_class )
    {
//  Get prior pointer of position object
      pos_set = this->memberSetOperations( pos_dbo );
      pos_set->setPrevPtr( new_dbo->dbAddress() );

      if( this->member_has_priorPtr() && pos_dbo->attachedToDB() )
        if( ( error = pos_dbo->write() ) != DBO_NO_ERR )
	  goto RETURN2;

      get_prior_member = TRUE;
    }
/*    else
    {
#ifdef DEBUG
      printf( DEBUG_PNM, ROUTINE_NAME );
#endif
      error = ~DBO_NO_ERR;
      goto RETURN2;
    }
*/
//  Get the member before position and set its next pointer
    if( get_prior_member )
    {
      SetOperations *prev_set;
      DbObject *prev_dbo = pos_dbo;

      if( ( error = pos_set->getPrior( &prev_dbo, this ) ) > DBO_NO_ERR )
        goto RETURN2;

      assert( prev_dbo != 0 );

      if( ( class_code = prev_dbo->getClassCode() ) == this->owner_class )
      {
		prev_set = this->ownerSetOperations( prev_dbo );
      }
      else //if( class_code == this->member_class )
      {
		prev_set = this->memberSetOperations( prev_dbo );
      }
/*      else
      {
#ifdef DEBUG
	printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
		error = ~DBO_NO_ERR;
		goto RETURN2;
      }
*/
// Set pointers
      prev_set->next = new_dbo->dbAddress();
      new_set->setPrevPtr( prev_dbo->dbAddress() );

      if( prev_dbo->attachedToDB() &&
		  ( error = prev_dbo->write() ) != DBO_NO_ERR )
		goto RETURN2;
    }

//  Set the forward pointer of the new member.
    new_set->next = pos_dbo->dbAddress();

//  If set has an owner pointer, set it appropriately.
    if( this->member_has_ownerPtr() )
    {
      long int owner_recnr;
      
      if( pos_dbo->getClassCode() == this->owner_class )
    	owner_recnr = pos_dbo->dbAddress();
      else
    	owner_recnr = pos_set->getOwnerPtr();

      new_set->setOwnerPtr( owner_recnr );
    }

    if( new_dbo->attachedToDB() )
      error = new_dbo->write();

RETURN2 :
    pos_dbo->Release();
  }

RETURN :
  new_dbo->Release();

  return( error );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	    "SetRelation::getOwner"

int SetRelation::getOwner(
  DbObject *dbo, 	    	// I: member in a set
  ObjHandle &owner	    	// O: owner of the set
)
{
  DbObject::ClassCode class_code;

  assert( dbo != 0 );

//  We have the owner
  if( ( class_code = dbo->getClassCode() ) == this->owner_class )
  {
    owner = dbo;

    return( DBO_NO_ERR );
  }

//  if( class_code == this->member_class )
  {
    SetOperations *set = this->memberSetOperations( dbo );

    return( set->getOwner( dbo, owner, this ) );
  }

/*#ifdef DEBUG
  printf( DEBUG_ONIS, ROUTINE_NAME );
#endif

//  The owner is not found
  return( ~DBO_NO_ERR );*/
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::isOwner"

int SetRelation::isOwner(
  DbObject *dbo	    	    	// I: object to check
)
{
  DbObject::ClassCode class_code;

  assert( dbo != 0 );

  if( ( class_code = dbo->getClassCode() ) == this->owner_class )
  {
    return( DBO_NO_ERR );
  }

#ifdef DEBUG
  if( class_code != this->member_class )
  {
    printf( DEBUG_ONIS, ROUTINE_NAME );
  }
#endif

  return( ~DBO_NO_ERR );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::empty"

int SetRelation::empty( DbObject *dbo )
{
  assert( dbo != 0 );

  if( dbo->getClassCode() == this->owner_class )
  {
    SetOperations *set = this->ownerSetOperations( dbo );

    if( set->next != dbo->dbAddress() && set->next != 0L )
      return( DBO_NO_ERR );
  }
  else
  {
#ifdef DEBUG
    printf( DEBUG_ONO, ROUTINE_NAME );
#endif
  }

  return( ~DBO_NO_ERR );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::isMember"

int SetRelation::isMember( DbObject *dbo )
{
  DbObject::ClassCode class_code;

  assert( dbo != 0 );

  if( ( class_code = dbo->getClassCode() ) != this->owner_class /*== this->member_class*/ )
  {
    return( DBO_NO_ERR );
  }

#ifdef DEBUG
  if( class_code != this->owner_class )
  {
    printf( DEBUG_ONIS, ROUTINE_NAME );
  }
#endif

  return( ~DBO_NO_ERR );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::removeSet"

int SetRelation::removeSet( DbObject *owner )
{
  DbObject::ClassCode class_code;
  int error;

  assert( owner != 0 );

  if( ( class_code = owner->getClassCode() ) != this->owner_class )
  {
#ifdef DEBUG
     if( class_code == this->member_class )
       printf( DEBUG_IOM, ROUTINE_NAME );
     else
       printf( DEBUG_ONIS, ROUTINE_NAME );
#endif
     return( ~DBO_NO_ERR );
  }

  owner->lock();

  {
    DbObject::Id next_recnr,
    	     owner_recnr = owner->dbAddress();
    SetOperations *set;

    set = this->ownerSetOperations( owner );

//  If not empty set - go through and set all pointers to 0.
    if( ( next_recnr = set->next ) != 0L &&
          next_recnr != owner_recnr )
    {
      set->next = owner_recnr;
      set->setPrevPtr( owner_recnr );
      if( owner->attachedToDB() &&
	  ( error = owner->write() ) != DBO_NO_ERR )
		goto RETURN;

      while( next_recnr != owner_recnr )
      {
    	DbObject *member;

		if( ( error = owner->database()->Read( next_recnr, &member ) )
		     != DBO_NO_ERR )
    	  goto RETURN;

    	assert( member != 0 );

		set = this->memberSetOperations( member );

    	next_recnr = set->next;
    	set->next = 0L;
		set->setPrevPtr( 0L );
    	set->setOwnerPtr( 0L );

    	if( member->attachedToDB() && 
		    ( error = member->write() ) != DBO_NO_ERR )
		  goto RETURN;
      }
    }
  }


RETURN :
  owner->Release();

  return( error );
}


#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::move"

int SetRelation::move(
  DbObject *move_dbo,      	// I: owner or member of the set to be moved
  DbObject *pos_dbo     	// I: owner or member of receiving set
)
{
  DbObject::ClassCode move_class,
    	        pos_class;
  SetOperations *move_set,
    	    	*pos_set,
    	    	*set;
  DbObject::Id next_recnr,
    	   last_recnr,
    	   prev_recnr,
    	   save_recnr;
  ObjHandle newOwner,
    	   lastMember,
    	   nextMember;
  int gotObject = FALSE;
  DbObject *object,
    	   *prevMember,
		   *moveMember;
  int error = DBO_NO_ERR;

  assert( move_dbo != 0 && pos_dbo != 0 );

  move_dbo->lock();
  pos_dbo->lock();

//  objects after the owner will be moved
  if( ( move_class = move_dbo->getClassCode() ) == this->owner_class )
  {

//  If set to be moved is empty just return
    if( this->empty( move_dbo ) == DBO_NO_ERR )
      goto RETURN;

    moveMember = prevMember = move_dbo;

    prevMember->lock();

    move_set = this->ownerSetOperations( move_dbo );
    if( ( error = move_set->getNext( &moveMember, this ) ) == DBO_NO_ERR )  // May have bug here 4/11/23
      gotObject = TRUE;
    else if( error > DBO_NO_ERR )
    {
      prevMember->Release();
      goto RETURN;
    }

    assert( moveMember != 0 );

    moveMember->lock();
  }
  else //if( move_class == this->member_class )
  {
    prevMember = moveMember = move_dbo;

    moveMember->lock();

    move_set = this->memberSetOperations( move_dbo );
    if( ( error = move_set->getPrior( &prevMember, this ) ) == DBO_NO_ERR ) // May have bug here 4/11/23
      gotObject = TRUE;
    else if( error > DBO_NO_ERR )
    {
      moveMember->Release();
      goto RETURN;
    }

    assert( prevMember != 0 );

    prevMember->lock();
  }
/*  else
  {
#ifdef DEBUG
    printf( DEBUG_PNM, ROUTINE_NAME );
#endif
    error = ~DBO_NO_ERR;
    goto RETURN;
  }
*/
  nextMember = pos_dbo;

  if( ( pos_class = pos_dbo->getClassCode() ) == this->owner_class )
  {
    pos_set = this->ownerSetOperations( pos_dbo );
    if( this->member_has_ownerPtr() )
      newOwner = pos_dbo;
  }
  else //if( pos_class == this->member_class )
  {
    pos_set = this->memberSetOperations( pos_dbo );
    if( this->member_has_ownerPtr() &&
		( error = this->getOwner( pos_dbo, newOwner ) ) != DBO_NO_ERR )
      goto RETURN2;
  }
/*  else
  {
#ifdef DEBUG
    printf( DEBUG_PNM, ROUTINE_NAME );
#endif
    error = ~DBO_NO_ERR;
    goto RETURN2;
  }
*/
//
//  Save next member pointer in position set and get the next object
//  in the position set.
//
  next_recnr = pos_set->next;
  if( ( error = this->getNext( nextMember ) ) > DBO_NO_ERR )
    goto RETURN2;

//  (1) Update position object's next pointer
  pos_set->next = moveMember->dbAddress();
  if( pos_dbo->attachedToDB() &&
      ( error = pos_dbo->write() ) != DBO_NO_ERR )
    goto RETURN2;

//  (2) Update move member's prior pointer (if has one).
  if( this->member_has_priorPtr() )
  {
    move_set->setPrevPtr( pos_dbo->dbAddress() );
    if( move_dbo->attachedToDB() &&
        ( error = move_dbo->write() ) != DBO_NO_ERR )
    goto RETURN2;
  }
//
//  If set has owner pointer, go down the set till the last member is reached,
//  while re-setting the owner pointer of each member to the new owner.
//
  if( this->member_has_ownerPtr() )
  {
    DbObject::Id owner_ptr,
    	     prior_ptr;

    object = moveMember;
    owner_ptr = object->dbAddress();
    for( ;; )
    {
      prior_ptr = object->dbAddress();

      move_set->setOwnerPtr( owner_ptr );

      if( object->attachedToDB() &&
          ( error = object->write() ) != DBO_NO_ERR )
		goto RETURN2;

      if( ( error = move_set->getNext( &object, this ) ) != DBO_NO_ERR )
    	break;

      assert( object != 0 );

      move_set = this->memberSetOperations( object );
    }

    if( ( error = pos_dbo->database()->Read( prior_ptr, lastMember ) ) != DBO_NO_ERR )
      goto RETURN2;

    last_recnr = prior_ptr;
  }
//
//  No owner pointer
//
  else
  {
    if( ( error = this->getLast( moveMember, lastMember ) ) > DBO_NO_ERR )
      goto RETURN2;

    if( ( object = lastMember.get() ) == 0 )
    {
#ifdef DEBUG
      printf( DEBUG_OIN, ROUTINE_NAME );
#endif
      error = ~DBO_NO_ERR;
      goto RETURN2;
    }

    last_recnr = object->dbAddress();
  }
//
//  (3) Set the next object's (after position in receving set) prior pointer
//      (if it has one).
//
  object = nextMember.get();
  assert( object != 0 );

  if( object->getClassCode() == this->owner_class )
  {
    if( this->owner_has_priorPtr() )
    {
      set = this->ownerSetOperations( object );
      set->setPrevPtr( last_recnr );
      if( object->attachedToDB() &&
          ( error = object->write() ) != DBO_NO_ERR )
		goto RETURN2;
    }
  }
  else if( this->member_has_priorPtr() )
  {
    set = this->memberSetOperations( object );
    set->setPrevPtr( last_recnr );
    if( object->attachedToDB() &&
        ( error = object->write() ) != DBO_NO_ERR )
      goto RETURN2;
  }
//
//  (4) Get last member's set and set its member pointer.
//
  object = lastMember.get();
  assert( object != 0 );

  set = this->memberSetOperations( object );
  save_recnr = set->next;
  set->next = next_recnr;
  if( object->attachedToDB() &&
      ( error = object->write() ) != DBO_NO_ERR )
    goto RETURN2;
//
//  (5) Set the previous member's (of the move set) next pointer.
//
  prev_recnr = prevMember->dbAddress();

  if( prevMember->getClassCode() == this->owner_class )
  {
    set = this->ownerSetOperations( prevMember );
  }
  else
  {
    set = this->memberSetOperations( prevMember );
  }
  set->next = save_recnr;
  if( prevMember->attachedToDB() &&
      ( error = prevMember->write() ) != DBO_NO_ERR )
    goto RETURN2;

//	(6) Update move owner's prior pointer (if it has one).
  if( this->owner_has_priorPtr() )
  {
    ObjHandle moveOwner = lastMember;

    if( ( error = this->getNext( moveOwner ) ) > DBO_NO_ERR )
      goto RETURN2;

    object = moveOwner.get();
    assert( object != 0 );

    set = this->ownerSetOperations( object );

    set->setPrevPtr( prev_recnr );
    if( object->attachedToDB() &&
       ( error = object->write() ) != DBO_NO_ERR )
      goto RETURN2;
  }

  error = DBO_NO_ERR;

RETURN2 :
  prevMember->Release();
  moveMember->Release();

RETURN :
  pos_dbo->Release();
  move_dbo->Release();

  return( error );
}

#undef ROUTINE_NAME
#define ROUTINE_NAME	"SetRelation::commit"

int SetRelation::commit(
  DbObject /*FAR*/ *owner      	// I: owner of the set to be made persistent
)
{
  SetOperations *prev_set,
    	        *owner_set;
  DbObject::Id last_recnr = 0L;
  ObjHandle member;
  DbObject *prev;
  int error = ~DBO_NO_ERR;

  if( ! this->isOwner( owner ) ||
      ( error = owner->write() ) != DBO_NO_ERR )
    return( error );

  owner->lock();

  prev = owner;
  prev_set = owner_set = this->ownerSetOperations( owner );

  prev->lock();
  member = owner;
  while( ( error = this->getNext( member ) ) == DBO_NO_ERR )
  {
    SetOperations *curr_set;
    DbObject *curr = member.get( TRUE );

    if( ( error = curr->write() ) != DBO_NO_ERR )
    {
      prev->Release();
      curr->Release();
      goto RETURN;
    }
 
    prev_set->next = last_recnr = curr->dbAddress();
    curr_set = this->memberSetOperations( curr ); // May have a bug here 4/11/23

    if( this->member_has_priorPtr() )
      curr_set->setPrevPtr( prev->dbAddress() );

    if( this->member_has_ownerPtr() )
      curr_set->setOwnerPtr( owner->dbAddress() );

    prev->Release();
    prev_set = curr_set;
    prev = curr;
  }

  if( error != ~DBO_NO_ERR )
    goto RETURN;

  if( last_recnr != 0L )
  {
    prev_set->next = owner->dbAddress();
    prev->Release();

    if( ( error = prev->write() ) != DBO_NO_ERR )
      goto RETURN;
  }

  if( this->owner_has_priorPtr() )
  {
    owner_set->setPrevPtr( last_recnr );
    if( ( error = owner->write() ) != DBO_NO_ERR )
      goto RETURN;
  }

  error = DBO_NO_ERR;

RETURN :
  owner->Release();

  return( error );
}

//  Constructor
SetRelation::SetRelation(
  DbObject::ClassCode oc,	    	    // I: class code of owner
  int oo,   	    	    	    // I: offset of owner class
  unsigned of,	    	    	    // I: class description
  DbObject::ClassCode mc,	    	    // I: class code of member
  int mo,   	    	    	    // I: offset of member class
  unsigned mf	    	    	    // I: class description
)
{
  this->owner_class = oc;
  this->owner_offset = oo;
  this->owner_ptrs = of;
  this->member_class = mc;
  this->member_offset = mo;
  this->member_ptrs = mf;
}
