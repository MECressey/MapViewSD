// TigerDB.h : main header file for the TigerDB DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTigerDBApp
// See TigerDB.cpp for the implementation of this class
//

class CTigerDBApp : public CWinApp
{
public:
	CTigerDBApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
