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

TigerDB::TigerDB(CDatabase *rDB) : GeoDB(1 << 11, 400, SEQUENTIAL/*PAGES*/)
{
	this->nLines = 0;
	this->db = rDB;
  assert( this->db != 0 );

	this->names = new DistNames( this->db );
  assert( this->names != 0 );
	this->names->nameParam = "";
	this->names->m_strFilter = _T("(NAME = ?)");
	this->names->Open( CRecordset::forwardOnly, 0, CRecordset::readOnly );
	while( ! this->names->IsEOF() )
		this->names->MoveNext();

	this->nameById = new DistNames( this->db );
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
