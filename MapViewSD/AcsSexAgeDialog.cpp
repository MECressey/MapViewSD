// AcsSexAgeDialog.cpp : implementation file
//

#include "pch.h"
#include "MapViewSD.h"
#include "afxdialogex.h"
#include "AcsSexAgeDialog.h"


// AcsSexAgeDialog dialog

IMPLEMENT_DYNAMIC(AcsSexAgeDialog, CDialogEx)

AcsSexAgeDialog::AcsSexAgeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACS_AGESEX_QUERY, pParent)
	, m_maleSex(FALSE)
	, m_femaleSex(FALSE)
	, m_sexesCombined(TRUE)
	, m_ageCatTotals(TRUE)
	, m_ageCat5To9(FALSE)
	, m_ageCatUnder5(FALSE)
	, m_ageCat10To14(FALSE)
	, m_ageCat15To17(FALSE)
	, m_ageCat18To19(FALSE)
	, m_ageCat20(FALSE)
	, m_ageCat21(FALSE)
	, m_ageCat20To24(FALSE) 	// Race iteration
	, m_ageCat22To24(FALSE)
	, m_ageCat25To29(FALSE)
	, m_ageCat30To34(FALSE)
	, m_ageCat35To39(FALSE)
	, m_ageCat35To44(FALSE) 	// Race Iteration
	, m_ageCat40To44(FALSE)
	, m_ageCat45To49(FALSE)
	, m_ageCat45To54(FALSE) 	// Race Iteration
	, m_ageCat50To54(FALSE)
	, m_ageCat55To59(FALSE)
	, m_ageCat55To64(FALSE) 	// Race iteration
	, m_ageCat60To61(FALSE)
	, m_ageCat62To64(FALSE)
	, m_ageCat65To66(FALSE)
	, m_ageCat65To74(FALSE) 	// Race iteration
	, m_ageCat67To69(FALSE)
	, m_ageCat70To74(FALSE)
	, m_ageCat75To79(FALSE)
	, m_ageCat75To84(FALSE) 	// Race iteration
	, m_ageCat80To84(FALSE)
	, m_ageCat85AndOver(FALSE)
	, m_showMOE(FALSE)
	, m_raceIteration(0)
{

}

AcsSexAgeDialog::~AcsSexAgeDialog()
{
}

void AcsSexAgeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_MALE, m_maleSex);
	DDX_Check(pDX, IDC_CHECK_FEMALE, m_femaleSex);
	DDX_Check(pDX, IDC_CHECK_COMBINED, m_sexesCombined);
	DDX_Check(pDX, IDC_CHECK_TOTALS, m_ageCatTotals);
	DDX_Check(pDX, IDC_UNDER5, m_ageCatUnder5);
	DDX_Check(pDX, IDC_5TO9, m_ageCat5To9);
	DDX_Check(pDX, IDC_10TO14, m_ageCat10To14);
	DDX_Check(pDX, IDC_15TO17, m_ageCat15To17);
	DDX_Check(pDX, IDC_18TO19, m_ageCat18To19);
	DDX_Check(pDX, IDC_20, m_ageCat20);
	DDX_Check(pDX, IDC_21, m_ageCat21);
	DDX_Check(pDX, IDC_22TO24, m_ageCat22To24);
	DDX_Check(pDX, IDC_25TO29, m_ageCat25To29);
	DDX_Check(pDX, IDC_30TO34, m_ageCat30To34);
	DDX_Check(pDX, IDC_35TO39, m_ageCat35To39);
	DDX_Check(pDX, IDC_40TO44, m_ageCat40To44);
	DDX_Check(pDX, IDC_45TO49, m_ageCat45To49);
	DDX_Check(pDX, IDC_50TO54, m_ageCat50To54);
	DDX_Check(pDX, IDC_50TO59, m_ageCat55To59);
	DDX_Check(pDX, IDC_60TO61, m_ageCat60To61);
	DDX_Check(pDX, IDC_62TO64, m_ageCat62To64);
	DDX_Check(pDX, IDC_65TO66, m_ageCat65To66);
	DDX_Check(pDX, IDC_67TO69, m_ageCat67To69);
	DDX_Check(pDX, IDC_70TO74, m_ageCat70To74);
	DDX_Check(pDX, IDC_75TO79, m_ageCat75To79);
	DDX_Check(pDX, IDC_80TO84, m_ageCat80To84);
	DDX_Check(pDX, IDC_85AndOVER, m_ageCat85AndOver);
	DDX_Check(pDX, IDC_MOE, m_showMOE);
	DDX_Radio(pDX, IDC_ALL_RACES, m_raceIteration);
}

