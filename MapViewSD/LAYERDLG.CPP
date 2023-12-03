// layerdlg.cpp : implementation file
//

//#include "stdafx.h"
#include "pch.h"
#include "MapViewSD.h"
#include "layerdlg.h"

/*#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif*/

/////////////////////////////////////////////////////////////////////////////
// LayerDlg dialog


LayerDlg::LayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(LayerDlg)
	doLines = TRUE;
	doOtherRds = FALSE;
	doBoundary = TRUE;
	doLocalRds = FALSE;
	doOtherFeatures = FALSE;
	doPrimaryRds = TRUE;
	doSecondaryRds = TRUE;
	doShoreline = TRUE;
	doStreams = FALSE;
	doTrails = FALSE;
	doAreas = TRUE,
	doLakesOrPonds = FALSE;
	doGNISPoints = FALSE;
	doLandForm = FALSE;
	doCoastal = FALSE;
	doCultural = FALSE;
	doCensus = FALSE;
	doOtherNames = FALSE;
	doTopographic = FALSE;
	doHydrology = FALSE;
	//}}AFX_DATA_INIT
}

void LayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LayerDlg)
	DDX_Check(pDX, IDC_LINES, doLines);
	DDX_Check(pDX, IDC_OTHER_RDS, doOtherRds);
	DDX_Check(pDX, IDC_BOUNDARY, doBoundary);
	DDX_Check(pDX, IDC_LOCAL_ROADS, doLocalRds);
	DDX_Check(pDX, IDC_OTHER_FEATURES, doOtherFeatures);
	DDX_Check(pDX, IDC_PRIMARD_RDS, doPrimaryRds);
	DDX_Check(pDX, IDC_SECONDARY_RDS, doSecondaryRds);
	DDX_Check(pDX, IDC_SHORELINE, doShoreline);
	DDX_Check(pDX, IDC_STEAMS, doStreams);
	DDX_Check(pDX, IDC_TRAILS, doTrails);
	DDX_Check(pDX, IDC_AREA, doAreas);
	DDX_Check(pDX, IDC_LAKE_POND, doLakesOrPonds);
	DDX_Check(pDX, IDC_POINT_NAMES, doGNISPoints);
	DDX_Check(pDX, IDC_LANDFORM, doLandForm);
	DDX_Check(pDX, IDC_COASTAL, doCoastal);
	DDX_Check(pDX, IDC_CULTURAL, doCultural);
	DDX_Check(pDX, IDC_CENSUS, doCensus);
	DDX_Check(pDX, IDC_OTHER_NAMES, doOtherNames);
	DDX_Check(pDX, IDC_TOPOGRAPHIC, doTopographic);
	DDX_Check(pDX, IDC_HYDROLOGY, doHydrology);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(LayerDlg, CDialog)
	//{{AFX_MSG_MAP(LayerDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// LayerDlg message handlers
