// ACSIncomeDialog.cpp : implementation file
//

#include "pch.h"
#include "MapViewSD.h"
#include "afxdialogex.h"
#include "ACSIncomeDialog.h"


// ACSIncomeDialog dialog

IMPLEMENT_DYNAMIC(ACSIncomeDialog, CDialogEx)

ACSIncomeDialog::ACSIncomeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACS_INCOME_QUERY, pParent)
	, m_incomeTotals(FALSE)
	, m_includeMOE(FALSE)
	, m_under10K(FALSE)
	, m_10KTo14999K(FALSE)
	, m_15KTo19999K(FALSE)
	, m_20KTo24999K(FALSE)
	, m_25KTo29999K(FALSE)
	, m_30KTo34999K(FALSE)
	, m_35KTo39999K(FALSE)
	, m_40KTo44999K(FALSE)
	, m_45KTo49999K(FALSE)
	, m_50KTo59999K(FALSE)
	, m_60KTo74999K(FALSE)
	, m_75KTo99999K(FALSE)
	, m_100KTo124999K(FALSE)
	, m_125KTo14999K(FALSE)
	, m_150KTo19999K(FALSE)
	, m_200KAndOver(FALSE)
	, m_allIncomeCategories(FALSE)
	, m_raceIteration(FALSE)
{

}

ACSIncomeDialog::~ACSIncomeDialog()
{
}

void ACSIncomeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_INCOME_TOTALS, m_incomeTotals);
	DDX_Check(pDX, IDC_INCOME_MOE, m_includeMOE);
	DDX_Check(pDX, IDC_UNDER10K, m_under10K);
	DDX_Check(pDX, IDC_10To14999, m_10KTo14999K);
	DDX_Check(pDX, IDC_15TO19999, m_15KTo19999K);
	DDX_Check(pDX, IDC_20To24999, m_20KTo24999K);
	DDX_Check(pDX, IDC_25To29999, m_25KTo29999K);
	DDX_Check(pDX, IDC_30To34999, m_30KTo34999K);
	DDX_Check(pDX, IDC_35To39999, m_35KTo39999K);
	DDX_Check(pDX, IDC_40To44999, m_40KTo44999K);
	DDX_Check(pDX, IDC_45To49999, m_45KTo49999K);
	DDX_Check(pDX, IDC_50To59999, m_50KTo59999K);
	DDX_Check(pDX, IDC_60To74999, m_60KTo74999K);
	DDX_Check(pDX, IDC_75To99999, m_75KTo99999K);
	DDX_Check(pDX, IDC_100To124999, m_100KTo124999K);
	DDX_Check(pDX, IDC_125To149999, m_125KTo14999K);
	DDX_Check(pDX, IDC_150To199999, m_150KTo19999K);
	DDX_Check(pDX, IDC_200AndOver, m_200KAndOver);
	DDX_Check(pDX, IDC_ALL_INCOMES, m_allIncomeCategories);
	DDX_Radio(pDX, IDC_ALL_RACES, m_raceIteration);
	DDX_Control(pDX, IDC_SUMMARY_LEVEL, m_summaryLevels);
}


BEGIN_MESSAGE_MAP(ACSIncomeDialog, CDialogEx)
END_MESSAGE_MAP()

BOOL ACSIncomeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	m_summaryLevels.AddString(_T("State"));
	m_summaryLevels.AddString(_T("County"));
	m_summaryLevels.AddString(_T("Tract"));
	m_summaryLevels.AddString(_T("Block Group"));
	m_summaryLevels.SetCurSel(2);

	return TRUE;
}
// ACSIncomeDialog message handlers
