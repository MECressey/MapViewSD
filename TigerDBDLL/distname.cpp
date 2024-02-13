//
//	DistNames.h - implementation for the DistNames class using the MFC CRecordset.
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

#include "distname.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(DistNames, CRecordset)

DistNames::DistNames( CDatabase* pDB )
	: CRecordset( pDB )
{
	//{{AFX_FIELD_INIT(DistNames)
	m_name = _T("");
	m_id	 = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT

	this->nameParam = _T("");
	this->idParam = 0;
//	this->m_strFilter = "(NAME = ?)";
	this->m_nParams = 1;
}

CString DistNames::GetDefaultConnect()
{
	return CString("ODBC;DSN=TigerBase;");
}

CString DistNames::GetDefaultSQL()
{
	return( _T( "DISTNAMES" ) );
}

void DistNames::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(DistNames)
	pFX->SetFieldType( CFieldExchange::outputColumn );

  RFX_Text( pFX, _T("name"), this->m_name );
	RFX_Long(pFX, _T("ID"), this->m_id );
	//}}AFX_FIELD_MAP

  if( ! this->m_strFilter.IsEmpty() )
  {
		pFX->SetFieldType( CFieldExchange::param );
	  
		if( this->m_strFilter == "(NAME = ?)" )
		  RFX_Text( pFX, _T("name"), this->nameParam );
		else
			RFX_Long( pFX, _T("id"), this->idParam );
  }
}
