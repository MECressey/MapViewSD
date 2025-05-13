//
//	TIGERDB.CPP - implementation for the TigerDB custom database using the NodeEdgePoly class library.
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
#include <assert.h>
#include <afxdb.h>

#include "tigerdb.hpp"
#include "distname.h"
#include "GNISName.h"
#include "ACSSurveyData.h"

using namespace NodeEdgePoly;

const int MAX_TIGER_LINES		= 700;

// Census Feature Code Class - based on 2006 classification codes
TigerDB::MAFTCCodes TigerDB::MapMTFCC(const char* mtfcc)
{
	int mtfccNum = atoi(&mtfcc[1]);
	TigerDB::MAFTCCodes code = TigerDB::FeatureNotClassified;

	switch (mtfcc[0])
	{
	default:
		fprintf(stderr, "*MapMTFCC - invalid MTFCC Code: %c\n", mtfcc[0]);
		break;

	case 'C':
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC C: %d\n", mtfccNum);
			break;
		case 3022:
			code = TigerDB::TOPO_MountainPeakSummit;
			break;
		case 3023:
			code = TigerDB::TOPO_Island;
			break;
		case 3024:
			code = TigerDB::TOPO_Levee;
			break;
		case 3025:
			code = TigerDB::TOPO_JettyBreakwater;
			break;
		case 3026:
			code = TigerDB::TOPO_Quarry;
			break;
		case 3027:
			code = TigerDB::TOPO_Dam;
			break;
		case 3061:
			code = TigerDB::TOPO_CulDeSac;
			break;
		case 3062:
			code = TigerDB::TOPO_TrafficCircle;
			break;
		case 3066:
			code = TigerDB::TOPO_Gate;
			break;
		case 3067:
			code = TigerDB::TOPO_TollBooth;
			break;
		case 3071:
			code = TigerDB::TOPO_Tower;
			break;
		case 3074:
			code = TigerDB::TOPO_LighthouseBeacon;
			break;
		case 3075:
			code = TigerDB::TOPO_Tank;
			break;
		case 3076:
			code = TigerDB::TOPO_WindmillFarm;
			break;
		case 3077:
			code = TigerDB::TOPO_SolarFarm;
			break;
		case 3078:
			code = TigerDB::TOPO_Monument;
			break;
		case 3079:
			code = TigerDB::TOPO_BoundaryMonument;
			break;
		case 3080:
			code = TigerDB::TOPO_SurveyControlPoint;
			break;
		case 3081:
			code = TigerDB::TOPO_LocalityPoint;
			break;
		case 3085:
			code = TigerDB::TOPO_AlaskaNativeVillage;
			break;
		}
		break;

	case 'G':
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC G: %d\n", mtfccNum);
			break;
		case 1000:
			code = TigerDB::TAB_Nation;
			break;
		case 1100:
			code = TigerDB::TAB_CensusRegion;
			break;
		case 1200:
			code = TigerDB::TAB_CensusDivision;
			break;
		case 2100:
			code = TigerDB::TAB_AIA;
			break;
		case 2120:
			code = TigerDB::TAB_HH;
			break;
		case 2130:
			code = TigerDB::TAB_ANVSA;
			break;
		case 2140:
			code = TigerDB::TAB_OTSA;
			break;
		case 2150:
			code = TigerDB::TAB_SDTSA;
			break;
		case 2160:
			code = TigerDB::TAB_TDSA;
			break;
		case 2170:
			code = TigerDB::TAB_AIJUA;
			break;
		case 2200:
			code = TigerDB::TAB_AlaskaRegionalCorp;
			break;
		case 2300:
			code = TigerDB::TAB_TribalSubdivision;
			break;
		case 2400:
			code = TigerDB::TAB_TribalCensusTract;
			break;
		case 2410:
			code = TigerDB::TAB_TribalBlockGroup;
			break;
		case 3100:
			code = TigerDB::TAB_CombinedStatisicalArea;
			break;
		case 3110:
			code = TigerDB::TAB_MetroStatisticalArea;
			break;
		case 3120:
			code = TigerDB::TAB_MetropolitanDivision;
			break;
		case 3200:
			code = TigerDB::TAB_NewEnglandCityTown;
			break;
		case 3210:
			code = TigerDB::TAB_NewEnglandMetroStatArea;
			break;
		case 3220:
			code = TigerDB::TAB_NewEngland_CityTownDiv;
			break;
		case 3500:
			code = TigerDB::TAB_UrbanArea;
			break;
		case 4000:
			code = TigerDB::TAB_StateFeature;
			break;
		case 4020:
			code = TigerDB::TAB_CountyFeature;
			break;
		case 4040:
			code = TigerDB::TAB_CountySubdivision;
			break;
		case 4050:
			code = TigerDB::TAB_Estate;
			break;
		case 4060:
			code = TigerDB::TAB_SubMinorCivilDivision;
			break;
		case 4110:
			code = TigerDB::TAB_IncorporatedPlace;
			break;
		case 4120:
			code = TigerDB::TAB_ConsolidatedCity;
			break;
		case 4210:
			code = TigerDB::TAB_CensusDesignatedPlace;
			break;
		case 4300:
			code = TigerDB::TAB_EconomicCensusPlace;
			break;
		case 5020:
			code = TigerDB::TAB_CensusTract;
			break;
		case 5030:
			code = TigerDB::TAB_CensusBlockGroup;
			break;
		case 5040:
			code = TigerDB::TAB_Block;
			break;
		case 5200:
			code = TigerDB::TAB_CongressionalDistrict;
			break;
		case 5210:
			code = TigerDB::TAB_StateLegislativeDistrictUC;
			break;
		case 5220:
			code = TigerDB::TAB_StateLegislativeDistrictLC;
			break;
		case 5240:
			code = TigerDB::TAB_VotingDistrict;
			break;
		case 5400:
			code = TigerDB::TAB_ElementarySchoolDistrict;
			break;
		case 5410:
			code = TigerDB::TAB_SecondarySchoolDistrict;
			break;
		case 5420:
			code = TigerDB::TAB_UnifiedSchoolDistrict;
			break;
		case 6120:
			code = TigerDB::TAB_PUMA;
			break;
		case 6330:
			code = TigerDB::TAB_UrbanGrowthArea;
			break;
		case 6350:
			code = TigerDB::TAB_ZIPCodeArea;
			break;
		case 6400:
			code = TigerDB::TAB_PlanningRegion;
			break;
		}
		break;

	case 'H':		// Hydrography
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC H: %d\n", mtfccNum);
			break;
		case 1100:
			code = TigerDB::HYDRO_Connector;
			break;
		case 2030:
			code = TigerDB::HYDRO_LakePond;
			break;
		case 2040:
			code = TigerDB::HYDRO_Reservoir;
			break;
		case 2041:
			code = TigerDB::HYDRO_TreatmentPond;
			break;
		case 2051:
			code = TigerDB::HYDRO_BayEstuaryGulfSound;
			break;
		case 2053:
			code = TigerDB::HYDRO_OceanSea;
			break;
		case 2081:
			code = TigerDB::HYDRO_Glacier;
			break;
		case 3010:
			code = TigerDB::HYDRO_StreamRiver;
			break;
		case 3013:
			code = TigerDB::HYDRO_BraidedStream;
			break;
		case 3020:
			code = TigerDB::HYDRO_CanalDitchAqueduct;
			break;
		}
		break;

	case 'K':
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC K: %d\n", mtfccNum);
			break;
		case 1121:
			code = TigerDB::LIVING_ApartmentBuilding;
			break;
		case 1223:
			code = TigerDB::LIVING_TrailerCourt;
			break;
		case 1225:
			code = TigerDB::LIVING_CrewOfVessel;
			break;
		case 1226:
			code = TigerDB::LIVING_HousingFacility;
			break;
		case 1227:
			code = TigerDB::LIVING_HotelMotelResort;
			break;
		case 1228:
			code = TigerDB::LIVING_Campground;
			break;
		case 1229:
			code = TigerDB::LIVING_ShelterMission;
			break;
		case 1231:
			code = TigerDB::LIVING_HospitalHospice;
			break;
		case 1233:
			code = TigerDB::LIVING_NursingHome;
			break;
		case 1235:
			code = TigerDB::LIVING_JuvenileInstitution;
			break;
		case 1236:
			code = TigerDB::LIVING_DententionCenter;
			break;
		case 1237:
			code = TigerDB::LIVING_FederalPenitentiary;
			break;
		case 1238:
			code = TigerDB::LIVING_OtherCorrectional;
			break;
		case 1239:
			code = TigerDB::LIVING_ConventMonasteryRectory;
			break;
		case 2100:
			code = TigerDB::GOV_Governmental;
			break;
		case 2110:
			code = TigerDB::GOV_MilitaryInstallation;
			break;
		case 2146:
			code = TigerDB::GOV_CommunityCenter;
			break;
		case 2165:
			code = TigerDB::GOV_GovermentCenter;
			break;
		case 2167:
			code = TigerDB::GOV_ConventionCenter;
			break;
		case 2180:		// Park
			code = TigerDB::GOV_Park;
			break;
		case 2181:
			code = TigerDB::PARK_NationalParkService;
			break;
		case 2182:
			code = TigerDB::PARK_NationalForest;
			break;
		case 2183:
			code = TigerDB::PARK_TribalPark;
			break;
		case 2184:
			code = TigerDB::PARK_StateParkForest;
			break;
		case 2185:
			code = TigerDB::PARK_RegionalParkForest;
			break;
		case 2186:
			code = TigerDB::PARK_CountyParkForest;
			break;
		case 2187:
			code = TigerDB::PARK_CountySubdivionPark;
			break;
		case 2188:
			code = TigerDB::PARK_IncorporatedPlacePark;
			break;
		case 2189:
			code = TigerDB::PARK_PrivateParkForest;
			break;
		case 2190:
			code = TigerDB::PARK_OtherParkForest;
			break;
		case 2191:
			code = TigerDB::GOV_PostOffice;
			break;
		case 2193:
			code = TigerDB::GOV_FireDepartment;
			break;
		case 2195:
			code = TigerDB::GOV_Library;
			break;
		case 2196:
			code = TigerDB::GOV_CityTownHall;
			break;
		case 2300:
			code = TigerDB::WORK_CommericalWorkPlace;
			break;
		case 2361:
			code = TigerDB::WORK_ShoppingCenter;
			break;
		case 2362:
			code = TigerDB::WORK_IndustrialBuildingPark;
			break;
		case 2363:
			code = TigerDB::WORK_OfficeBuildingPark;
			break;
		case 2364:
			code = TigerDB::WORK_FarmVineyardOrchard;
			break;
		case 2366:
			code = TigerDB::WORK_OtherEmploymentCenter;
			break;
		case 2400:
			code = TigerDB::WORK_TransportationTerminal;
			break;
		case 2424:
			code = TigerDB::TT_Marina;
			break;
		case 2432:
			code = TigerDB::TRANS_PierDock;
			break;
		case 2451:
			code = TigerDB::TT_Airport;
			break;
		case 2452:
			code = TigerDB::TT_TrainStation;
			break;
		case 2453:
			code = TigerDB::TT_BusTerminal;
			break;
		case 2454:
			code = TigerDB::TT_MarineTerminal;
			break;
		case 2455:
			code = TigerDB::TT_SeaplaneAnchorage;
			break;
		case 2457:
			code = TigerDB::TT_Airport;
			break;
		case 2459:
			code = TigerDB::TRANS_RunwayTaxiWay;
			break;
		case 2460:
			code = TigerDB::TT_HelicopterLandingPad;
			break;
		case 2540:
			code = TigerDB::OTHERWP_UniversityCollege;
			break;
		case 2543:
			code = TigerDB::OTHERWP_SchoolAcademy;
			break;
		case 2545:
			code = TigerDB::OTHERWP_MuseumVistorCenter;
			break;
		case 2561:
			code = TigerDB::OTHERWP_GolfCourse;
			break;
		case 2564:
			code = TigerDB::OTHERWP_AmusementCenter;
			break;
		case 2582:
			code = TigerDB::OTHERWP_Cemetery;
			break;
		case 2586:
			code = TigerDB::OTHERWP_Zoo;
			break;
		case 3544:
			code = TigerDB::OTHERWP_PlaceOfWorkship;
			break;
		}
		break;

	case 'L':
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC L: %d\n", mtfccNum);
			break;
		case 4010:
			code = TigerDB::MISC_Pipeline;
			break;
		case 4020:
			code = TigerDB::MISC_Powerline;
			break;
		case 4031:
			code = TigerDB::MISC_AerialTramway;
			break;
		case 4110:
			code = TigerDB::MISC_FenceLine;
			break;
		case 4121:
			code = TigerDB::MISC_RidgeLine;
			break;
		case 4125:
			code = TigerDB::MISC_Cliff;
			break;
		case 4130:
			code = TigerDB::MISC_PointToPoint;
			break;
		case 4140:
			code = TigerDB::MISC_PropertyLine;
			break;
		case 4150:	// Coastline
			code = TigerDB::MISC_Coastline;
			break;
		case 4165:
			code = TigerDB::MISC_FerryCrossing;
			break;
		}
		break;

	case 'P':
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC P: %d\n", mtfccNum);
			break;
		case 1:
			code = TigerDB::EDGE_NonvisibleLinearBoundary;
			break;
		case 2:
			code = TigerDB::EDGE_PerennialShoreline;
			break;
		case 3:
			code = TigerDB::EDGE_IntermittentShoreline;
			break;
		case 4:  // Other non-visible edge (need a new code)
			code = TigerDB::EDGE_OtherNonVisible;
			break;
		}
		break;

	case 'R':	// Rail
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC R: %d\n", mtfccNum);
			break;
		case 1011:
			code = TigerDB::RAIL_Rail;
			break;
		}
		break;

	case 'S': // Street Type
		switch (mtfccNum)
		{
		default:
			fprintf(stderr, "*MapMTFCC - Unknown MTFCC S: %d\n", mtfccNum);
			break;
		case 1100:
			code = TigerDB::ROAD_PrimaryRoad;
			break;
		case 1200:
			code = TigerDB::ROAD_SecondaryRoad;
			break;
		case 1400:
			code = TigerDB::ROAD_LocalNeighborhoodRoad;
			break;
		case 1500:
			code = TigerDB::ROAD_VehicularTrail4WD;
			break;
		case 1630:
			code = TigerDB::ROAD_Ramp;
			break;
		case 1640:
			code = TigerDB::ROAD_ServiceDrive;
			break;
		case 1710:
			code = TigerDB::ROAD_Walkway;
			break;
		case 1720:
			code = TigerDB::ROAD_Stairway;
			break;
		case 1730:
			code = TigerDB::ROAD_Alley;
			break;
		case 1740:
			code = TigerDB::ROAD_PrivateRoad;
			break;
		case 1750:
			code = TigerDB::ROAD_InternalCensusBureau;
			break;
		case 1780:
			code = TigerDB::ROAD_ParkingLotRd;
			break;
		case 1810:
			code = TigerDB::ROAD_WinterTrail;
			break;
		case 1820:
			code = TigerDB::ROAD_BikePath;
			break;
		case 1830:
			code = TigerDB::ROAD_BridlePath;
			break;
		}
		break;
	}

	return(code);
}

