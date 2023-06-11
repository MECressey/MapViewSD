/******************************************************************************
*
*   SETS.HPP - declarations for the Network Set Classes.
*
*   Copyright (c) 1992-1995, Object-Based Technologies, Topsham, ME, USA.
*   All rights reserved.
*
******************************************************************************/
#ifndef SETS_HPP
#define SETS_HPP

#define NEW_STUFF

#include <string.h>

#include "dbom.hpp"

//  forward class references
class SetRelation;
class SetSllOwner;
class SetSllMember;
class SetDllOwner;
class SetDllMember;
class SetSllMemberOP;
class SetDllMemberOP;

//  flags to describe contents of each set class

//  Base class for all sets
class SetOperations {
  public :
    void init( DbObject::Id ptr = 0L )   { this->next = ptr; };
    char /*FAR*/ *store( char /*FAR*/ * );
    char /*FAR*/ *fetch( char /*FAR*/ * );
    unsigned size( void );
	enum Type {
	  DEFAULT_PTR = 0,		// contains only next pointer
	  PRIOR_PTR = 1<<0,   	// prior pointer bit
	  OWNER_PTR = 1<<1   	// owner poiter bit
    };
    
  protected :
    int getNext( DbObject /*FAR*/ **, SetRelation /*FAR*/ * );
    DbObject::Id getNextPtr( void )	    { return( next ); };
    void setNextPtr( long ptr )	    { next = ptr; };
    virtual void setPrevPtr( long int );
    virtual DbObject::Id getOwnerPtr( void );
    virtual void setOwnerPtr( long int );
    virtual int getPrior( DbObject /*FAR*/ **, SetRelation /*FAR*/ * );
    virtual int getOwner( DbObject /*FAR*/ *, ObjHandle &, SetRelation /*FAR*/ * );
    SetOperations()   { this->init(); };

  private :
    friend SetRelation;
    friend SetSllOwner;
    friend SetSllMember;
    friend SetDllOwner;
    friend SetDllMember;
    friend SetSllMemberOP;
    friend SetDllMemberOP;
    long int next;
};


inline char /*FAR*/ *	    	    	// O: updated address of buffer to store into
SetOperations::store(
  char /*FAR*/ *to  	    	    	// I: buffer to write into
)
{
// store next pointer
#if defined( NEW_STUFF )
	::memcpy( to, &this->next, sizeof( this->next ) );
#else
  *(long int *)to = this->next;
#endif
// update pointer and return it
  return( to + sizeof( this->next ) );
}


inline char /*FAR*/ *	    	    	// O: updated address of buffer
SetOperations::fetch(
  char /*FAR*/ *from	    	    	// I: buffer to read from
)
{
// retrieve next pointer
#if defined( NEW_STUFF )
	::memcpy( &this->next, from, sizeof( this->next ) );
#else
  this->next = *(long int *)from;
#endif
// update pointer and return it
  return( from + sizeof( this->next ) );
}


inline unsigned	    	    	// O: size needed on disk to store base class
SetOperations::size( void )
{
  return( (unsigned)sizeof( this->next ) );
}


//  Owner of a singly-linked set - only a forward pointer
class SetSllOwner : public SetOperations {
  public :
//    static unsigned description;
	enum Type {
	  description = DEFAULT_PTR
	};
    SetSllOwner() : SetOperations()	    { }
  
  private :
    int getPrior( DbObject /*FAR*/ **, SetRelation /*FAR*/ * );
    int getOwner( DbObject /*FAR*/ *, ObjHandle &, SetRelation /*FAR*/ * );
};


//  Member of a singly-linked set - only a forward pointer
class SetSllMember : public SetOperations {
  public :
//    static unsigned description;
	enum Type {
	  description = DEFAULT_PTR
	};
    SetSllMember() : SetOperations() { }
};


//  Owner of a doubly-linked set - forward and prior pointers
class SetDllOwner : public SetOperations {
  public :
	enum Type {
	  description = PRIOR_PTR
	};
//    static unsigned description;
    void init( DbObject::Id forw = 0L, DbObject::Id backw = 0L )
    		{ SetOperations::init( forw ), this->prev = backw; };
    SetDllOwner() : SetOperations()	    	{ this->prev = 0L; }
    char /*FAR*/ *store( char /*FAR*/ * );
    char /*FAR*/ *fetch( char /*FAR*/ * );
    unsigned size( void );

  protected :
    int getPrior( DbObject /*FAR*/ **, SetRelation /*FAR*/ * );
    void setPrevPtr( DbObject::Id );
    DbObject::Id getPriorPtr()	    	{ return( this->prev ); };
    void setPriorPtr( long ptr )    	{ this->prev = ptr; };

