// linedlg.cpp : implementation file
//

#include "pch.h"
#include "mapviewSD.h"
#include "linedlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LineDlg dialog


LineDlg::LineDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(LineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(LineDlg)
	m_id = "";
	m_type = "";
	m_name = _T("");
	//}}AFX_DATA_INIT
  this->Create( LineDlg::IDD, pParent );	
}

void LineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LineDlg)
	DDX_Text(pDX, IDC_LINE_ID, m_id);
	DDX_Text(pDX, IDC_LINE_TYPE, m_type);
	DDX_Text(pDX, IDC_LINE_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(LineDlg, CDialog)
	//{{AFX_MSG_MAP(LineDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// LineDlg message handlers
