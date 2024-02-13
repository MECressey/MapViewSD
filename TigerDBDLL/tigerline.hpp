//
//	TigerLine.hpp - declarations for the TigerLine class using the NodeEdgePoly class library.
//  Copyright(C) 2024 Michael E. Cressey
//
//	This definition is not used - see tigerdb.hpp
//
#pragma once

#include "tigerdb.hpp"

class  TigerLine : public DbLine
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