    DbObject::Id prev;
};


inline char /*FAR*/ *	    	    	// O: updated address of buffer to store into
SetDllOwner::store(
  char /*FAR*/ *to  	    	    	// I: buffer to write into
)
{
//  store base class
  to = this->SetOperations::store( to );

//  store prior pointer
  *(long int *)to = this->prev;

//  update address and return
  return( to + sizeof( this->prev ) );
}


inline char /*FAR*/ *	    	    	// O: updated address of buffer
SetDllOwner::fetch(
  char /*FAR*/ *from	    	    	// I: buffer to read from
)
{
//  retrieve base class
  from = this->SetOperations::fetch( from );

//  retrieve prior pointer
  this->prev = *(DbObject::Id *)from;

//  update address and return
  return( from + sizeof( this->prev ) );
}


inline unsigned	    	    	// O: size needed on disk to store this class
SetDllOwner::size( void )
{
  return( (unsigned)sizeof( this->prev ) + this->SetOperations::size() );
}


//  Member of a doubly-linked set - forward and prior pointers
class SetDllMember : public SetOperations {
  public :
	enum Type {
	  description = PRIOR_PTR
	};
//    static unsigned description;
    void init( DbObject::Id forw = 0L, DbObject::Id backw = 0L )
    	{ SetOperations::init( forw ), this->prev = backw; };
    SetDllMember() : SetOperations()	    	{ this->prev = 0L; }
    char /*FAR*/ *store( char /*FAR*/ * );
    char /*FAR*/ *fetch( char /*FAR*/ * );
    unsigned size( void );

  protected :
    int getPrior( DbObject /*FAR*/ **, SetRelation /*FAR*/ * );
    void setPrevPtr( long int );
    DbObject::Id getPriorPtr()	    	{ return( this->prev ); };
    void setPriorPtr( DbObject::Id ptr )    	{ this->prev = ptr; };

    DbObject::Id prev;
};


inline char /*FAR*/ *	    	    	// O: updated address of buffer to store into
SetDllMember::store(
  char /*FAR*/ *to  	    	    	// I: buffer to write into
)
{
//  store base class
  to = this->SetOperations::store( to );

//  store prior pointer
  *(long int *)to = this->prev;

//  update address and return
  return( to + sizeof( this->prev ) );
}


inline char /*FAR*/ *	    	    	// O: updated address of buffer
SetDllMember::fetch(
  char /*FAR*/ *from	    	    	// I: buffer to read from
)
{
//  retrieve base class
  from = SetOperations::fetch( from );

//  retrieve prior pointer
  this->prev = *(DbObject::Id *)from;

//  update address and return
  return( from + sizeof( this->prev ) );
}


inline unsigned	    	    	// O: size needed on disk to store this class
SetDllMember::size( void )
{
  return( (unsigned)sizeof( DbObject::Id ) + SetOperations::size() );
}

//  Member of a singly-linked set - forward and owner pointers
class SetSllMemberOP : public SetSllMember {
  public :
	enum Type {
	  description = OWNER_PTR
	};
//    static unsigned description;
    void init( DbObject::Id forw = 0L, DbObject::Id o_ptr = 0L )
       { SetSllMember::init( forw ), this->owner = o_ptr; };
    SetSllMemberOP() : 	SetSllMember()	    	{ this->owner = 0L; }
    char /*FAR*/ *store( char /*FAR*/ * );
    char /*FAR*/ *fetch( char /*FAR*/ * );
    unsigned size( void );

  protected :
    int getPrior( DbObject /*FAR*/ **, SetRelation /*FAR*/ * );
    int getOwner( DbObject /*FAR*/ *, ObjHandle &, SetRelation /*FAR*/ * );
    DbObject::Id getOwnerPtr( void );
    void setOwnerPtr( DbObject::Id );

    DbObject::Id owner;
};


inline char /*FAR*/ *	    	    	// O: updated address of buffer to store into
SetSllMemberOP::store(
  char /*FAR*/ *to  	    	    	// I: buffer to write into
)
{
//  store base class
  to = this->SetSllMember::store( to );

//  store owner pointer
  *(long int *)to = this->owner;

//  update pointer and return
  return( to + sizeof( this->owner ) );
}


inline char /*FAR*/ *	    	    	// O: updated address of buffer
SetSllMemberOP::fetch(
  char /*FAR*/ *from	    	    	// I: buffer to read from
)
{
//  retrieving the base class
  from = this->SetSllMember::fetch( from );

//  retrieving the owner pointer
  this->owner = *(DbObject::Id *)from;

//  update pointer and return
  return( from + sizeof( this->owner ) );
}


