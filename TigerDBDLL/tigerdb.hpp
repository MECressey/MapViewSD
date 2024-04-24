//
//	TIGERDB.HPP - declarations for the TigerDB custom database using the NodeEdgePoly class library.
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
#pragma once

#include <tchar.h>
#include "geodb.hpp"
#include <vector>
#include <string>

class CDatabase;
class DistNames;
class GNISName;

using namespace NodeEdgePoly;

class  __declspec(dllexport) TigerDB : public NodeEdgePoly::GeoDB
{
	public:
		enum MAFTCCodes {		// 2022 MAF/TIGER Feature Class codes
			FeatureNotClassified,
			ROAD_PrimaryRoad,								// S1100			Linear features
			ROAD_SecondaryRoad,							// S1200
			ROAD_LocalNeighborhoodRoad,			// S1400
			ROAD_VehicularTrail4WD,					// S1500
			ROAD_Ramp,											// S1630
			ROAD_ServiceDrive,							// S1640
			ROAD_Walkway,										// S1710
			ROAD_Stairway,									// S1720
			ROAD_Alley,											// S1730
			ROAD_PrivateRoad,								// S1740
			ROAD_InternalCensusBureau,			// S1750
			ROAD_ParkingLotRd,							// S1780
			ROAD_WinterTrail,								// S1810
			ROAD_BikePath,									// S1820
			ROAD_BridlePath,								// S1830
			HYDRO_Connector,								// H1100
			HYDRO_StreamRiver,							// H3010
			HYDRO_BraidedStream,						// H3013
			HYDRO_CanalDitchAqueduct,				// H3020
			TRANS_PierDock,									// K2432
      TRANS_RunwayTaxiWay,						// K2459
			MISC_Pipeline,									// L4010
			MISC_Powerline,									// L4020
			MISC_AerialTramway,							// L4031
			MISC_FenceLine,									// L4110
			MISC_RidgeLine,									// L4121
			MISC_Cliff,											// L4125
			MISC_PointToPoint,							// L4130
			MISC_PropertyLine,							// L4140
			MISC_Coastline,									// L4150
			MISC_FerryCrossing,							// L4165
			EDGE_NonvisibleLinearBoundary,	// P0001
			EDGE_PerennialShoreline,				// P0002
			EDGE_IntermittentShoreline,			// P0003
			EDGE_OtherNonVisible,						// P0004
			RAIL_Rail,											// R1011
			TOPO_Levee,											// C3024
			TOPO_JettyBreakwater,						// C3025
			TOPO_Dam,												// C3027
			TOPO_Island,										// C3023   Areal Features
			TOPO_Quarry,										// C3026
			TOPO_Tank,											// C3075
			TOPO_WindmillFarm,							// C3076
			TOPO_SolarFarm,									// C3077
			TAB_Nation,											// G1000
			TAB_CensusRegion,								// G1100
			TAB_CensusDivision,							// G1200
			TAB_AIA,												// G2100
			TAB_HH,													// G2120
			TAB_ANVSA,											// G2130
			TAB_OTSA,												// G2140
			TAB_SDTSA,											// G2150
			TAB_TDSA,												// G2160
			TAB_AIJUA,											// G2170
			TAB_AlaskaRegionalCorp,					// G2200
			TAB_TribalSubdivision,					// G2300
			TAB_TribalCensusTract,					// G2400
			TAB_TribalBlockGroup,						// G2410
			TAB_CombinedStatisicalArea,			// G3100
			TAB_MetroStatisticalArea,				// G3110
			TAB_MetropolitanDivision,				// G3120
			TAB_NewEnglandCityTown,					// G3200
			TAB_NewEnglandMetroStatArea,		// G3210
			TAB_NewEngland_CityTownDiv,			// G3220
			TAB_UrbanArea,									// G3500
			TAB_StateFeature,								// G4000
			TAB_CountyFeature,							// G4020
			TAB_CountySubdivision,					// G4040
			TAB_Estate,											// G4050
			TAB_SubMinorCivilDivision,			// G4060
			TAB_IncorporatedPlace,					// G4110
			TAB_ConsolidatedCity,						// G4120
			TAB_CensusDesignatedPlace,			// G4210
			TAB_EconomicCensusPlace,				// G4300
			TAB_CensusTract,								// G5020
			TAB_CensusBlockGroup,						// G5030
			TAB_Block,											// G5040
			TAB_CongressionalDistrict,			// G5200
			TAB_StateLegislativeDistrictUC,	// G5210
			TAB_StateLegislativeDistrictLC,	// G5220
			TAB_VotingDistrict,							// G5240
			TAB_ElementarySchoolDistrict,		// G5400
			TAB_SecondarySchoolDistrict,		// G5410
			TAB_UnifiedSchoolDistrict,			// G5420
			TAB_PUMA,												// G6120
			TAB_UrbanGrowthArea,						// G6330
			TAB_ZIPCodeArea,								// G6350
			TAB_PlanningRegion,							// G6400
			HYDRO_LakePond,									// H2030
			HYDRO_Reservoir,								// H2040
			HYDRO_TreatmentPond,						// H2041
			HYDRO_BayEstuaryGulfSound,			// H2051
			HYDRO_OceanSea,									// H2053
			HYDRO_Glacier,									// H2081
			LIVING_ApartmentBuilding,				// K1121
			LIVING_TrailerCourt,						// K1223
			LIVING_CrewOfVessel,						// K1225
			LIVING_HousingFacility,					// K1226
			LIVING_HotelMotelResort,				// K1227
			LIVING_Campground,							// K1228
			LIVING_ShelterMission,					// K1229
			LIVING_HospitalHospice,					// K1231
			LIVING_NursingHome,							// K1233
			LIVING_JuvenileInstitution, 		// K1235
			LIVING_DententionCenter,				// K1236
			LIVING_FederalPenitentiary,			// K1237
			LIVING_OtherCorrectional,				// K1238
			LIVING_ConventMonasteryRectory,	// K1239
			GOV_Governmental,								// K2100
			GOV_MilitaryInstallation,				// K2110
			GOV_CommunityCenter,						// K2146
      GOV_GovermentCenter,						// K2165
      GOV_ConventionCenter,						// K2167
			GOV_Park,												// K2180
			PARK_NationalParkService,				// K2181
			PARK_NationalForest,						// K2182
			PARK_TribalPark,								// K2183
			PARK_StateParkForest,						// K2184
			PARK_RegionalParkForest,				// K2185
			PARK_CountyParkForest,					// K2186
			PARK_CountySubdivionPark,				// K2187
			PARK_IncorporatedPlacePark,			// K2188
			PARK_PrivateParkForest,					// K2189
			PARK_OtherParkForest,						// K2190
			WORK_CommericalWorkPlace,				// K2300
			WORK_ShoppingCenter,						// K2361
			WORK_IndustrialBuildingPark,		// K2362
			WORK_OfficeBuildingPark,				// K2363
			WORK_FarmVineyardOrchard,				// K2364
			WORK_OtherEmploymentCenter,			// K2366
			WORK_TransportationTerminal,		// K2400
			TT_Marina,											// K2424  Transportation Terminal
			TT_PierDock,										// K2432
			TT_TrainStation,								// K2452
			TT_BusTerminal,									// K2453
			TT_MarineTerminal,							// K2454
			TT_SeaplaneAnchorage,						// K2455
			TT_Airport,											// K2457
			OTHERWP_UniversityCollege,			// K2540
			OTHERWP_SchoolAcademy,					// K2543
			OTHERWP_MuseumVistorCenter,			// K2545
			OTHERWP_GolfCourse,							// K2561
			OTHERWP_AmusementCenter,				// K2564
			OTHERWP_Cemetery,								// K2582
			OTHERWP_Zoo,										// K2586
			OTHERWP_PlaceOfWorkship,				// K3544
			TOPO_MountainPeakSummit,				// C3022	Point features
			TOPO_CulDeSac,									// C3061
			TOPO_TrafficCircle,							// C3062
			TOPO_Gate,											// C3066
			TOPO_TollBooth,									// C3067
			TOPO_Tower,											// C3071
			TOPO_LighthouseBeacon,					// C3074
			TOPO_Monument,									// C3078
			TOPO_BoundaryMonument,					// C3079
			TOPO_SurveyControlPoint,				// C3080
			TOPO_LocalityPoint,							// C3081
			TOPO_AlaskaNativeVillage,				// C3085
			GOV_PostOffice,									// K2191
			GOV_FireDepartment,							// K2193
			GOV_Library,										// K2195
			GOV_CityTownHall,								// K2196
			TRANS_AirportAirField,					// K2451
			TT_HelicopterLandingPad					// K2460
		};

