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
	, m_ageCat22To24(FALSE)
	, m_ageCat25To29(FALSE)
	, m_ageCat30To34(FALSE)
	, m_ageCat35To39(FALSE)
	, m_ageCat40To44(FALSE)
	, m_ageCat45To49(FALSE)
	, m_ageCat50To54(FALSE)
	, m_ageCat55To59(FALSE)
	, m_ageCat60To61(FALSE)
	, m_ageCat62To64(FALSE)
	, m_ageCat65To66(FALSE)
	, m_ageCat67To69(FALSE)
	, m_ageCat70To74(FALSE)
	, m_ageCat75To79(FALSE)
	, m_ageCat80To84(FALSE)
	, m_ageCat85AndOver(FALSE)
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
	DDX_Radio(pDX, IDC_ALL_RACES, m_raceIteration);
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
END_MESSAGE_MAP()


// AcsSexAgeDialog message handlers


void AcsSexAgeDialog::OnBnClickedAllRaces()
{
	m_raceIteration = 0;
}


void AcsSexAgeDialog::OnBnClickedWhiteAlone()
{
	m_raceIteration = 1;
}


void AcsSexAgeDialog::OnBnClickedBlackAlone()
{
	m_raceIteration = 2;
}


void AcsSexAgeDialog::OnBnClickedIndianAlaskian()
{
	m_raceIteration = 3;
}


void AcsSexAgeDialog::OnBnClickedAsianAlone()
{
	m_raceIteration = 4;
}


void AcsSexAgeDialog::OnBnClickedHawaiianAlone()
{
	m_raceIteration = 5;
}


void AcsSexAgeDialog::OnBnClickedOtherRace()
{
	m_raceIteration = 6;
}

void AcsSexAgeDialog::OnBnClickedTwoRaces()
{
	m_raceIteration = 7;
}

void AcsSexAgeDialog::OnBnClickedNotHispanic()
{
	m_raceIteration = 8;
}


void AcsSexAgeDialog::OnBnClickedHispanicLatino()
{
	m_raceIteration = 9;
}


