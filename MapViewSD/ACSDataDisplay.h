#pragma once
#include "afxdialogex.h"

#include "GridCtrl.h"

// ACSDataDisplay dialog

class ACSDataDisplay : public CDialogEx
{
	DECLARE_DYNAMIC(ACSDataDisplay)

public:
	ACSDataDisplay(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ACSDataDisplay();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACS_DIALOG };
#endif

	CGridCtrl m_Grid;

protected:
	HICON m_hIcon;
	//CImageList m_ImageList;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
