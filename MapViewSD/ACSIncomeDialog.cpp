// ACSIncomeDialog.cpp : implementation file
//

#include "pch.h"
#include "MapViewSD.h"
#include "afxdialogex.h"
#include "ACSIncomeDialog.h"
#include "ACSSurveyData.h"

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

int ACSIncomeDialog::getIncomeCategories(void)
{
	int incomeCategories = 0;
	if (this->m_incomeTotals)
		incomeCategories = ACSSurveyData::TOTAL_INCOME;
	else
	{
		if (this->m_under10K)
			incomeCategories |= ACSSurveyData::TUnder10;
		if (this->m_10KTo14999K)
			incomeCategories |= ACSSurveyData::T10To14999;
		if (this->m_15KTo19999K)
			incomeCategories |= ACSSurveyData::T15To19999;
		if (this->m_20KTo24999K)
			incomeCategories |= ACSSurveyData::T20To24999;
		if (this->m_25KTo29999K)
			incomeCategories |= ACSSurveyData::T25To29999;
		if (this->m_30KTo34999K)
			incomeCategories |= ACSSurveyData::T30To34999;
		if (this->m_35KTo39999K)
			incomeCategories |= ACSSurveyData::T35To39999;
		if (this->m_40KTo44999K)
			incomeCategories |= ACSSurveyData::T40To44999;
		if (this->m_45KTo49999K)
			incomeCategories |= ACSSurveyData::T45To49999;
		if (this->m_50KTo59999K)
			incomeCategories |= ACSSurveyData::T50To59999;
		if (this->m_60KTo74999K)
			incomeCategories |= ACSSurveyData::T60To74999;
		if (this->m_75KTo99999K)
			incomeCategories |= ACSSurveyData::T75To99999;
		if (this->m_100KTo124999K)
			incomeCategories |= ACSSurveyData::T100To124999;
		if (this->m_125KTo14999K)
			incomeCategories |= ACSSurveyData::T125To149999;
		if (this->m_150KTo19999K)
			incomeCategories |= ACSSurveyData::T150To199999;
		if (this->m_200KAndOver)
			incomeCategories |= ACSSurveyData::T200andOver;
	}

	return incomeCategories;
}
// ACSIncomeDialog message handlers
