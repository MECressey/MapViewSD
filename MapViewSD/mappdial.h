// mappdial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapPDIAL dialog

class MapPDIAL : public CDialog
{
// Construction
public:
	MapPDIAL(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapPDIAL)
	enum { IDD = IDD_MAP_PROJD };
	int		m_projNum;
	//}}AFX_DATA
/*
	BOOL	doNone;
	BOOL	doEquidistantCyclindrical;
*/
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapPDIAL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MapPDIAL)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};
