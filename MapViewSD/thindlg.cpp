// thindlg.cpp : implementation file
//

#include "pch.h"
#include "mapviewSD.h"
#include "thindlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ThinDlg dialog


ThinDlg::ThinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ThinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ThinDlg)
	m_checked = FALSE;
	m_value = _T("");
	//}}AFX_DATA_INIT
}


void ThinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ThinDlg)
	DDX_Check(pDX, IDC_CHECK1, m_checked);
	DDX_Text(pDX, IDC_EDIT1, m_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ThinDlg, CDialog)
	//{{AFX_MSG_MAP(ThinDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ThinDlg message handlers
