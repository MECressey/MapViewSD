// TigerDBDLL.h : main header file for the TigerDBDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTigerDBDLLApp
// See TigerDBDLL.cpp for the implementation of this class
//

class CTigerDBDLLApp : public CWinApp
{
public:
	CTigerDBDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
