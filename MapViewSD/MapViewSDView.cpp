
// MapViewSDView.cpp : implementation of the CMapViewSDView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MapViewSD.h"
#endif
#include "mapviewSD.h"
#include "MainFrm.h"

#include "MapViewSDDoc.h"
#include "MapViewSDView.h"

#include "dbsearch.hpp"
#include "lineseg.hpp"
#include "drawline.hpp"
#include "mappdial.h"
#include "thindlg.h"
#include "trendlin.h"

#include "TString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapViewSDView

IMPLEMENT_DYNCREATE(CMapViewSDView, CView)

BEGIN_MESSAGE_MAP(CMapViewSDView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMapViewSDView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_COMMAND(ID_ZOOM_DOWN, OnPanDown)
	ON_COMMAND(ID_ZOOM_LEFT, OnPanLeft)
	ON_COMMAND(ID_ZOOM_RIGHT, OnPanRight)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ZOOM_UP, OnPanUp)
	ON_COMMAND(ID_MAP_LAYERS, OnMapLayers)
	ON_UPDATE_COMMAND_UI(ID_MAP_LAYERS, OnUpdateMapLayers)
	ON_COMMAND(ID_VIEW_LINEINFO, OnLineInfo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LINEINFO, OnUpdateLineInfo)
	ON_COMMAND(ID_MAP_PROJECTION, OnMapProj)
	ON_COMMAND(ID_MAP_THINING, OnThinPts)
END_MESSAGE_MAP()