BOOL AcsSexAgeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// This is required to get the checkboxes in their correct state
	if (m_raceIteration != 0)
		SwitchToRaceIteration();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(AcsSexAgeDialog, CDialogEx)
	ON_BN_CLICKED(IDC_ALL_RACES, &AcsSexAgeDialog::OnBnClickedAllRaces)
	ON_BN_CLICKED(IDC_WHITE_ALONE, &AcsSexAgeDialog::OnBnClickedWhiteAlone)
	ON_BN_CLICKED(IDC_BLACK_ALONE, &AcsSexAgeDialog::OnBnClickedBlackAlone)
	ON_BN_CLICKED(IDC_INDIAN_ALASKIAN, &AcsSexAgeDialog::OnBnClickedIndianAlaskian)
	ON_BN_CLICKED(IDC_ASIAN_ALONE, &AcsSexAgeDialog::OnBnClickedAsianAlone)
	ON_BN_CLICKED(IDC_HAWAIIAN_ALONE, &AcsSexAgeDialog::OnBnClickedHawaiianAlone)
	ON_BN_CLICKED(IDC_OTHER_RACE, &AcsSexAgeDialog::OnBnClickedOtherRace)
	ON_BN_CLICKED(IDC_NOT_HISPANIC, &AcsSexAgeDialog::OnBnClickedNotHispanic)
	ON_BN_CLICKED(IDC_HISPANIC_LATINO, &AcsSexAgeDialog::OnBnClickedHispanicLatino)
	ON_BN_CLICKED(IDC_TWO_RACES, &AcsSexAgeDialog::OnBnClickedTwoRaces)
	ON_BN_CLICKED(IDC_CHECK_COMBINED, &AcsSexAgeDialog::OnBnClickedCheckCombined)
	ON_BN_CLICKED(IDC_CHECK_FEMALE, &AcsSexAgeDialog::OnBnClickedCheckFemale)
	ON_BN_CLICKED(IDC_CHECK_MALE, &AcsSexAgeDialog::OnBnClickedCheckMale)
END_MESSAGE_MAP()

void AcsSexAgeDialog::SwitchToAllRaces()
{
	CWnd* button = GetDlgItem(IDC_20);
	assert(button != nullptr);
	button->EnableWindow();

	button = GetDlgItem(IDC_21);
	button->EnableWindow();

	button = GetDlgItem(IDC_22TO24);
	button->SetWindowText(_T("22 to 24"));

	button = GetDlgItem(IDC_35TO39);
	button->SetWindowText(_T("35 to 39"));

	button = GetDlgItem(IDC_40TO44);
	button->EnableWindow();

	button = GetDlgItem(IDC_45TO49);
	button->SetWindowText(_T("45 to 49"));

	button = GetDlgItem(IDC_50TO54);
	button->EnableWindow();

	button = GetDlgItem(IDC_55TO59);
	button->SetWindowText(_T("55 to 59"));

	button = GetDlgItem(IDC_60TO61);
	button->EnableWindow();
	button = GetDlgItem(IDC_62TO64);
	button->EnableWindow();

	button = GetDlgItem(IDC_65TO66);
	button->SetWindowText(_T("65 to 66"));

	button = GetDlgItem(IDC_67TO69);
	button->EnableWindow();

	button = GetDlgItem(IDC_75TO79);
	button->SetWindowText(_T("75 to 79"));

	button = GetDlgItem(IDC_70TO74);
	button->EnableWindow();

	button = GetDlgItem(IDC_80TO84);
	button->EnableWindow();
}