TigerDB::TigerDB(CDatabase *rDB, int stateFips) : GeoDB(1 << 11, 400, SEQUENTIAL/*PAGES*/)
{
	this->nLines = 0;
	this->db = rDB;
  assert( this->db != 0 );

	CString stateAbbr;
	switch (stateFips)
	{
	default:
		stateAbbr = "??";
		break;

	case 23:
		stateAbbr = "ME";
		break;
	case 25:
		stateAbbr = "MA";
		break;
	}

	this->names = new DistNames(stateAbbr, this->db);
  assert( this->names != 0 );
	this->names->nameParam = "";
	this->names->m_strFilter = _T("(NAME = ?)");
	this->names->Open( CRecordset::forwardOnly, 0, CRecordset::readOnly );
	while( ! this->names->IsEOF() )
		this->names->MoveNext();

	this->nameById = new DistNames(stateAbbr, this->db );
  assert( this->nameById != 0 );
	this->nameById->idParam = 0;
	this->nameById->m_strFilter = _T("(ID = ?)");
	this->nameById->Open( CRecordset::forwardOnly, 0, CRecordset::readOnly );
	while( ! this->nameById->IsEOF() )
		this->nameById->MoveNext();

	this->nameByFeatureId = new GNISName(this->db);
	this->nameByFeatureId->idParam = 0;
	this->nameByFeatureId->m_strFilter = _T("(feature_id = ?)");
	this->nameByFeatureId->Open(CRecordset::forwardOnly, 0, CRecordset::readOnly);
	while (!this->nameByFeatureId->IsEOF())
		this->nameByFeatureId->MoveNext();
}

