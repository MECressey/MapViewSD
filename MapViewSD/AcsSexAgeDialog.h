#pragma once
#include "afxdialogex.h"


// AcsSexAgeDialog dialog

class AcsSexAgeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AcsSexAgeDialog)

public:
	AcsSexAgeDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AcsSexAgeDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACS_AGESEX_QUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_maleSex;
	BOOL m_femaleSex;
	BOOL m_sexesCombined;
	BOOL m_ageCatTotals;
	BOOL m_ageCatUnder5;
	BOOL m_ageCat5To9;
	BOOL m_ageCat10To14;
	BOOL m_ageCat15To17;
	BOOL m_ageCat18To19;
	BOOL m_ageCat20;
	CButton m_ageCat21;
	BOOL m_ageCat22To24;
	BOOL m_ageCat25To29;
	BOOL m_ageCat30To34;
	BOOL m_ageCat35To39;
	BOOL m_ageCat40To44;
	BOOL m_ageCat45To49;
	BOOL m_ageCat50To54;
	BOOL m_ageCat50To59;
	BOOL m_ageCat60To61;
	BOOL m_ageCat62To64;
	BOOL m_ageCat65To66;
	BOOL m_ageCat67To69;
	BOOL m_ageCat70To74;
	BOOL m_ageCat75To79;
	BOOL m_ageCat80To84;
	BOOL m_ageCat85AndOver;
	int m_raceIteration;
	afx_msg void OnBnClickedAllRaces();
	afx_msg void OnBnClickedWhiteAlone();
	afx_msg void OnBnClickedBlackAlone();
	afx_msg void OnBnClickedIndianAlaskian();
	afx_msg void OnBnClickedAsianAlone();
	afx_msg void OnBnClickedHawaiianAlone();
	afx_msg void OnBnClickedOtherRace();
	afx_msg void OnBnClickedNotHispanic();
	afx_msg void OnBnClickedHispanicLatino();
	afx_msg void OnBnClickedTwoRaces();
};
