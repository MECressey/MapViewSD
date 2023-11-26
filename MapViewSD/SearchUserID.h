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
};