		enum Classification			// Census Feature Class Codes (CFCC) for the Tiger chains
		{
			NotClassified,
			ROAD_MajorCategoryUnknown,
			ROAD_PrimaryLimitedAccess,
			ROAD_PrimaryUnlimitedAccess,
			ROAD_SecondaryAndConnecting,
			ROAD_LocalNeighborhoodAndRural,
			ROAD_VehicularTrail,
			ROAD_SpecialCharacteristics,
			ROAD_Cul_de_sac,
			ROAD_TrafficCircle,
			ROAD_AccessRamp,
			ROAD_ServiceDr,
			ROAD_FerryCrossing,
			ROAD_BarrierToTravel,   // New 2006 codes (2/19/2024)
			ROAD_InternalUSCensusBureau,
			ROAD_OtherThoroughfare,
			RR_MajorCategoryUnknown,
			RR_MainLine,
			RR_Spur,
			RR_Yard,
			RR_FerryCrossing,
			RR_OtherThoroughfare,
			MGT_CategoryUnknown,
			MGT_Pipeline,
			MGT_PowerLine,
			MGT_Other,
			MGT_AerialTramway,
			MGT_PierDock,
			LM_CategoryUnknown,
			LM_MilitaryInstallation,
			LM_MultihouseholdOrTransientQuarters,
			LM_ApartmentBuildingOrBoardingHouse,
			LM_MobileHomePark,
			LM_Marina,
			LM_CrewOfVessel,
			LM_HotelOrMotel,
			LM_Campground,
			LM_ShelterOrMission,
			LM_CustodialFacility,
			LM_Hospital,
			LM_HalfwayHouse,
			LM_NursingHome,
			LM_CountyHome,
			LM_Orphanage,
			LM_Jail,
			LM_FederalOrStatePrison,
			LM_EducationalOrReligiousInstitution,
			LM_SororityOrFraternity,
			LM_ConventOrMonastery,
			LM_EducationalInstitution,
			LM_ReligiousInstitution,
			LM_Museum,
			LM_CommunityCenter,
			LM_Library,
			LM_TransportationTerminal,
			LM_Airport,
			LM_TrainStation,
			LM_BusTerminal,
			LM_MarineTerminal,
			LM_SeaplaneAnchorage,
			LM_AirportIntermodelTransportationHub,
			LM_AirportStatisticalRepresentation,
			LM_ParkAndRide,
			LM_Employmentcenter,
			LM_ShoppingOrRetailCenter,
			LM_IndustrialBuildingOrPark,
			LM_OfficebuildingOrPark,
			LM_AmusementCenter,
			LM_GovernmentCenter,
			LM_OtherEmploymentCenter,
			LM_ConventionCenter,
			LM_Tower,
			LM_LookoutTower,
			LM_TransmissionTower,
			LM_WaterTower,
			LM_LighthouseBeacon,
			LM_Tank,
			LM_WindmillFarm,
			LM_SolarFarm,
			LM_MonumentMemorial,
			LM_SurveyBoundaryMemorial,
			LM_OpenSpace,
			LM_GolfCourse,
			LM_Cemetery,
			LM_NationalParkService,
			LM_NationalForestOrOther,
			LM_StateOrLocalPark_Forest,
			LM_Zoo,
			LM_VineyardWineryOrchard,
			LM_LandfillDump,
			LM_SpecialPurpose,
			LM_InternalUSCensusBureau,
			LM_Urbanizacion,  // Puerto Rico
			PF_CategoryUnknown,
			PF_Fenceline,
			PF_TopographicFeature,
			PF_RidgeLine,
			PF_MountainPeak,
			PF_Island,
			PF_Levee,
			PF_MarshSwamp,
			PF_QuarryMine,
			PF_Dam,
			NVF_BoundaryClassificationUnknown,
			NVF_LegalOrAdministrativeBoundary,
			NVF_DatabaseTopology, // F20
			NVF_FeatureExtension, // F21 & F22
			NVF_ClosureExtension,
			NVF_SeparationLine, // F24
			NVF_Centerline,
			NVF_PointToPointLine, // F30
			NVF_PropertyLine,  // F40
			NVF_PublicLandSurveySystem,
			NVF_ZIPCodeBoundary,
			NVF_InternalUSCensusBureau,  // F52, F82 & F86
			NVF_StatisticalBoundary,
			NVF_OtherTabulationBoundary,	// Generic
			NVF_SchoolDistrictBoundary,
			NVF_Census2000, // F83 to F85
			NVF_OregonUrbanAreaBoundary, // F87
			NVF_CurrentStatisticalAreaBoundary, // F88
			HYDRO_ClassificationUnknown,
			HYDRO_PerennialShoreline,
			HYDRO_IntermittentShoreline,
			HYDRO_PerennialStream,
			HYDRO_IntermittentStream,
			HYDRO_BraidedStr,  // H13
			HYDRO_CanalDitchAqeductUnknownMinor, // H20
			HYDRO_PerennialCanalDitchOrAqueduct,  // H21
			HYDRO_IntermittentCanalDitchOrAqueduct,
			HYDRO_PerennialLakeOrPond,
			HYDRO_IntermittentLakeOrPond,
			HYDRO_PerennialReservoir,
			HYDRO_IntermittentReservoir,
			HYDRO_TreatmentPd,
			HYDRO_BayEstuaryGulfOrSound,
			HYDRO_SeaOrOcean,
			HYDRO_GravelPitOrQuarry,
			HYDRO_WaterAreaDefinitionBoundary,  // H70
			HYDRO_USGSClosureLine,	// H71
			HYDRO_CensusWaterCenterLine, // H72
			HYDRO_CensusWaterBoundary3Mile,
			HYDRO_CensusWaterBoundary12Mile,
			HYDRO_WaterBoundaryInlandVsCoastal,	// H74?
			HYDRO_ArtificialPath,
			HYDRO_SpecialWaterFeature, // H80
			HYDRO_GlacierOld,		// H81
			ROAD_Runway_Taxiway // Tiger 2022
		};