static const char* LineStr(int code)
{
	const char* str;

	switch (code)
	{
	default:
	case TigerDB::NotClassified:
		str = "Feature not classified";
		break;

	case TigerDB::ROAD_MajorCategoryUnknown:
		str = "Road: categories unknown";
		break;

	case TigerDB::ROAD_PrimaryLimitedAccess:
		str = "Primary Road: Interstate highway";
		break;

	case TigerDB::ROAD_PrimaryUnlimitedAccess:
		str = "Primary Road: US/State highway";
		break;

	case TigerDB::ROAD_SecondaryAndConnecting:
		str = "Secondary Road: State/county highway";
		break;

	case TigerDB::ROAD_LocalNeighborhoodAndRural:
		str = "Local Road: city street/rural road";
		break;

	case TigerDB::ROAD_VehicularTrail:
		str = "Trail";
		break;

	case TigerDB::ROAD_AccessRamp:
		str = "Access ramp";
		break;

	case TigerDB::ROAD_SpecialCharacteristics:
	case TigerDB::ROAD_Cul_de_sac:
	case TigerDB::ROAD_TrafficCircle:
	case TigerDB::ROAD_OtherThoroughfare:
	case TigerDB::ROAD_ServiceDrive:
		str = "Road: other";
		break;

	case TigerDB::ROAD_FerryCrossing:
		str = "Ferry crossing";
		break;

	case TigerDB::RR_MajorCategoryUnknown:
	case TigerDB::RR_MainLine:
	case TigerDB::RR_Spur:
		str = "Railroad";
		break;

	case TigerDB::RR_Yard:
	case TigerDB::RR_SpecialCharacteristics:
	case TigerDB::RR_OtherThoroughfare:
		str = "Railroad: other";
		break;

	case TigerDB::MGT_CategoryUnknown:
	case TigerDB::MGT_Pipeline:
	case TigerDB::MGT_PowerLine:
	case TigerDB::MGT_SpecialCharacteristics:
		str = "Ground transportation";
		break;

	case TigerDB::LM_CategoryUnknown:
	case TigerDB::LM_MilitaryInstallation:
	case TigerDB::LM_MultihouseholdOrTransientQuarters:
	case TigerDB::LM_ApartmentBuildingOrBoardingHouse:
	case TigerDB::LM_MobileHomePark:
	case TigerDB::LM_Marina:
	case TigerDB::LM_CrewOfVessel:
	case TigerDB::LM_HotelOrMotel:
	case TigerDB::LM_Campground:
	case TigerDB::LM_ShelterOrMission:
	case TigerDB::LM_CustodialFacility:
	case TigerDB::LM_Hospital:
	case TigerDB::LM_HalfwayHouse:
	case TigerDB::LM_NursingHome:
	case TigerDB::LM_CountyHome:
	case TigerDB::LM_Orphanage:
	case TigerDB::LM_Jail:
	case TigerDB::LM_FederalOrStatePrison:
	case TigerDB::LM_EducationalOrReligiousInstitution:
	case TigerDB::LM_SororityOrFraternity:
	case TigerDB::LM_ConventOrMonastery:
	case TigerDB::LM_EducationalInstitution:
	case TigerDB::LM_ReligiousInstitution:
	case TigerDB::LM_TransportationTerminal:
	case TigerDB::LM_Airport:
	case TigerDB::LM_TrainStation:
	case TigerDB::LM_BusTerminal:
	case TigerDB::LM_MarineTerminal:
	case TigerDB::LM_SeaplaneAnchorage:
	case TigerDB::LM_Employmentcenter:
	case TigerDB::LM_ShoppingOrRetailCenter:
	case TigerDB::LM_IndustrialBuildingOrPark:
	case TigerDB::LM_OfficebuildingOrPark:
	case TigerDB::LM_AmusementCenter:
	case TigerDB::LM_GovernmentCenter:
	case TigerDB::LM_OtherEmploymentCenter:
	case TigerDB::LM_Tower:
	case TigerDB::LM_LookoutTower:
	case TigerDB::LM_OpenSpace:
	case TigerDB::LM_GolfCourse:
	case TigerDB::LM_Cemetery:
	case TigerDB::LM_NationalParkOrForest:
	case TigerDB::LM_OtherFederalLand:
	case TigerDB::LM_StateOrLocalPark_Forest:
	case TigerDB::LM_SpecialPurpose:
		str = "Land Mark features";
		break;

	case TigerDB::PF_CategoryUnknown:
	case TigerDB::PF_Fenceline:
	case TigerDB::PF_TopographicFeature:
	case TigerDB::PF_RidgeLine:
	case TigerDB::PF_MountainPeak:
		str = "Physical features";
		break;

	case TigerDB::NVF_BoundaryClassificationUnknown:
	case TigerDB::NVF_LegalOrAdministrativeBoundary:
		str = "Jurisdictional boundary";
		break;

	case TigerDB::NVF_ClosureExtension:
	case TigerDB::NVF_SeparationLine:
	case TigerDB::NVF_Centerline:
		str = "Closure extension";
		break;

	case TigerDB::NVF_PropertyLine:
		str = "Property line";
		break;

	case TigerDB::NVF_ZIPCodeBoundary:
	case TigerDB::NVF_StatisticalBoundary:
	case TigerDB::NVF_OtherTabulationBoundary:
	case TigerDB::NVF_WaterAreaDefinitionBoundary:
	case TigerDB::NVF_USGSClosureLine:
		str = "Closure line";
		break;

	case TigerDB::NVF_CensusWaterBoundary3Mile:
		str = "3 Mile Water Boundary";
		break;
	case TigerDB::NVF_CensusWaterBoundary12Mile:
		str = "12 Mile Water Boundary";
		break;

	case TigerDB::HYDRO_ClassificationUnknown:
	case TigerDB::HYDRO_PerennialShoreline:
	case TigerDB::HYDRO_IntermittentShoreline:
		str = "Shoreline";
		break;

	case TigerDB::HYDRO_PerennialStream:
	case TigerDB::HYDRO_IntermittentStream:
		str = "Streams";
		break;

	case TigerDB::HYDRO_PerennialCanalDitchOrAqueduct:
	case TigerDB::HYDRO_IntermittentCanalDitchOrAqueduct:
	case TigerDB::HYDRO_PerennialLakeOrPond:
	case TigerDB::HYDRO_IntermittentLakeOrPond:
	case TigerDB::HYDRO_PerennialReservoir:
	case TigerDB::HYDRO_IntermittentReservoir:
	case TigerDB::HYDRO_BayEstuaryGulfOrSound:
	case TigerDB::HYDRO_SeaOrOcean:
	case TigerDB::HYDRO_GravelPitOrQuarry:
	case TigerDB::HYDRO_Glacier:
		str = "Hydrography";
		break;
	}

	return(str);
}

// CMapViewSDView construction/destruction
enum RoadTypes
{
	INTERSTATE_ROAD = 0,
	PRIMARY_ROAD,
	SECONDARY_ROAD,
	LOCAL_ROAD,
	SHORELINE,
	STREAM,
	TRAIL,
	BOUNDARY,
	PARK,
	OTHER_ROAD
};

const int BLCK_PEN = 1;
const int RED_PEN = 0;
const int GREEN_PEN = 7;
const int BLUE_PEN = 3;
const int YELLOW_PEN = 4;		// RGB(255,255,0)
const int CYAN_PEN = 5;		// RGB(0,255,255)
const int MAGENTA_PEN = 8;		// RGB(255,0,255)
const int DASH_PEN = OTHER_ROAD + 1;
const int DOT_PEN = 8;
const int DASH_DOT_PEN = DASH_PEN + 1;
const int DASH_2DOTS_PEN = 10;

