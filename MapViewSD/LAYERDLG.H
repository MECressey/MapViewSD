//
//	layerdlg.h - declarations for the LayerDlg class which controls the layers drawn in MapViewSD.
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
#include "GEODB.HPP"

/////////////////////////////////////////////////////////////////////////////
// LayerDlg dialog
class LayerDlg : public CDialog
{
// Construction
public:
	NodeEdgePoly::GeoDB::searchClasses_t objClasses;
	LayerDlg(CWnd* pParent = NULL);	// standard constructor
	void OnOK();

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
	BOOL	doFaces;
	BOOL doAreas;
	BOOL	doLakesOrPonds;
	BOOL  doPark;
	BOOL  doPlaces;
	BOOL	doTracts;
	BOOL	doCounties;
	BOOL  doGNISPoints;
	BOOL  doLandForm;
	BOOL  doCoastal;
	BOOL  doCultural;
	BOOL  doCensus;
	BOOL  doOtherNames;
	BOOL  doTopographic;
	BOOL  doHydrology;
	BOOL	doGroundTransportation;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(LayerDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetUpSpatialFilter(void);
public:
};
