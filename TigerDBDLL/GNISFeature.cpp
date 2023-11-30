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
			/*char buffer[256];

			::strcpy(buffer, TString(db->nameByFeatureId->m_name));
			std::string s(buffer);
			//std::string s2 = s;
			this->name = s;
			//this->name.assign();*/
			//this->name = (const char *)db->nameByFeatureId->m_name;
			this->name = (const char*)TString(db->nameByFeatureId->m_name);
			//this->name = (LPCTSTR)db->nameByFeatureId->m_name;
			//::strcpy(out->name, TString(db->nameById->m_name));
			while (!db->nameByFeatureId->IsEOF())
				db->nameByFeatureId->MoveNext();
		}
	}

	return this->name;
}