CMapViewSDView::CMapViewSDView() noexcept
{
	this->doThining = FALSE;
	this->doProj = 0;
	this->mapWin = 0;
	this->pens[INTERSTATE_ROAD].CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	this->pens[PRIMARY_ROAD].CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	this->pens[SECONDARY_ROAD].CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	this->pens[LOCAL_ROAD].CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	this->pens[SHORELINE].CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	this->pens[STREAM].CreatePen(PS_DASHDOTDOT, 1, RGB(0, 255, 255));
	this->pens[TRAIL].CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	this->pens[BOUNDARY].CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	this->pens[PARK].CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	this->pens[OTHER_ROAD].CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	this->pens[DASH_PEN].CreatePen(PS_DASH, 1, RGB(255, 0, 255));
	this->pens[DASH_DOT_PEN].CreatePen(PS_DASHDOT, 1, RGB(255, 0, 255));

	this->polyBrush.CreateSolidBrush(RGB(27, 149, 224));

	pts = 0;
	this->pan_overlap = 50;
	this->zoom_factor = 2.0;
	this->sDist = 10.0;
	this->tDist = 0.0;
	this->pts = 0;
	this->doWindow = FALSE;
	this->doPick = FALSE;
	this->doInfo = FALSE;

	this->pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	this->hPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	this->mapProj = 0;
	this->lineDlg = 0;

	GeoSphere sphere(6378.137);
	GeoEllipsoid ellipsoid;

	this->mapProjs[0] = new EquidistantCylindrical(sphere);
	this->mapProjs[1] = new TransverseMeracator(ellipsoid);
	//ASSERT(this->mapProj != 0);
	this->lineDlg = 0;
	this->doInfo = FALSE;
	this->doTest = FALSE;
	this->doShortPath = FALSE;
	this->pickCount = 0;
	this->startId = 0;
	this->startDir = 0;
	this->startDist = 0.0;
}

CMapViewSDView::~CMapViewSDView()
{
	if (this->mapWin)
		delete this->mapWin;

	delete this->mapProj;

	if (this->pts)
		delete[] pts;

	for (int i = 0; i < sizeof(this->pens) / sizeof(this->pens[0]); i++)
		this->pens[i].DeleteObject();

	this->pen.DeleteObject();
	this->hPen.DeleteObject();
	if (this->lineDlg)
		delete this->lineDlg;
}

BOOL CMapViewSDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CMapViewSDView::OnInitialUpdate()
{
	//	CSize region( 1, 1 );
	CView::OnInitialUpdate();
	CMapViewSDDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	ASSERT(pDoc != NULL);
	ASSERT(pDoc->db != 0);
	if (!pDoc->isOpen)
		//  if( ! pDoc->db->IsOpen() )
		return;

	if (this->mapWin == 0)
	{
		this->mapWin = new MapWindow(0, 1);
		ASSERT(this->mapWin != 0);
		if (this->doProj != 0)
			this->mapWin->Set(this->mapProj);
	}

	this->lineDlg = new LineDlg(this);

#if defined( DO_TIGER )
	this->geoPts.SetSize(1000, 100);
#endif

	if (this->pts == 0)
		this->pts = new XY_t/*GeoPoint*/[15000];
	ASSERT(this->pts != 0);

	CRect region;
	GetClientRect(region);

	Range2D range;

	range.x.min = (double)region.left;
	range.x.max = (double)region.right;
	range.y.min = (double)region.top;
	range.y.max = (double)region.bottom;

	this->mapWin->SetViewport(range);

#ifdef SAVE_FOR_NOW
	if (this->mapProj)
	{
		XY_t ll,
			ur,
			center;

		pDoc->range.Corners(&ll, &ur);
		pDoc->range.Center(&center);
		this->mapProj->Set(center.x, center.y);

		this->mapProj->Forward(&ll, ll);
		this->mapProj->Forward(&ur, ur);
		range.Init(ll, ur);
		this->mapWin->Set(range);
		this->sDist = (range.x.max - range.x.min) / 100.0;
	}
	else
#endif
	{
		this->mapWin->Set(pDoc->range);
		if (this->mapProj)
		{
			XY_t center;

			pDoc->range.Center(&center);
			this->mapProj->Forward(&center, center);
			this->mapProj->Set(center.x, center.y);
		}
	}
	//	SetScrollSizes( MM_TEXT, region /*GetDocument()->GetDocSize()*/ );
	//	this->SetWindowText( GetDocument()->title );
}


// CMapViewSDView drawing
CBrush* CMapViewSDView::GetBrush(int code)
{
	if (!this->layerDlg.doAreas)
		return 0;
	return &this->polyBrush;
}

