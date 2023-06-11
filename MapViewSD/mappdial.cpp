// mappdial.cpp : implementation file
//

#include "pch.h"
#include "mapviewSD.h"
#include "mappdial.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MapPDIAL dialog


MapPDIAL::MapPDIAL(CWnd* pParent /*=NULL*/)
	: CDialog(MapPDIAL::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapPDIAL)
	m_projNum = -1;
	//}}AFX_DATA_INIT
/*	doNone = TRUE;
	doEquidistantCyclindrical = FALSE;*/
}


void MapPDIAL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapPDIAL)
	DDX_Radio(pDX, IDC_NO_PROJ, m_projNum);
	//}}AFX_DATA_MAP
/*	DDX_Radio( pDX, IDC_NO_PROJ, doNone );
	DDX_Radio( pDX, IDC_EQUI_CYCL, doEquidistantCyclindrical );*/
}


BEGIN_MESSAGE_MAP(MapPDIAL, CDialog)
	//{{AFX_MSG_MAP(MapPDIAL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MapPDIAL message handlers

