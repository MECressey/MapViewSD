//
//	GNISFeature.cpp - implementation for the TigerDB::GNISFeature class using the NodeEdgePoly class library.
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
#include "GNISname.h"
#include "tstring.h"

TigerDB::GNISFeature::GNISFeature(void) : GeoDB::Point()
{
	this->GeoDB::Point::Init();
	this->name.clear();
}

TigerDB::GNISFeature::~GNISFeature(void)
{
}

void TigerDB::GNISFeature::Init(void)
{
	this->GeoDB::Point::Init();
	this->name.clear();
}

std::string TigerDB::GNISFeature::GetName(void)
{
	if (this->name.empty())
	{
		TigerDB* db = (TigerDB*)((DbObject*)this)->database();

		db->nameByFeatureId->idParam = this->userId;
		db->nameByFeatureId->Requery();
		if (db->nameByFeatureId->IsEOF())
		{
			this->name.clear();
		}
		else
		{
			this->name = (const char*)TString(db->nameByFeatureId->m_name);
			while (!db->nameByFeatureId->IsEOF())
				db->nameByFeatureId->MoveNext();
		}
	}

	return this->name;
}