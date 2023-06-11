// thindlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ThinDlg dialog

class ThinDlg : public CDialog
{
// Construction
public:
	ThinDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ThinDlg)
	enum { IDD = IDD_THINING };
	BOOL	m_checked;
	CString	m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ThinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ThinDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