TigerDB::~TigerDB()
{
	if (this->IsOpen())
	{
		this->Close();
	}
/*
	if( this->lines != 0 )
    delete [] this->lines;
*/
	assert( this->names != 0 );
	delete this->names;

	assert( this->nameById != 0 );
	delete this->nameById;
}

int TigerDB::Close( void )
{
	assert( this->names != 0 );
	if( this->names->IsOpen() )
	{
		this->names->Close();
	}

	assert( this->nameById != 0 );
	if( this->nameById->IsOpen() )
	{
		this->nameById->Close();
	}

	return( this->GeoDB::Close() );
}

// Override this method when you have extended GeoDB base classes such as Node, Edge, Point or Poly
DbObject *TigerDB::CreateDbObject( DbObject::ClassCode code )
{
	DbObject* object = 0;
	switch( code )
  {
    default :
		  return( this->GeoDB::CreateDbObject( code ) );

		case DB_EDGE:
			object = new Chain;
			this->nLines++;
#ifdef SAVE_FOR_NOW
      if( this->nLines < MAX_TIGER_LINES )
		  {
	    	object = (DbObject *)&this->lines[ this->nLines ];
	    	this->nLines++;
	    	return( object );
      }
#endif
      break;

		case DB_POLY:
			object = new TigerDB::Polygon;
			break;

		case DB_POINT:
			object = new TigerDB::GNISFeature;
#ifdef SAVE_FOR_NOW
			static int nPoints = 0;  // Temp
			if (nPoints++ < 100)
			{
				object = new TigerDB::GNISFeature;
				return object;
			}
#endif
			break;
  }

  return object;
}