inline unsigned	    	    	// O: size needed on disk to store this class
SetSllMemberOP::size( void )
{
  return( (unsigned)sizeof( this->owner ) + this->SetSllMember::size() );
}


//  Member of a doubly-linked set - forward, prior, and owner pointers
class SetDllMemberOP : public SetDllMember {
  public :
	enum Type {
	  description = PRIOR_PTR | OWNER_PTR
	};
//    static unsigned description;
    void init( DbObject::Id forw = 0L, DbObject::Id backw = 0L,
		DbObject::Id o_ptr = 0L )
       { SetDllMember::init( forw, backw ), this->owner = o_ptr; };
    SetDllMemberOP() : 	SetDllMember()	    	{ this->owner = 0L; }
    char /*FAR*/ *store( char /*FAR*/ * );
    char /*FAR*/ *fetch( char /*FAR*/ * );
    unsigned size( void );

  protected :
    int getOwner( DbObject /*FAR*/ *, ObjHandle &, SetRelation /*FAR*/ * );
    long int getOwnerPtr( void );
    void setOwnerPtr( long int );

    DbObject::Id owner;
};


inline char /*FAR*/ *	    	    	// O: updated address of buffer to store into
SetDllMemberOP::store(
  char /*FAR*/ *to  	    	    	// I: buffer to write into
)
{
//  store the base class
  to = this->SetDllMember::store( to );

//  store the owner pointer
  *(DbObject::Id *)to = this->owner;

//  update pointer and return
  return( to + sizeof( this->owner ) );
}


inline char /*FAR*/ *	    	    	// O: updated address of buffer
SetDllMemberOP::fetch(
  char /*FAR*/ *from	    	    	// I: buffer to read from
)
{
//  retrieve the base class
  from = SetDllMember::fetch( from );

//  retrieve the owner pointer
  this->owner = *(DbObject::Id *)from;

//  update the pointer and return
  return( from + sizeof( this->owner ) );
}


inline unsigned	    	    	// O: size needed on disk to store this class
SetDllMemberOP::size( void )
{
  return( (unsigned)sizeof( this->owner ) + this->SetDllMember::size() );
}


//  Class that manages the set classes themselves
class SetRelation {
  public :
    SetRelation( DbObject::ClassCode oc = 0,  int oo = 0,
        unsigned of = SetOperations::DEFAULT_PTR,
    	DbObject::ClassCode mc = 0, int mo = 0,
    	unsigned mf = SetOperations::DEFAULT_PTR );
    int delink( DbObject /*FAR*/ * );
    int getNext( ObjHandle & );
    int getPrior( ObjHandle & );
    int getLast( DbObject /*FAR*/ *, ObjHandle & );
    int insertAfter( DbObject /*FAR*/ *, DbObject /*FAR*/ * );
    int insertBefore( DbObject /*FAR*/ *, DbObject /*FAR*/ * );
    int getOwner( DbObject /*FAR*/ *, ObjHandle & );
    int isMember( DbObject /*FAR*/ * );
    int isOwner( DbObject /*FAR*/ * );
    int empty( DbObject /*FAR*/ * );
    int removeSet( DbObject /*FAR*/ * );
    int move( DbObject /*FAR*/ *, DbObject /*FAR*/ * );
    int commit( DbObject /*FAR*/ * );

  private :
    friend SetOperations;
    friend SetSllOwner;
    friend SetSllMember;
    friend SetDllOwner;
    friend SetDllMember;
    friend SetSllMemberOP;
    friend SetDllMemberOP;
    int member_offset;
    int owner_offset;
    DbObject::ClassCode owner_class;
    DbObject::ClassCode member_class;
    unsigned owner_ptrs;
    unsigned member_ptrs;
    int member_has_priorPtr( void );
    int owner_has_priorPtr( void );
    int member_has_ownerPtr( void );
    SetOperations /*FAR*/ *memberSetOperations( DbObject /*FAR*/ * );
    SetOperations /*FAR*/ *ownerSetOperations( DbObject /*FAR*/ * );
};


inline SetOperations /*FAR*/ *
SetRelation::memberSetOperations( DbObject /*FAR*/ *dbo )
{
  return( (SetOperations *)( (char *)dbo + this->member_offset ) );
}

inline SetOperations /*FAR*/ *SetRelation::ownerSetOperations( DbObject *dbo 
)
{
  return( (SetOperations *)( (char *)dbo + this->owner_offset ) );
}

#endif
