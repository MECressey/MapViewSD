//
//	mappdial.cpp - implementation of the MapPDIAL class which has some map projections
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