void TigerDB::DeleteDbObject( DbObject::ClassCode code, DbObject *dbo )
{
  DbObject *object = dbo;

  switch( code )
  {
    default :
		  this->GeoDB::DeleteDbObject( code, dbo );
      break;

		case DB_EDGE : 
      assert( this->nLines > 0 );
      if( this->nLines > 0 )
		  {
	    	--this->nLines;
      }
      break;       
  }
}


TCHAR* TigerDB::MapStateFipsAbbrev(int stateFips)
{
	TCHAR* abbrev = 0;

	switch (stateFips)
	{
	default:
		break;
	case ACSSurveyData::AL:
		abbrev = _T("AL");
		break;
	case ACSSurveyData::AK:
		abbrev = _T("AK");
		break;
	case ACSSurveyData::AZ:
		abbrev = _T("AZ");
		break;
	case ACSSurveyData::AR:
		abbrev = _T("AR");
		break;
	case ACSSurveyData::CA:
		abbrev = _T("CA");
		break;
	case ACSSurveyData::CO:
		abbrev = _T("CO");
		break;
	case ACSSurveyData::CT:
		abbrev = _T("CT");
		break;
	case ACSSurveyData::DE:
		abbrev = _T("DE");
		break;
	case ACSSurveyData::DC:
		abbrev = _T("DC");
		break;
	case ACSSurveyData::FL:
		abbrev = _T("FL");
		break;
	case ACSSurveyData::GA:
		abbrev = _T("GA");
		break;
	case ACSSurveyData::HI:
		abbrev = _T("HI");
		break;
	case ACSSurveyData::ID:
		abbrev = _T("ID");
		break;
	case ACSSurveyData::IL:
		abbrev = _T("IL");
		break;
	case ACSSurveyData::INDIANA:
		abbrev = _T("IN");
		break;
	case ACSSurveyData::IA:
		abbrev = _T("IA");
		break;
	case ACSSurveyData::KS:
		abbrev = _T("KS");
		break;
	case ACSSurveyData::KY:
		abbrev = _T("KY");
		break;
	case ACSSurveyData::LA:
		abbrev = _T("LA");
		break;
	case ACSSurveyData::ME:
		abbrev = _T("ME");
		break;
	case ACSSurveyData::MD:
		abbrev = _T("MD");
		break;
	case ACSSurveyData::MA:
		abbrev = _T("MA");
		break;
	case ACSSurveyData::MI:
		abbrev = _T("MI");
		break;
	case ACSSurveyData::MN:
		abbrev = _T("MN");
		break;
	case ACSSurveyData::MS:
		abbrev = _T("MS");
		break;
	case ACSSurveyData::MO:
		abbrev = _T("MO");
		break;
	case ACSSurveyData::MT:
		abbrev = _T("MT");
		break;
	case ACSSurveyData::NE:
		abbrev = _T("NE");
		break;
	case ACSSurveyData::NV:
		abbrev = _T("NV");
		break;
	case ACSSurveyData::NH:
		abbrev = _T("NH");
		break;
	case ACSSurveyData::NJ:
		abbrev = _T("NJ");
		break;
	case ACSSurveyData::NM:
		abbrev = _T("NM");
		break;
	case ACSSurveyData::NY:
		abbrev = _T("NY");
		break;
	case ACSSurveyData::NC:
		abbrev = _T("NC");
		break;
	case ACSSurveyData::ND:
		abbrev = _T("ND");
		break;
	case ACSSurveyData::OH:
		abbrev = _T("OH");
		break;
	case ACSSurveyData::OK:
		abbrev = _T("OK");
		break;
	case ACSSurveyData::OR:
		abbrev = _T("OR");
		break;
	case ACSSurveyData::PA:
		abbrev = _T("PA");
		break;
	case ACSSurveyData::RI:
		abbrev = _T("RI");
		break;
	case ACSSurveyData::SC:
		abbrev = _T("SC");
		break;
	case ACSSurveyData::SD:
		abbrev = _T("SD");
		break;
	case ACSSurveyData::TN:
		abbrev = _T("TN");
		break;
	case ACSSurveyData::TX:
		abbrev = _T("TX");
		break;
	case ACSSurveyData::UT:
		abbrev = _T("UT");
		break;
	case ACSSurveyData::VT:
		abbrev = _T("VT");
		break;
	case ACSSurveyData::VI:
		abbrev = _T("VI");
		break;
	case ACSSurveyData::WA:
		abbrev = _T("WA");
		break;
	case ACSSurveyData::WV:
		abbrev = _T("WV");
		break;
	case ACSSurveyData::WI:
		abbrev = _T("WI");
		break;
	case ACSSurveyData::WY:
		abbrev = _T("WY");
		break;
	}

	return abbrev;
}

