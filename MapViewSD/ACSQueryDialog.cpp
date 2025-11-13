// ACSQueryDialog.cpp : implementation file
//

#include "pch.h"
#include "MapViewSD.h"
#include "afxdialogex.h"
#include "ACSQueryDialog.h"
#include "TString.h"

// ACSQueryDialog dialog

IMPLEMENT_DYNAMIC(ACSQueryDialog, CDialogEx)

ACSQueryDialog::ACSQueryDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACS_QUERY, pParent)
	, m_value1(_T(""))
	, m_subjectType (0)
{
	m_idxCol2 = m_idxCol1 = 0;
	m_idxComp2 = m_idxComp1 = (ACSSurveyData::SQLComparisonOp)0 ;
	m_idxLogOp1 = m_idxLogOp2 = (ACSSurveyData::SQLLogicalOp)1;
}

ACSQueryDialog::~ACSQueryDialog()
{
}

void ACSQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_COMBO, m_sourceList);
	//DDX_Control(pDX, IDC_COL_LIST, m_colList);
	DDX_Control(pDX, IDC_COL_COMBO, m_colCombo);
	//DDX_Text(pDX, IDC_COL_COMBO, m_col1);
	DDX_Control(pDX, IDC_COL_COMBO2, m_colCombo2);
	DDX_Control(pDX, IDC_YEAR_COMBO, m_yearCombo);
	DDX_Control(pDX, IDC_COMP_OP1, m_sqlCompOp1);
	DDX_Control(pDX, IDC_COMP_OP2, m_sqlCompOp2);
	DDX_Text(pDX, IDC_VALUE1, m_value1);
	DDX_Text(pDX, IDC_VALUE2, m_value2);
	DDX_Control(pDX, IDC_LOGICAL_OP, m_logOp1);
	//DDX_CBString(pDX, IDC_LOGICAL_OP, m_logOp1);
}


BEGIN_MESSAGE_MAP(ACSQueryDialog, CDialogEx)
	ON_LBN_SELCHANGE(IDC_SOURCE_COMBO, &ACSQueryDialog::OnLbnSelchangeSourceList)
	ON_CBN_SELCHANGE(IDC_COL_COMBO, &ACSQueryDialog::OnCbnSelchangeColCombo)
	ON_CBN_SELCHANGE(IDC_COL_COMBO2, &ACSQueryDialog::OnCbnSelchangeColCombo2)
	ON_EN_CHANGE(IDC_VALUE1, &ACSQueryDialog::OnEnChangeValue1)
	ON_CBN_SELCHANGE(IDC_COMP_OP1, &ACSQueryDialog::OnCbnSelchangeCompOp1)
	ON_CBN_SELCHANGE(IDC_COMP_OP2, &ACSQueryDialog::OnCbnSelchangeCompOp2)
	ON_CBN_SELCHANGE(IDC_LOGICAL_OP, &ACSQueryDialog::OnCbnSelchangeLogicalOp)
END_MESSAGE_MAP()


// ACSQueryDialog message handlers


