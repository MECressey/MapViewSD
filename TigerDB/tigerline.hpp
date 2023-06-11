///////////////////////////////////////////////////////////////////////////////
//
//	TIGERLINE.HPP - declarations for the DB Line object.
//
//	Copyright (c) 1992-1996, Object-Based Technologies, Topsham, ME, USA.
//	All rights reserved.
///////////////////////////////////////////////////////////////////////////////
#if ! defined( TIGERLINE_HPP )
#define TIGERLINE_HPP

#include "tigerdb.hpp"

class TigerLine : public DbLine
{
	public :
		class Name
		{
			public :
				Name( void );
				char prefix[ 3 ];
				char name[ 41 ];
				char type[ 5 ];
				char suffix[ 3 ];
		};
		unsigned GetNumNames( void ) const;
		void GetName( const TigerDB &, Name *, int ) const;
//
//	Used only for setting the records
		class NameRec
		{
			public :
				long nameId;
				unsigned char prefixCode;
				unsigned char suffixCode;
				unsigned char typeCode;
		};

	private :
		unsigned char nNames;
		NameRec names[ 5 ];

    void Compress( void * );
    void Decompress( void *, int );
    unsigned DiskSize( void );
};

TigerLine::Name::Name( void )
{
	this->prefix[ 0 ] = this->name[ 0 ] = this->type[ 0 ] = this->suffix[ 0 ] = '\0';
}

inline unsigned TigerLine::GetNumNames( void ) const
{
	return( this->nNames );
}


#endif
