// linedlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LineDlg dialog

class LineDlg : public CDialog
{
// Construction
public:
	LineDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(LineDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_id;
	CString	m_type;
	CString	m_name;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(LineDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