BOOL ACSQueryDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	m_sourceList.AddString(_T("Age and Sex"));
	m_sourceList.AddString(_T("Household Income"));
	m_sourceList.SetCurSel(0);

	m_yearCombo.AddString(_T("2023"));
	m_yearCombo.AddString(_T("2024"));
	m_yearCombo.SetCurSel(0);

	m_sqlCompOp1.AddString(_T(""));
	m_sqlCompOp1.AddString(_T(" = "));
	m_sqlCompOp1.AddString(_T(" < "));
	m_sqlCompOp1.AddString(_T(" <="));
	m_sqlCompOp1.AddString(_T(" > "));
	m_sqlCompOp1.AddString(_T(" >="));
	m_sqlCompOp1.AddString(_T(" <>"));
	m_sqlCompOp1.SetCurSel(0);

	m_sqlCompOp2.AddString(_T(""));
	m_sqlCompOp2.AddString(_T(" = "));
	m_sqlCompOp2.AddString(_T(" < "));
	m_sqlCompOp2.AddString(_T(" <="));
	m_sqlCompOp2.AddString(_T(" > "));
	m_sqlCompOp2.AddString(_T(" >="));
	m_sqlCompOp2.AddString(_T(" <>"));
	m_sqlCompOp2.SetCurSel(0);

	m_logOp1.AddString(_T("AND"));
	m_logOp1.AddString(_T("OR"));
	m_logOp1.SetCurSel(0);

	//SetAgeAndSexColumns();
	InitColumnList(ACSSurveyData::SEX_BY_AGE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ACSQueryDialog::InitColumnList(ACSSurveyData::SubjectType subjectType)
{
	m_subjectType = subjectType;

	m_colNames.clear();
	ACSSurveyData::GetTableColumns(m_colNames, subjectType);

	m_colCombo.ResetContent();
	m_colCombo2.ResetContent();
	switch (subjectType)
	{
	default:
		break;
	case ACSSurveyData::SEX_BY_AGE:
	case ACSSurveyData::HOUSEHOLD_INCOME_IN_THE_PAST_12MONTHS:
		m_colCombo.AddString(_T("Total"));
		m_colCombo2.AddString(_T("Total"));
		break;
	}
	for (int i = 0; i < m_colNames.size(); i++)
	{
		//LPCTSTR lpcstr = m_colNames[i].colName.c_str()
		m_colCombo.AddString(TString(m_colNames[i].colName.c_str()));
		m_colCombo2.AddString(TString(m_colNames[i].colName.c_str()));
	}

	m_colCombo.SetCurSel(0);
	m_colCombo2.SetCurSel(0);
}

void ACSQueryDialog::OnLbnSelchangeSourceList()
{
	CString sourceList;

	int nIndex = m_sourceList.GetCurSel();
	switch (nIndex)
	{
	default:
		break;

	case 0:
		InitColumnList(ACSSurveyData::SEX_BY_AGE);
		break;
	case 1:
		InitColumnList(ACSSurveyData::HOUSEHOLD_INCOME_IN_THE_PAST_12MONTHS);
		break;

	}
}

void ACSQueryDialog::SetAgeAndSexColumns()
{
	m_colCombo.ResetContent();

	m_colCombo.AddString(_T("Total"));
	m_colCombo.AddString(_T("Under5"));
	m_colCombo.AddString(_T("5To9"));
	m_colCombo.AddString(_T("10To14"));
	m_colCombo.AddString(_T("15To17"));
	m_colCombo.AddString(_T("18To19"));
	m_colCombo.AddString(_T("20"));
	m_colCombo.AddString(_T("21"));
	m_colCombo.AddString(_T("22To24"));
	m_colCombo.AddString(_T("25To29"));
	m_colCombo.AddString(_T("30To34"));
	m_colCombo.AddString(_T("35To39"));
	m_colCombo.AddString(_T("40To44"));
	m_colCombo.AddString(_T("45To49"));
	m_colCombo.AddString(_T("50To54"));
	m_colCombo.AddString(_T("55To59"));
	m_colCombo.AddString(_T("60To61"));
	m_colCombo.AddString(_T("62To64"));
	m_colCombo.AddString(_T("67To69"));
	m_colCombo.AddString(_T("70To74"));
	m_colCombo.AddString(_T("75To79"));
	m_colCombo.AddString(_T("80To84"));
	m_colCombo.AddString(_T("85AndOVER"));

	m_colCombo.SetCurSel(0);

	m_colCombo2.ResetContent();

	m_colCombo2.AddString(_T("Total"));
	m_colCombo2.AddString(_T("Under5"));
	m_colCombo2.AddString(_T("5To9"));
	m_colCombo2.AddString(_T("10To14"));
	m_colCombo2.AddString(_T("15To17"));
	m_colCombo2.AddString(_T("18To19"));
	m_colCombo2.AddString(_T("20"));
	m_colCombo2.AddString(_T("21"));
	m_colCombo2.AddString(_T("22To24"));
	m_colCombo2.AddString(_T("25To29"));
	m_colCombo2.AddString(_T("30To34"));
	m_colCombo2.AddString(_T("35To39"));
	m_colCombo2.AddString(_T("40To44"));
	m_colCombo2.AddString(_T("45To49"));
	m_colCombo2.AddString(_T("50To54"));
	m_colCombo2.AddString(_T("55To59"));
	m_colCombo2.AddString(_T("60To61"));
	m_colCombo2.AddString(_T("62To64"));
	m_colCombo2.AddString(_T("67To69"));
	m_colCombo2.AddString(_T("70To74"));
	m_colCombo2.AddString(_T("75To79"));
	m_colCombo2.AddString(_T("80To84"));
	m_colCombo2.AddString(_T("85AndOVER"));

	m_colCombo2.SetCurSel(0);
}

void ACSQueryDialog::OnCbnSelchangeColCombo()
{
	m_idxCol1 = m_colCombo.GetCurSel();
}

void ACSQueryDialog::OnCbnSelchangeColCombo2()
{
	m_idxCol2 = m_colCombo2.GetCurSel();
}


void ACSQueryDialog::OnEnChangeValue1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void ACSQueryDialog::OnCbnSelchangeCompOp1()
{
	m_idxComp1 = (ACSSurveyData::SQLComparisonOp)(m_sqlCompOp1.GetCurSel()/* + 1*/);
}

void ACSQueryDialog::OnCbnSelchangeCompOp2()
{
	m_idxComp2 = (ACSSurveyData::SQLComparisonOp)(m_sqlCompOp2.GetCurSel()/* + 1*/);
}


void ACSQueryDialog::OnCbnSelchangeLogicalOp()
{
	m_idxLogOp1 = (ACSSurveyData::SQLLogicalOp)(m_logOp1.GetCurSel() + 1);
}
