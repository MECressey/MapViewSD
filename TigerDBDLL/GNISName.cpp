#include "pch.h"

#include "GNISname.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(GNISName, CRecordset)

GNISName::GNISName(CDatabase* pDB) : CRecordset(pDB)
{
	//{{AFX_FIELD_INIT(GNISName)
	m_name = _T("");
	m_id = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT

	//this->nameParam = _T("");
	this->idParam = 0;
	//	this->m_strFilter = "(NAME = ?)";
	this->m_nParams = 1;
}

CString GNISName::GetDefaultConnect()
{
	return CString("ODBC;DSN=TigerData;");
}

CString GNISName::GetDefaultSQL()
{
	return(_T("GNISNames"));
}

void GNISName::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(GNISName)
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, _T("name"), this->m_name);
	RFX_Long(pFX, _T("feature_id"), this->m_id);
	//}}AFX_FIELD_MAP

	if (!this->m_strFilter.IsEmpty())
	{
		pFX->SetFieldType(CFieldExchange::param);

		/*if (this->m_strFilter == "(NAME = ?)")
			RFX_Text(pFX, _T("name"), this->nameParam);
		else*/
			RFX_Long(pFX, _T("feature_id"), this->idParam);
	}
}
