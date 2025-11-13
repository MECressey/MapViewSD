#pragma once
#include "afxdialogex.h"
#include "ACSSurveyData.h"


// ACSQueryDialog dialog

class ACSQueryDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ACSQueryDialog)

public:
	ACSQueryDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ACSQueryDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACS_QUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_sourceList;
	std::vector<ACSSurveyData::ACSColumnRec> m_colNames;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeSourceList();
	CComboBox m_yearCombo;
	CComboBox m_colCombo,
						m_colCombo2;

private:
	int m_subjectType;
	void InitColumnList(ACSSurveyData::SubjectType subjectType);
	void SetAgeAndSexColumns();

public:
	afx_msg void OnCbnSelchangeColCombo();
	afx_msg void OnCbnSelchangeColCombo2();

	CComboBox m_sqlCompOp1,
						m_sqlCompOp2;
	CString /*m_col1,*/
		      m_value1,
				  m_value2;
	afx_msg void OnEnChangeValue1();
	CComboBox m_logOp1;
	int m_idxCol1,
		  m_idxCol2;
	ACSSurveyData::SQLComparisonOp m_idxComp1,
		  m_idxComp2;
	ACSSurveyData::SQLLogicalOp m_idxLogOp1,
		  m_idxLogOp2;
	afx_msg void OnCbnSelchangeCompOp1();
	afx_msg void OnCbnSelchangeCompOp2();
	afx_msg void OnCbnSelchangeLogicalOp();
};