CPen* CMapViewSDView::GetPen(int code)
{
	CPen* pen = 0;
	if (!this->layerDlg.doLines)
		return pen;

	switch (code)
	{
	default:
		break;

	case TigerDB::ROAD_MajorCategoryUnknown:
	case TigerDB::ROAD_SpecialCharacteristics:
	case TigerDB::ROAD_Cul_de_sac:
	case TigerDB::ROAD_TrafficCircle:
	case TigerDB::ROAD_AccessRamp:
	case TigerDB::ROAD_ServiceDrive:
	case TigerDB::ROAD_FerryCrossing:
	case TigerDB::ROAD_OtherThoroughfare:
		if (this->layerDlg.doOtherRds)
			pen = &this->pens[OTHER_ROAD];
		break;

	case TigerDB::ROAD_PrimaryLimitedAccess:
		if (this->layerDlg.doPrimaryRds)
			pen = &this->pens[INTERSTATE_ROAD];
		break;

	case TigerDB::ROAD_PrimaryUnlimitedAccess:
		if (this->layerDlg.doPrimaryRds)
			pen = &this->pens[PRIMARY_ROAD];
		break;

	case TigerDB::ROAD_SecondaryAndConnecting:
		if (this->layerDlg.doSecondaryRds)
			pen = &this->pens[SECONDARY_ROAD];
		break;

	case TigerDB::ROAD_LocalNeighborhoodAndRural:
		if (this->layerDlg.doLocalRds)
			pen = &this->pens[LOCAL_ROAD];
		break;

	case TigerDB::ROAD_VehicularTrail:
		if (this->layerDlg.doTrails)
			pen = &this->pens[TRAIL];
		break;

	case TigerDB::RR_MajorCategoryUnknown:
	case TigerDB::RR_MainLine:
	case TigerDB::RR_Spur:
	case TigerDB::RR_Yard:
	case TigerDB::RR_SpecialCharacteristics:
	case TigerDB::RR_OtherThoroughfare:
		pen = 0;
		break;

	case TigerDB::MGT_CategoryUnknown:
	case TigerDB::MGT_Pipeline:
	case TigerDB::MGT_PowerLine:
	case TigerDB::MGT_SpecialCharacteristics:
		pen = 0;
		break;

	case TigerDB::LM_Airport:
	case TigerDB::LM_GolfCourse:
	case TigerDB::LM_Cemetery:
	case TigerDB::LM_NationalParkOrForest:
	case TigerDB::LM_OtherFederalLand:
	case TigerDB::LM_StateOrLocalPark_Forest:
		pen = &this->pens[PARK];
		break;

	case TigerDB::NVF_BoundaryClassificationUnknown:
	case TigerDB::NVF_LegalOrAdministrativeBoundary:
		if (this->layerDlg.doBoundary)
			pen = &this->pens[BOUNDARY];
		break;

	case TigerDB::NVF_PropertyLine:
		if (this->layerDlg.doOtherFeatures)
			pen = &this->pens[PARK];
		break;

	case TigerDB::HYDRO_ClassificationUnknown:
	case TigerDB::HYDRO_PerennialShoreline:
	case TigerDB::HYDRO_IntermittentShoreline:
	case TigerDB::HYDRO_IntermittentCanalDitchOrAqueduct:
	case TigerDB::HYDRO_PerennialLakeOrPond:
	case TigerDB::HYDRO_IntermittentLakeOrPond:
	case TigerDB::HYDRO_PerennialReservoir:
	case TigerDB::HYDRO_IntermittentReservoir:
	case TigerDB::HYDRO_BayEstuaryGulfOrSound:
	case TigerDB::HYDRO_SeaOrOcean:
	case TigerDB::HYDRO_GravelPitOrQuarry:
	case TigerDB::HYDRO_Glacier:
		if (this->layerDlg.doShoreline)
			pen = &this->pens[SHORELINE];
		break;

	case TigerDB::HYDRO_PerennialStream:
	case TigerDB::HYDRO_IntermittentStream:
		if (this->layerDlg.doStreams)
			pen = &this->pens[STREAM];
		break;
	}
#ifdef SAVE_FOR_NOW
	if (code >= 0 && code < 100)			// roads
	{
		if (code >= 10 && code < 30)		// Interstates & US highways
		{
			if (this->layerDlg.doPrimaryRds)
				pen = &this->pens[PRIMARY_ROAD];
		}
		else if (code >= 30 && code < 40)	// Secondary & Connectors
		{
			if (this->layerDlg.doSecondaryRds)
				pen = &this->pens[SECONDARY_ROAD];
		}
		else if (code >= 40 && code < 50)	// Local/Rural
		{
			if (this->layerDlg.doLocalRds)
				pen = &this->pens[LOCAL_ROAD];
		}
		else if (code >= 50 && code < 60)		// Trails
		{
			if (this->layerDlg.doTrails)
				pen = &this->pens[TRAIL];
		}
		else if (code < 10 || code >= 60)
		{
			if (this->layerDlg.doOtherRds)
				pen = &this->pens[OTHER_ROAD];
		}
	}
	else if (code >= 100 && code < 200)	// railroad
		pen = 0;
	else if (code >= 200 && code < 300)	// Miscellenous ground transportation
		pen = 0;
	else if (code >= 300 && code < 400)	// Land Mark features
	{
		if (this->layerDlg.doOtherFeatures)
			pen = &this->pens[PARK];
	}
	else if (code >= 400 && code < 500)	// Physical features
		pen = 0;
	else if (code >= 500 && code < 600)	// Non-visible features
	{
		if (code == 510 || code == 511 || code == 512)
		{
			if (this->layerDlg.doBoundary)
				pen = &this->pens[BOUNDARY];
		}
		else if (code == 540)
		{
			if (this->layerDlg.doOtherFeatures)
				pen = &this->pens[PARK];
		}
	}
	else if (code >= 700 && code < 800)	// Hydrography
	{
		switch (code)
		{
		default:
			//	        pen = &this->pens[ GREEN_PEN ];
			break;

		case 700:
		case 701:
		case 702:
		case 730:
		case 731:
		case 750:
		case 751:
		case 752:
		case 753:
			if (this->layerDlg.doShoreline)
				pen = &this->pens[SHORELINE];
			break;

		case 710:
		case 711:
		case 712:
			if (this->layerDlg.doStreams)
				pen = &this->pens[STREAM];
			break;
		}
	}
#endif
	return(pen);
}


