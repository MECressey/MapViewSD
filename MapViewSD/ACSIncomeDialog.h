#pragma once
#include "afxdialogex.h"


// ACSIncomeDialog dialog

class ACSIncomeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ACSIncomeDialog)

public:
	ACSIncomeDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ACSIncomeDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACS_INCOME_QUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_incomeTotals;
	BOOL m_includeMOE;
	BOOL m_under10K;
	BOOL m_10KTo14999K;
	BOOL m_15KTo19999K;
	BOOL m_20KTo24999K;
	BOOL m_25KTo29999K;
	BOOL m_30KTo34999K;
	BOOL m_35KTo39999K;
	BOOL m_40KTo44999K;
	BOOL m_45KTo49999K;
	BOOL m_50KTo59999K;
	BOOL m_60KTo74999K;
	BOOL m_75KTo99999K;
	BOOL m_100KTo124999K;
	BOOL m_125KTo14999K;
	BOOL m_150KTo19999K;
	BOOL m_200KAndOver;
	BOOL m_allIncomeCategories;
	BOOL m_raceIteration;
	CComboBox m_summaryLevels;
	virtual BOOL OnInitDialog();
};
