// layerdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LayerDlg dialog

class LayerDlg : public CDialog
{
// Construction
public:
	LayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(LayerDlg)
	enum { IDD = IDD_MAP_LAYERS };
	BOOL doLines;
	BOOL	doOtherRds;
	BOOL	doBoundary;
	BOOL	doLocalRds;
	BOOL	doOtherFeatures;
	BOOL	doPrimaryRds;
	BOOL	doSecondaryRds;
	BOOL	doShoreline;
	BOOL	doStreams;
	BOOL	doTrails;
	BOOL  doAreas;
	BOOL	doLakesOrPonds;
	BOOL	doGNISPoints;
	BOOL  doLandForm;
	BOOL  doCoastal;
	BOOL  doCultural;
	BOOL  doCensus;
	BOOL  doOtherNames;
	BOOL  doTopographic;
	BOOL  doHydrology;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(LayerDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
