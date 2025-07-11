//
//	layerdlg.cpp - implementation for the LayerDlg class which controls the layers drawn in MapViewSD.
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

//#include "stdafx.h"
#include "pch.h"
#include "MapViewSD.h"
#include "layerdlg.h"

/*#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif*/

using namespace NodeEdgePoly;

/////////////////////////////////////////////////////////////////////////////
// LayerDlg dialog
void LayerDlg::OnOK()
{
	CDialog::OnOK();
	SetUpSpatialFilter();
}

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
	doLakesOrPonds = TRUE;
	doGNISPoints = TRUE;
	doLandForm = FALSE;
	doCoastal = FALSE;
	doCultural = FALSE;
	doCensus = FALSE;
	doCivil = TRUE;
	doPP = FALSE;
	doOtherNames = FALSE;
	doTopographic = FALSE;
	doHydrology = FALSE;
	doIsland = FALSE;
	doGroundTransportation = FALSE;
	doPark = FALSE;
	doPlaces = TRUE;
	doTracts = FALSE;
	doCounties = FALSE;
	doFaces = FALSE;
	doBlkGroups = FALSE;
	doZctas = FALSE;
	//}}AFX_DATA_INIT

	SetUpSpatialFilter();
}

void LayerDlg::SetUpSpatialFilter(void)
{
	this->objClasses.reset();
	if (doLines && (doOtherRds || doBoundary || doLocalRds || doOtherFeatures || doPrimaryRds || doSecondaryRds ||
			doShoreline || doStreams || doTrails || doGroundTransportation || doFaces))
		this->objClasses.set(DB_EDGE);
	if (doGNISPoints)
		this->objClasses.set(DB_POINT);
	if (doAreas && (doLakesOrPonds || doPark || doPlaces || doTracts || doCounties || doBlkGroups || doZctas))
		this->objClasses.set(DB_POLY);
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
	DDX_Check(pDX, IDC_CIVIL, doCivil);
	DDX_Check(pDX, IDC_PP, doPP);
	DDX_Check(pDX, IDC_ISLAND, doIsland);
	DDX_Check(pDX, IDC_OTHER_NAMES, doOtherNames);
	DDX_Check(pDX, IDC_TOPOGRAPHIC, doTopographic);
	DDX_Check(pDX, IDC_HYDROLOGY, doHydrology);
	DDX_Check(pDX, IDC_GRD_TRANSPORTATION, doGroundTransportation);
	DDX_Check(pDX, IDC_PARK_POLY, doPark);
	DDX_Check(pDX, IDC_PLACE, doPlaces);
	DDX_Check(pDX, IDC_TRACTS, doTracts);
	DDX_Check(pDX, IDC_COUNTIES, doCounties);
	DDX_Check(pDX, IDC_FACES, doFaces);
	DDX_Check(pDX, IDC_BLKGRP, doBlkGroups);
	DDX_Check(pDX, IDC_ZCTA, doZctas);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(LayerDlg, CDialog)
	//{{AFX_MSG_MAP(LayerDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// LayerDlg message handlers