int TigerDB::MapStateAbbrevFipsCode(const TCHAR* abbrev)
{
	int stateFips = 0;
	switch (abbrev[0])
	{
	case _T('A'):
	case _T('a'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('L'):
		case _T('l'):
			stateFips = ACSSurveyData::AL;
			break;
		case _T('K'):
		case _T('k'):
			stateFips = ACSSurveyData::AK;
			break;
		case _T('Z'):
		case _T('z'):
			stateFips = ACSSurveyData::AZ;
			break;
		case _T('R'):
		case _T('r'):
			stateFips = ACSSurveyData::AR;
			break;
		}
		break;

	case _T('C'):
	case _T('c'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('A'):
		case _T('a'):
			stateFips = ACSSurveyData::CA;
			break;
		case _T('O'):
		case _T('o'):
			stateFips = ACSSurveyData::CO;
			break;
		case _T('T'):
		case _T('t'):
			stateFips = ACSSurveyData::CT;
			break;
		case _T('R'):
		case _T('r'):
			stateFips = ACSSurveyData::AR;
			break;
		}
		break;

	case _T('D'):
	case _T('d'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('E'):
		case _T('e'):
			stateFips = ACSSurveyData::DE;
			break;
		case _T('C'):
		case _T('c'):
			stateFips = ACSSurveyData::DC;
			break;
		}
		break;

	case _T('F'):
	case _T('f'):
		if (abbrev[1] == _T('L') || abbrev[1] == _T('l'))
			stateFips = ACSSurveyData::FL;
		break;

	case _T('G'):
	case _T('g'):
		if (abbrev[1] == _T('A') || abbrev[1] == _T('a'))
			stateFips = ACSSurveyData::GA;
		break;

	case _T('H'):
	case _T('h'):
		if (abbrev[1] == _T('I') || abbrev[1] == _T('i'))
			stateFips = ACSSurveyData::HI;
		break;

	case _T('I'):
	case _T('i'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('D'):
		case _T('d'):
			stateFips = ACSSurveyData::ID;
			break;
		case _T('L'):
		case _T('i'):
			stateFips = ACSSurveyData::IL;
			break;
		case _T('N'):
		case _T('n'):
			stateFips = ACSSurveyData::INDIANA;
			break;
		case _T('A'):
		case _T('a'):
			stateFips = ACSSurveyData::IA;
			break;
		}
		break;

	case _T('K'):
	case _T('k'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('S'):
		case _T('s'):
			stateFips = ACSSurveyData::KS;
			break;
		case _T('Y'):
		case _T('y'):
			stateFips = ACSSurveyData::KY;
			break;
		}
		break;

	case _T('L'):
	case _T('l'):
		if (abbrev[1] == _T('A') || abbrev[1] == _T('a'))
			stateFips = ACSSurveyData::LA;
		break;

	case _T('M'):
	case _T('m'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('E'):
		case _T('e'):
			stateFips = ACSSurveyData::ME;
			break;
		case _T('D'):
		case _T('d'):
			stateFips = ACSSurveyData::MD;
			break;
		case _T('A'):
		case _T('a'):
			stateFips = ACSSurveyData::MA;
			break;
		case _T('I'):
		case _T('i'):
			stateFips = ACSSurveyData::MI;
			break;
		case _T('N'):
		case _T('n'):
			stateFips = ACSSurveyData::MN;
			break;
		case _T('S'):
		case _T('s'):
			stateFips = ACSSurveyData::MS;
			break;
		case _T('O'):
		case _T('o'):
			stateFips = ACSSurveyData::MO;
			break;
		case _T('T'):
		case _T('t'):
			stateFips = ACSSurveyData::MT;
			break;
		}
		break;

	case _T('N'):
	case _T('n'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('E'):
		case _T('e'):
			stateFips = ACSSurveyData::NE;
			break;
		case _T('V'):
		case _T('v'):
			stateFips = ACSSurveyData::NV;
			break;
		case _T('H'):
		case _T('h'):
			stateFips = ACSSurveyData::NH;
			break;
		case _T('J'):
		case _T('j'):
			stateFips = ACSSurveyData::NJ;
			break;
		case _T('M'):
		case _T('m'):
			stateFips = ACSSurveyData::NM;
			break;
		case _T('Y'):
		case _T('y'):
			stateFips = ACSSurveyData::NY;
			break;
		case _T('C'):
		case _T('c'):
			stateFips = ACSSurveyData::NC;
			break;
		case _T('D'):
		case _T('d'):
			stateFips = ACSSurveyData::ND;
			break;
		}
		break;

	case _T('O'):
	case _T('o'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('H'):
		case _T('h'):
			stateFips = ACSSurveyData::OH;
			break;
		case _T('K'):
		case _T('k'):
			stateFips = ACSSurveyData::OK;
			break;
		case _T('R'):
		case _T('r'):
			stateFips = ACSSurveyData::OR;
			break;
		}
		break;

	case _T('P'):
	case _T('p'):
		if (abbrev[1] == _T('A') || abbrev[1] == _T('a'))
			stateFips = ACSSurveyData::PA;
		break;

	case _T('R'):
	case _T('r'):
		if (abbrev[1] == _T('I') || abbrev[1] == _T('i'))
			stateFips = ACSSurveyData::RI;
		break;

	case _T('S'):
	case _T('s'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('C'):
		case _T('c'):
			stateFips = ACSSurveyData::SC;
			break;
		case _T('D'):
		case _T('d'):
			stateFips = ACSSurveyData::SD;
			break;
		}
		break;

	case _T('T'):
	case _T('t'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('N'):
		case _T('n'):
			stateFips = ACSSurveyData::TN;
			break;
		case _T('X'):
		case _T('x'):
			stateFips = ACSSurveyData::TX;
			break;
		}
		break;

	case _T('U'):
	case _T('u'):
		if (abbrev[1] == _T('T') || abbrev[1] == _T('t'))
			stateFips = ACSSurveyData::UT;
		break;

	case _T('V'):
	case _T('v'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('T'):
		case _T('t'):
			stateFips = ACSSurveyData::VT;
			break;
		case _T('I'):
		case _T('i'):
			stateFips = ACSSurveyData::VI;
			break;
		}
		break;

	case _T('W'):
	case _T('w'):
		switch (abbrev[1])
		{
		default:
			break;
		case _T('A'):
		case _T('a'):
			stateFips = ACSSurveyData::WA;
			break;
		case _T('V'):
		case _T('v'):
			stateFips = ACSSurveyData::WV;
			break;
		case _T('I'):
		case _T('i'):
			stateFips = ACSSurveyData::WI;
			break;
		case _T('Y'):
		case _T('y'):
			stateFips = ACSSurveyData::WY;
			break;
		}
		break;
	}

	return stateFips;
}
