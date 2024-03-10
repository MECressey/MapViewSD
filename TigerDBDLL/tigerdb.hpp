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
			ROAD_ServiceDrive,
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
			HYDRO_BraidedStream,  // H13
			HYDRO_CanalDitchAqeductUnknownMinor, // H20
			HYDRO_PerennialCanalDitchOrAqueduct,  // H21
			HYDRO_IntermittentCanalDitchOrAqueduct,
			HYDRO_PerennialLakeOrPond,
			HYDRO_IntermittentLakeOrPond,
			HYDRO_PerennialReservoir,
			HYDRO_IntermittentReservoir,
			HYDRO_TreatmentPond,
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
			HYDRO_Glacier		// H81
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