void AcsSexAgeDialog::SwitchToRaceIteration()
{
	CWnd* button = GetDlgItem(IDC_20);
	assert(button != nullptr);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_21);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_22TO24);
	button->SetWindowText(_T("20 to 24"));

	button = GetDlgItem(IDC_21);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_35TO39);
	button->SetWindowText(_T("35 to 44"));

	button = GetDlgItem(IDC_40TO44);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_45TO49);
	button->SetWindowText(_T("45 to 54"));

	button = GetDlgItem(IDC_50TO54);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_55TO59);
	button->SetWindowText(_T("55 to 64"));

	button = GetDlgItem(IDC_60TO61);
	button->EnableWindow(0);
	button = GetDlgItem(IDC_62TO64);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_65TO66);
	button->SetWindowText(_T("65 to 74"));

	button = GetDlgItem(IDC_67TO69);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_75TO79);
	button->SetWindowText(_T("75 to 84"));

	button = GetDlgItem(IDC_70TO74);
	button->EnableWindow(0);

	button = GetDlgItem(IDC_80TO84);
	button->EnableWindow(0);
}

// AcsSexAgeDialog message handlers


void AcsSexAgeDialog::OnBnClickedAllRaces()
{
	if (m_raceIteration != 0)
		SwitchToAllRaces();
	m_raceIteration = 0;
}


void AcsSexAgeDialog::OnBnClickedWhiteAlone()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 1;
}


void AcsSexAgeDialog::OnBnClickedBlackAlone()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 2;
}


void AcsSexAgeDialog::OnBnClickedIndianAlaskian()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 3;
}


void AcsSexAgeDialog::OnBnClickedAsianAlone()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 4;
}


void AcsSexAgeDialog::OnBnClickedHawaiianAlone()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 5;
}


void AcsSexAgeDialog::OnBnClickedOtherRace()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 6;
}

void AcsSexAgeDialog::OnBnClickedTwoRaces()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 7;
}

void AcsSexAgeDialog::OnBnClickedNotHispanic()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 8;
}


void AcsSexAgeDialog::OnBnClickedHispanicLatino()
{
	if (m_raceIteration == 0)
		SwitchToRaceIteration();
	m_raceIteration = 9;
}


void AcsSexAgeDialog::OnBnClickedCheckCombined()
{
	CButton* button = (CButton*)GetDlgItem(IDC_CHECK_COMBINED);
	UINT nCheck = button->GetState();

	button = (CButton*)GetDlgItem(IDC_CHECK_MALE);
	if ((nCheck & BST_CHECKED) != 0)
	{
		button->SetCheck(BST_UNCHECKED);

		//button->EnableWindow(0);
		button = (CButton*)GetDlgItem(IDC_CHECK_FEMALE);
		button->SetCheck(BST_UNCHECKED);
		//button->EnableWindow(0);
	}
	else
	{
		button->SetCheck(BST_CHECKED);			// Enable just Male for now (could do Female as well?)
/*		button->EnableWindow();
		button = (CButton*)GetDlgItem(IDC_CHECK_FEMALE);
		button->EnableWindow();*/
	}
	/*
	CButton* button = (CButton *)GetDlgItem(IDC_CHECK_MALE);


	button = (CButton*)GetDlgItem(IDC_CHECK_FEMALE);
	button->SetCheck(BST_UNCHECKED);
	*/
}


void AcsSexAgeDialog::OnBnClickedCheckFemale()
{
	CButton* button = (CButton*)GetDlgItem(IDC_CHECK_FEMALE);
	UINT nCheck = button->GetState();

	button = (CButton*)GetDlgItem(IDC_CHECK_COMBINED);
	if ((nCheck & BST_CHECKED) != 0)
		button->SetCheck(BST_UNCHECKED);
	else
	{
		CButton* button2 = (CButton*)GetDlgItem(IDC_CHECK_MALE);
		nCheck = button2->GetState();
		if ((nCheck & BST_CHECKED) == 0)
			button->SetCheck(BST_CHECKED);
	}
}


void AcsSexAgeDialog::OnBnClickedCheckMale()
{
	CButton* button = (CButton*)GetDlgItem(IDC_CHECK_MALE);
	UINT nCheck = button->GetState();

	button = (CButton*)GetDlgItem(IDC_CHECK_COMBINED);
	if ((nCheck & BST_CHECKED) != 0)
		button->SetCheck(BST_UNCHECKED);
	else
	{
		CButton* button2 = (CButton*)GetDlgItem(IDC_CHECK_FEMALE);
		nCheck = button2->GetState();
		if ((nCheck & BST_CHECKED) == 0)
			button->SetCheck(BST_CHECKED);
	}
}