void CMapViewSDView::OnDraw(CDC* pDC)
{
	CMapViewSDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CMainFrame* frame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	HCURSOR cursor = SetCursor(LoadCursor(0, IDC_WAIT));

	ASSERT(pDoc->db != 0);
	if (pDoc->isOpen)
		//  if( doc->db->IsOpen() )
	{
		Range2D range;
		CPen* lastPen = 0;
		CPen* oldPen = pDC->SelectObject((CPen*)pDC->SelectStockObject(NULL_PEN));
		//	CWinApp *app = AfxGetApp();
		//	this->mapWin->ReverseRange( &range );

		{
			CRect region;
			XY_t pt1,
				pt2;

			pDC->GetClipBox(region);

			CPoint& pt = region.TopLeft();
			pt1.x = (double)pt.x;
			pt1.y = (double)pt.y;
			this->mapWin->Reverse(&pt1, pt1);
			pt = region.BottomRight();
			pt2.x = (double)pt.x;
			pt2.y = (double)pt.y;
			this->mapWin->Reverse(&pt2, pt2);

			range.Init(pt1, pt2);
			//range = pDoc->db->GetRange();  // Temporary hack to get all the features
			//	range.Envelope( pt0 );
		}
		//	app->LoadStandardCursor( IDC_WAIT );
#if defined (DO_TIGER)
		GeoPoint min,
			max;

		min.lon = (long)range.x.min;
		max.lon = (long)range.x.max;

		min.lat = (long)range.y.min;
		max.lat = (long)range.y.max;

		doc->tigerLines->SetQueryByMBR(min, max);
		doc->tigerLines->Requery();
		while (!doc->tigerLines->IsEOF())
		{
			if (frame->OnAbort())
				break;
			int nPts = doc->tigerLines->GetGeoPts(this->geoPts);
			ASSERT(nPts <= 1000);
			for (int i = nPts; --i >= 0; )
			{
				this->pts[i].x = this->geoPts[i].lon;
				this->pts[i].y = this->geoPts[i].lat;
			}

			CPen* pen;
			if ((pen = this->GetPen(doc->tigerLines->GetDFCC())) != 0)
			{
				if (pen != lastPen)
				{
					pDC->SelectObject(pen);
					lastPen = pen;
				}
				if (doThining)
					nPts = TrendLine(this->pts, nPts, this->tDist);
				DrawLine(*this->mapWin, pDC, this->pts, nPts);
			}

			doc->tigerLines->MoveNext();
		}
#else
		ObjHandle dbo;
		GeoDB::Search ss;

//		pDoc->db->CheckTree();

		pDoc->db->Init(range, &ss);
		while (pDoc->db->GetNext(&ss, &dbo) == 0)
		{
			/*if (frame->OnAbort())
				break;*/
			GeoDB::SpatialObj* spatialObj = (GeoDB::SpatialObj*)dbo.Lock();
//			DbObject::ClassCode code = so->getClassCode();
//			if (code == DB_TIGER_POLY)
			GeoDB::SpatialClass sc = spatialObj->IsA();
			switch (sc)
			{
				case GeoDB::AREA:
				{
					int nPts = TigerDB::Polygon::GetPts(dbo, this->pts);
					TigerDB::Polygon* poly = (TigerDB::Polygon*)spatialObj;
					CBrush* brush;
					if ((brush = this->GetBrush(poly->GetCode())) != 0)
					{
						pDC->SelectObject(brush);
						DrawPolygon(*this->mapWin, pDC, this->pts, nPts);
					}
					break;
				}

				case GeoDB::LINE:
				{
					TigerDB::Chain* line = (TigerDB::Chain*)spatialObj;
					ASSERT(line != 0);
					CPen* pen;
					if ((pen = this->GetPen(line->GetCode())) != 0)
					{
						int nPts = (int)line->GetNumPts();
						line->Get(this->pts);
						if (pen != lastPen)
						{
							pDC->SelectObject(pen);
							lastPen = pen;
						}
						if (doThining)
							nPts = TrendLine(this->pts, nPts, this->tDist);
						DrawLine(*this->mapWin, pDC, this->pts, nPts);
						//	    this->mapWin->Draw( pDC, this->pts, nPts );
					}
				}
			}
			dbo.Unlock();
		}
#endif
		if (oldPen != 0)
			pDC->SelectObject(oldPen);
		//	app->LoadStandardCursor( IDC_ARROW );
	}

	SetCursor(cursor);
}

