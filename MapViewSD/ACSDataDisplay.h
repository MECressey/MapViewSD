#pragma once
#include "afxdialogex.h"

#include <vector>
#include <map>
#include "GridCtrl.h"

// ACSDataDisplay dialog

class ACSDataDisplay : public CDialogEx
{
	DECLARE_DYNAMIC(ACSDataDisplay)

public:
	ACSDataDisplay(std::vector<CString> &headers, std::multimap<int, std::vector<int>> &rows, CWnd* pParent = nullptr);   // standard constructor
	virtual ~ACSDataDisplay();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACS_DIALOG };
#endif

	CGridCtrl m_Grid;

protected:
	std::vector<CString>& m_headers;
	std::multimap<int, std::vector<int>>& m_rows;

	HICON m_hIcon;
	CImageList m_ImageList;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
