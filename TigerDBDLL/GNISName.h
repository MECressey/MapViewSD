#pragma once

#include <afxdb.h>

class GNISName : public CRecordset
{
public:
	CString	m_name;
	long		m_id;

	//CString	nameParam;
	long	idParam;

	GNISName(CDatabase* pDB = 0);

	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	DECLARE_DYNAMIC(GNISName)
};