void CMapViewSDView::DoPan(double horizontal, double vertical)
{
	if (this->mapWin != 0)
	{
		double pan_factor = (double)(100 - this->pan_overlap) / 100.0;
		XY_t dispPt;

		dispPt.x = horizontal * pan_factor;
		dispPt.y = vertical * pan_factor;

		this->mapWin->PanByDisplay(dispPt);
		this->Invalidate();
	}
}

void CMapViewSDView::OnPanDown()
{
	this->DoPan(0.0, -1.0);
}

void CMapViewSDView::OnPanLeft()
{
	this->DoPan(-1.0, 0.0);
}

void CMapViewSDView::OnPanRight()
{
	this->DoPan(1.0, 0.0);
}

void CMapViewSDView::OnPanUp()
{
	this->DoPan(0.0, 1.0);
}

void CMapViewSDView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (this->mapWin != 0)
	{
		this->pt = point;
		this->doWindow = TRUE;
		this->rect.SetRectEmpty();
	}

	CView::OnLButtonDown(nFlags, point);
}

const int PICK_TOL = 3;

void CMapViewSDView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);

	if (this->doWindow /*&& this->mOnLButtonUpapWin != 0*/)
	{
		XY_t pt0;
		int xDiff,
			yDiff;

		pt0.x = (double)this->pt.x;
		pt0.y = (double)this->pt.y;
		this->mapWin->Reverse(&pt0, pt0);

		if ((xDiff = point.x - this->pt.x) < 0)
			xDiff = -xDiff;

		if ((yDiff = point.y - this->pt.y) < 0)
			yDiff = -yDiff;

		if (xDiff <= PICK_TOL && yDiff <= PICK_TOL)
			//	if( point.x == this->pt.x && point.y == this->pt.y )
		{
#ifdef SAVE_FOR_NOW
			if (this->mapProj)
			{
				this->mapProj->Set(pt0.x, pt0.y);
				this->mapProj->Forward(&pt0, pt0);
			}
#endif
			this->mapWin->Set(pt0);
		}
		else
		{
			Range2D range;

			range.Add(pt0);

			pt0.x = (double)point.x;
			pt0.y = (double)point.y;
			this->mapWin->Reverse(&pt0, pt0);
			range.Add(pt0);

#ifdef SAVE_FOR_NOW  
			if (this->mapProj)
			{
				XY_t ll,
					ur,
					center;

				range.Corners(&ll, &ur);
				range.Center(&center);
				this->mapProj->Set(center.x, center.y);

				this->mapProj->Forward(&ll, ll);
				this->mapProj->Forward(&ur, ur);
				range.Init(ll, ur);
			}
#endif
			this->mapWin->Set(range);
		}

		this->doWindow = FALSE;
		this->Invalidate();
	}
}

void CMapViewSDView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (this->mapWin != 0)
	{
		this->doPick = TRUE;

		if (this->doTest)
		{
			XY_t pt0;

			pt0.x = (double)point.x;
			pt0.y = (double)point.y;
			this->mapWin->Reverse(&this->pts[0], pt0);
		}
	}

	CView::OnRButtonDown(nFlags, point);
}

