// SearchUserID.cpp : implementation file
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
