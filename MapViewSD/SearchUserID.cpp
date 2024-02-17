//
//	SearchUserID.cpp - implementation of the SearchUserID class (generated by Visual Studio)
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
#include "MapViewSD.h"
#include "afxdialogex.h"
#include "SearchUserID.h"


// SearchUserID dialog

IMPLEMENT_DYNAMIC(SearchUserID, CDialogEx)

SearchUserID::SearchUserID(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCH_USERID, pParent)
{

}

SearchUserID::~SearchUserID()
{
}

void SearchUserID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERID, m_UserID);
	DDX_Text(pDX, IDC_EDIT_USERID, m_UserIDStr);
}


BEGIN_MESSAGE_MAP(SearchUserID, CDialogEx)
END_MESSAGE_MAP()


// SearchUserID message handlers