void CMapViewSDView::OnRButtonUp(UINT nFlags, CPoint point)
{
	XY_t pt0;
	CMapViewSDDoc* doc = GetDocument();

	if (this->doTest)
	{
		LineSeg2D lSeg;

		pt0.x = (double)point.x;
		pt0.y = (double)point.y;
		this->mapWin->Reverse(&pt0, pt0);

		ASSERT(doc->db != 0);
		if (doc->db->IsOpen())
		{
#if defined( DO_TIGER )
#else
			DbSearchByLSeg so(*doc->db);
			DbSearch::Found fo;
			lSeg.Init(this->pts[0], pt0);

			so.Init(lSeg);
			if (so.FindBest(&fo) == 0)
			{
			}
#endif
		}
	}
	else if (this->doPick)
	{
		pt0.x = (double)point.x;
		pt0.y = (double)point.y;
		this->mapWin->Reverse(&pt0, pt0);

		ASSERT(doc->db != 0);
		//	if( doc->isOpen )
		if (doc->db->IsOpen())
		{
			CDC* dc = GetDC();
			HCURSOR cursor = SetCursor(LoadCursor(0, IDC_WAIT));
#if defined( DO_TIGER )
#else
			DbSearchByPt so(*doc->db);
			DbSearch::Found fo;

			so.Init(pt0, this->sDist);
			if (so.FindBest(&fo) == 0)
			{
				TigerDB::Chain* line = (TigerDB::Chain*)fo.handle.Lock();
				ASSERT(line != 0);
				CPen* pen;
				int code = line->GetCode();

				if ((pen = &this->hPen/*this->GetPen(code)*/) != 0)
				{
					//pen = &this->hPen;
					int nPts = (int)line->GetNumPts();
					line->Get(this->pts);

					CPen* oldPen = dc->SelectObject(pen);
					int old_rop2 = dc->SetROP2(R2_XORPEN);

					if (this->doThining)
						nPts = TrendLine(this->pts, nPts, this->tDist);
					DrawLine(*this->mapWin, dc, this->pts, nPts);
					//	      this->mapWin->Draw( dc, this->pts, nPts );
/**/				if (this->doInfo)
					{
						TCHAR buffer[80];
						TigerDB::Name name;
						_stprintf_s(buffer, _T("%ld (%ld)"), line->GetTLID(), line->dbAddress());
						this->lineDlg->m_id = buffer;
						int nNames = line->GetNumNames();

						buffer[0] = _T('\0');
						if (nNames > 0)
						{
							for (int i = 0; i < nNames; i++)
							{
								line->GetName(&name, i);
								if (i > 0)
									_tcscat_s(buffer, _T("|"));

								if (::strlen(name.prefix) > 0)
								{
									_tcscat_s(buffer, TString(name.prefix));
									_tcscat_s(buffer, _T(" "));
								}

								if (::strlen(name.name) > 0)
								{
									_tcscat_s(buffer, TString(name.name));
								}
								if (::strlen(name.type) > 0)
								{
									_tcscat_s(buffer, _T(" "));
									_tcscat_s(buffer, TString(name.type));
								}
								if (::strlen(name.suffix) > 0)
								{
									_tcscat_s(buffer, _T(" "));
									_tcscat_s(buffer, TString(name.suffix));
								}
							}
						}
						
						this->lineDlg->m_name = buffer;
						this->lineDlg->m_type = LineStr(code);
						this->lineDlg->UpdateData(FALSE);
					}
				/**/
#ifdef DO_LATER		  
					if (this->doShortPath)
					{
						double distSq;
						XY_t tempPt;
						int dir;

						distSq = fo.pt.DistSqr(this->pts[0]);
						if (distSq < fo.pt.DistSqr(this->pts[nPts - 1]))
						{
							tempPt = this->pts[0];
							dir = -1;
						}
						else
						{
							tempPt = this->pts[nPts - 1];
							dir = 1;
						}

						if (++this->pickCount == 1)
						{
							this->startId = line->dbAddress();
							this->startPt = tempPt;
							this->startDir = dir;
							this->startDist = line->Length();
						}
						else if (this->pickCount == 2)
						{
							ShortPath sPath;
							CArray<long, long> lineIds;
							ObjHandle handle;
							double dist;
							int nIds;

							doc->db->Read(this->startId, handle);
							line = (TigerDB::Chain*)handle.Lock();
							sPath.Init(tempPt, *line);
							handle.Unlock();
							//							sPath.Init( this->startId, line, 0, tempPt );
							if (nIds = sPath.Find(doc->db, 0, 0, &lineIds, &dist))
							{
								while (--nIds >= 0)
								{
									doc->db->Read(lineIds[nIds], handle);
									line = (TigerDB::Chain*)handle.Lock();
									nPts = (int)line->GetNumPts();
									line->Get(this->pts);
									DrawLine(*this->mapWin, dc, this->pts, nPts);
									handle.Unlock();
								}
							}

							this->pickCount = 0;
						}
					}
#endif
					dc->SelectObject(oldPen);
					dc->SetROP2(old_rop2);
				}
				fo.handle.Unlock();
				this->pickObj = fo.handle;
			}
#endif
			SetCursor(cursor);
			ReleaseDC(dc);
		}
	}

	this->doPick = FALSE;
	CView::OnRButtonUp(nFlags, point);
}