		enum GNISFeatures			// GNIS feature class codes
		{
			GNIS_Arch,
			GNIS_Area,
			GNIS_Arroyo,
			GNIS_Bar,
			GNIS_Basin,
			GNIS_Bay,
			GNIS_Beach,
			GNIS_Bench,
			GNIS_Bend,
			GNIS_Canal,
			GNIS_Cape,
			GNIS_Census,
			GNIS_Channel,
			GNIS_Civil,
			GNIS_Cliff,
			GNIS_Crater,
			GNIS_Crossing,
			GNIS_Falls,
			GNIS_Flat,
			GNIS_Gap,
			GNIS_Glacier,
			GNIS_Gut,
			GNIS_Island,
			GNIS_Isthmus,
			GNIS_Lake,
			GNIS_Lava,
			GNIS_Levee,
			GNIS_Military,
			GNIS_Pillar,
			GNIS_Plain,
			GNIS_PopulatedPlace,
			GNIS_Range,
			GNIS_Rapids,
			GNIS_Reservoir,
			GNIS_Ridge,
			GNIS_Sea,
			GNIS_Slope,
			GNIS_Spring,
			GNIS_Stream,
			GNIS_Summit,
			GNIS_Swamp,
			GNIS_Valley,
			GNIS_Woods
		};
		
