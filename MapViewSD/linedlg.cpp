//
//	linedlg.cpp - implementation of the LineDlg class which is used to display information on edges that the user interactively selects.
//  Copyright(C) 2024 Michael E. Cressey
//
//	This program is free software : you can redistribute it and /or modify it under the terms of the
//	GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
//	implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along with this program.
//  If not, see https://www.gnu.org/licenses/
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