void CMapViewSDView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (doWindow)
	{
		CDC* dc = GetDC();

		this->brush.Attach(GetStockObject(NULL_BRUSH));

		CPen* old_pen = (CPen*)dc->SelectStockObject(WHITE_PEN /*&this->pen*/);
		CBrush* old_brush = dc->SelectObject(&this->brush);
		int old_rop2 = dc->SetROP2(R2_XORPEN);

		//	int dx = abs( this->pt.x - point.x);
		//	int dy = abs( this->pt.y - point.y);
		if (!this->rect.IsRectEmpty())
			dc->Rectangle(this->rect);

		this->rect.SetRect(this->pt.x, this->pt.y, point.x, point.y);
		this->rect.NormalizeRect();

		dc->Rectangle(this->rect);

		dc->SelectObject(old_pen);
		dc->SelectObject(old_brush);
		dc->SetROP2(old_rop2);
		this->brush.Detach();

		ReleaseDC(dc);
	}

	CView::OnMouseMove(nFlags, point);
}

// CMapViewSDView printing


void CMapViewSDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMapViewSDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapViewSDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapViewSDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
/*
void CMapViewSDView::OnRButtonUp(UINT , CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}
*/
void CMapViewSDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMapViewSDView diagnostics

#ifdef _DEBUG
void CMapViewSDView::AssertValid() const
{
	CView::AssertValid();
}

void CMapViewSDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapViewSDDoc* CMapViewSDView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapViewSDDoc)));
	return (CMapViewSDDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapViewSDView message handlers

void CMapViewSDView::OnZoomIn()
{
	if (this->mapWin != 0)
	{
		this->mapWin->ScaleByFactor(this->zoom_factor);
		this->Invalidate();
	}
}

void CMapViewSDView::OnZoomOut()
{
	if (this->mapWin != 0)
	{
		this->mapWin->ScaleByFactor(1.0 / this->zoom_factor);
		this->Invalidate();
	}
}

void CMapViewSDView::OnMapLayers()
{
	if (this->layerDlg.DoModal() == IDOK)
	{
		this->Invalidate();
	}
}

void CMapViewSDView::OnUpdateMapLayers(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(this->mapWin != 0);
}

void CMapViewSDView::OnLineInfo()
{
	this->doInfo = !this->doInfo;
	if (doInfo)
		this->lineDlg->ShowWindow(SW_NORMAL);
	else
		this->lineDlg->ShowWindow(SW_HIDE);
}

void CMapViewSDView::OnUpdateLineInfo(CCmdUI* pCmdUI)
{
	if (this->mapWin != 0)
	{
		pCmdUI->SetCheck(this->doInfo);
	}
	else
		pCmdUI->Enable(FALSE);
}

void CMapViewSDView::OnMapProj()
{
	MapPDIAL dialog(this);

	dialog.m_projNum = this->doProj;
	if (dialog.DoModal() == IDOK)
	{
		if (dialog.m_projNum != this->doProj)
		{
			Range2D range;
			this->mapWin->GetRange(&range);

			this->doProj = dialog.m_projNum;
			if (this->doProj != 0)
			{
				this->mapProj = this->mapProjs[this->doProj - 1];
				this->mapWin->Set(this->mapProj);
			}
			else
				this->mapWin->Set(0);
			this->mapWin->Set(range);
			this->Invalidate();
		}
	}
}

void CMapViewSDView::OnThinPts()
{
	ThinDlg dlg(this);

	dlg.m_checked = this->doThining;
	dlg.m_value.Format(_T("%f"), this->tDist);
	if (dlg.DoModal() == IDOK)
	{
		double dist = ::atof(TString(dlg.m_value));
		BOOL doInvalid = FALSE;

		if (dist != this->tDist)
		{
			doInvalid = TRUE;
			this->tDist = dist;
		}

		if (this->doThining != dlg.m_checked)
		{
			doInvalid = TRUE;
			this->doThining = dlg.m_checked;
		}

		if (doInvalid)
			this->Invalidate();
	}
}
