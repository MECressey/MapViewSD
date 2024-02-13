//
//	TigerPoly.cpp - implementation for the Polygon class using the NodeEdgePoly class library.
//  Copyright(C) 2024 Michael E. Cressey
//
//	This program is free software : you can redistribute it and /or modify it under the terms of the
//	GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
//	implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along with this program.
//  If not, see https://www.gnu.org/licenses/
//
#include "pch.h"
#include <assert.h>

#include "tigerdb.hpp"

TigerDB::Polygon::Polygon(void) : GeoDB::Poly()
{
	this->GeoDB::Poly::Init();
	memset(this->name, '\0', sizeof(this->name));
}

TigerDB::Polygon::~Polygon(void)
{
}

void TigerDB::Polygon::Init(void)
{
	this->GeoDB::Poly::Init();
	memset(this->name, '\0', sizeof(this->name));
}

unsigned TigerDB::Polygon::DiskSize(void)
{
	unsigned size = this->GeoDB::Poly::DiskSize();
	size += sizeof(this->name);

	return(size);
}

void TigerDB::Polygon::Compress(void* obj)
{
	char* to = (char*)obj;

	this->GeoDB::Poly::Compress(to);
	to += this->GeoDB::Poly::DiskSize();

	memcpy(to, this->name, sizeof(this->name));
}

void TigerDB::Polygon::Decompress(void* obj, int size)
{
	char* from = (char*)obj;

	this->GeoDB::Poly::Decompress(from, size);
	from += this->GeoDB::Poly::DiskSize();

	memcpy(this->name, from, sizeof(this->name));
}

void TigerDB::Polygon::SetName(std::string name)
{
	size_t len = name.length();

	if (len > sizeof(this->name))
		len = sizeof(this->name) - 1;

	::strncpy_s(this->name, name.c_str(), len);
	this->name[len] = '\0';

}

std::string TigerDB::Polygon::GetName() const
{
	std::string str(this->name);

	return str;
}
