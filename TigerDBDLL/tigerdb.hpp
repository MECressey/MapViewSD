///////////////////////////////////////////////////////////////////////////////
//
//	TIGERDB.HPP - declarations for the Geographic Database.
//
//	Copyright (c) 1992-1996, Object-Based Technologies, Topsham, ME, USA.
//	All rights reserved.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <tchar.h>
#include "geodb.hpp"
#include <vector>
#include <string>
//#include "dac.hpp"

class CDatabase;
class DistNames;
class GNISName;

//extern /*__declspec(dllexport)*/ SetRelation POLY_EDGE;

//extern /*__declspec(dllexport)*/ SetRelation EDGE_POLY;

//using namespace NodeEdgePoly;

class  __declspec(dllexport) TigerDB : public NodeEdgePoly::GeoDB
{
	public:
		enum Classification
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
			ROAD_OtherThoroughfare,
			RR_MajorCategoryUnknown,
			RR_MainLine,
			RR_Spur,
			RR_Yard,
			RR_SpecialCharacteristics,
			RR_OtherThoroughfare,
			MGT_CategoryUnknown,
			MGT_Pipeline,
			MGT_PowerLine,
			MGT_SpecialCharacteristics,
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
			LM_TransportationTerminal,
			LM_Airport,
			LM_TrainStation,
			LM_BusTerminal,
			LM_MarineTerminal,
			LM_SeaplaneAnchorage,
			LM_Employmentcenter,
			LM_ShoppingOrRetailCenter,
			LM_IndustrialBuildingOrPark,
			LM_OfficebuildingOrPark,
			LM_AmusementCenter,
			LM_GovernmentCenter,
			LM_OtherEmploymentCenter,
			LM_Tower,
			LM_LookoutTower,
			LM_OpenSpace,
			LM_GolfCourse,
			LM_Cemetery,
			LM_NationalParkOrForest,
			LM_OtherFederalLand,
			LM_StateOrLocalPark_Forest,
			LM_SpecialPurpose,
			PF_CategoryUnknown,
			PF_Fenceline,
			PF_TopographicFeature,
			PF_RidgeLine,
			PF_MountainPeak,
			NVF_BoundaryClassificationUnknown,
			NVF_LegalOrAdministrativeBoundary,
			NVF_ClosureExtension,
			NVF_SeparationLine,
			NVF_Centerline,
			NVF_PropertyLine,
			NVF_ZIPCodeBoundary,
			NVF_StatisticalBoundary,
			NVF_OtherTabulationBoundary,
			NVF_WaterAreaDefinitionBoundary,
			NVF_USGSClosureLine,
			NVF_CensusWaterBoundary3Mile,
			NVF_CensusWaterBoundary12Mile,
			HYDRO_ClassificationUnknown,
			HYDRO_PerennialShoreline,
			HYDRO_IntermittentShoreline,
			HYDRO_PerennialStream,
			HYDRO_IntermittentStream,
			HYDRO_PerennialCanalDitchOrAqueduct,
			HYDRO_IntermittentCanalDitchOrAqueduct,
			HYDRO_PerennialLakeOrPond,
			HYDRO_IntermittentLakeOrPond,
			HYDRO_PerennialReservoir,
			HYDRO_IntermittentReservoir,
			HYDRO_BayEstuaryGulfOrSound,
			HYDRO_SeaOrOcean,
			HYDRO_GravelPitOrQuarry,
			HYDRO_Glacier,
			LM_POBox_ZipCode,
			LM_Urbanizacion,
			PF_Island,
			HYDRO_BraidedStream,
			NVF_CensusWaterCenterLine,
			NVF_ArtificialPath
		};

		enum GNISFeatures
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

		class Name
		{
			public :
				Name( void );
				char /*TCHAR*/ prefix[3];
				char /*TCHAR*/ name[41];
				char /*TCHAR*/ type[5];
				char /*TCHAR*/ suffix[3];
		};

		class __declspec(dllexport) Chain : public GeoDB::Edge, public DbHashAccess
		{
			public :
				Chain( void );
				~Chain( void );
				unsigned GetNumNames( void ) const;
				void GetName( Name *, int ) const;
				void SetName( Name lineNames[], int );

				int is_equal(DbObject*);
				long int hashKey(int nBits);

				virtual void Init(void);

			protected :
		    virtual void Compress( void * );
		    virtual void Decompress( void *, int );
		    virtual unsigned DiskSize( void );

			private :
				struct TName
				{
					long nameId;
					unsigned char prefixCode;
					unsigned char suffixCode;
					unsigned char typeCode;
				};
		//
		//	Used only for getting/setting the records
				unsigned char nNames;
				TName names[ 5 ];
				//unsigned char code;
				//long tlid;	// Tiger LineID
		};

		class __declspec(dllexport) Polygon : public GeoDB::Poly
		{
		public:
			Polygon(void);
			~Polygon(void);

			void SetName(std::string);
			std::string GetName(void) const;

			//int GetCode(void) const;
			//void SetCode(int code);
			//double GetArea(void) const;
			//void SetArea(double);
			//int Level(int*);

			//static int GetPts(ObjHandle &, XY_t[]);

			//int AddEdge(ObjHandle& eh, unsigned char dir);

			//int matchPoly(ObjHandle&, std::vector<DirLineId>& polyLines, int start, int end);

			//SetSllOwner poly_epl;

			//static SetRelation POLY_EDGE;
			virtual void Init(void);

		protected:
			virtual void Compress(void*);
			virtual void Decompress(void*, int);
			virtual unsigned DiskSize(void);

		private:
			char name[31];
		//	unsigned char code;
		//	double area;
		};

		class __declspec(dllexport) GNISFeature : public GeoDB::Point
		{
		public:
			GNISFeature(void);
			~GNISFeature(void);

			std::string GetName(void);
			virtual void Init(void);

		protected:
			/*virtual void Compress(void*);
			virtual void Decompress(void*, int);
			virtual unsigned DiskSize(void);*/

		private:
			std::string name;
		};

		TigerDB( CDatabase * );
		~TigerDB( void );
		int Close( void );

	private :
		DbObject *CreateDbObject( DbObject::ClassCode );
		void DeleteDbObject( DbObject::ClassCode, DbObject * );
		
		Chain *lines;
		unsigned nLines;
		CDatabase *db;
		DistNames *names;
		DistNames *nameById;
		GNISName *nameByFeatureId;
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
/*
inline int TigerDB::Chain::GetCode( void ) const
{
	return( this->code );
}

inline void TigerDB::Chain::SetCode( int Code )
{
	this->code = Code;
}
*/
/*
inline void TigerDB::Chain::SetTLID(long tlid)
{
	this->tlid = tlid;
}

inline long TigerDB::Chain::GetTLID(void) const
{
	return(this->tlid);
}
*/
/*
inline int TigerDB::Polygon::GetCode(void) const
{
	return(this->code);
}

inline void TigerDB::Polygon::SetCode(int Code)
{
	this->code = Code;
}

inline int TigerDB::EdgePolyLink::GetCode(void) const
{
	return(this->code);
}

inline void TigerDB::EdgePolyLink::SetCode(int Code)
{
	this->code = Code;
}

inline unsigned char TigerDB::EdgePolyLink::GetDir(void) const
{
	return(this->dir);
}

inline void TigerDB::EdgePolyLink::SetDir(unsigned char dir)
{
	this->dir = dir;
}

inline double TigerDB::Polygon::GetArea(void) const { return this->area;  }
inline void TigerDB::Polygon::SetArea(double a) { this->area = a; }
*/
