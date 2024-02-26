//
//	SearchUserID.h - interface of the SearchUserID class (generated by Visual Studio)
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
#pragma once
#include "afxdialogex.h"


// SearchUserID dialog

class SearchUserID : public CDialogEx
{
	DECLARE_DYNAMIC(SearchUserID)

public:
	SearchUserID(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SearchUserID();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_USERID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_UserID;
	CString m_UserIDStr;
	CEdit m_DatabaseID;
	CString m_DatabaseIDStr;
};