		class Name			// Feature Identifiers (Record Type 5)
		{
			public :
				Name( void );
				char /*TCHAR*/ prefix[3];		// FEDIRP
				char /*TCHAR*/ name[41];		// FENAME
				char /*TCHAR*/ type[5];			// FETYPE
				char /*TCHAR*/ suffix[3];		// FEDIRS
		};

		class __declspec(dllexport) Chain : public GeoDB::Edge, public DbHashAccess  // Tiger Chain class
		{
			public :
				Chain( void );
				~Chain( void );
				unsigned GetNumNames( void ) const;
				void GetName( Name *, int ) const;
				void SetName( Name lineNames[], int );

				int is_equal(DbObject*);				// DbHashAccess interface
				long int hashKey(int nBits);

				virtual void Init(void);

			protected :
		    virtual void Compress( void * );					// DbBaseStore interface
		    virtual void Decompress( void *, int );
		    virtual unsigned DiskSize( void );

			private :
				struct TName		// Links to the actual name in the SQL database
				{
					unsigned short nameId;
					unsigned char prefixCode;
					unsigned char suffixCode;
					unsigned char typeCode;
				};
				//
				//	Used only for getting/setting the records (these are stored on disk)
				unsigned char nNames;
				TName names[5];
		};

		class __declspec(dllexport) Polygon : public GeoDB::Poly
		{
		public:
			Polygon(void);
			~Polygon(void);

			void SetName(std::string);
			std::string GetName(void) const;

			virtual void Init(void);

		protected:
			virtual void Compress(void*);
			virtual void Decompress(void*, int);
			virtual unsigned DiskSize(void);

		private:
			char name[31];			// Using a member variable, not an ODBC source
		};

		class __declspec(dllexport) GNISFeature : public GeoDB::Point
		{
		public:
			GNISFeature(void);
			~GNISFeature(void);

			std::string GetName(void);
			virtual void Init(void);

		private:
			std::string name;
		};

		TigerDB(CDatabase *);		// Connection to a SQL database using ODBC
		~TigerDB(void);
		int Close( void );
		static MAFTCCodes MapMTFCC(const char* mtfcc);

	private :
		DbObject *CreateDbObject( DbObject::ClassCode );			// Override method to create objects
		void DeleteDbObject( DbObject::ClassCode, DbObject * );
		
		//Chain *lines;
		unsigned nLines;
		CDatabase *db;
		DistNames *names;						// CRecordset used to query the DistNames table by name
		DistNames *nameById;				// CRecordset used to query the DistNames table by Id
		GNISName *nameByFeatureId;	// CRecordset used to query the GNISNames table
		friend Chain;
};

inline TigerDB::Name::Name( void )
{
	this->prefix[ 0 ] = this->name[ 0 ] = this->type[ 0 ] = this->suffix[ 0 ] = '\0';
}

inline unsigned TigerDB::Chain::GetNumNames( void ) const
{
	return( this->nNames );
}
