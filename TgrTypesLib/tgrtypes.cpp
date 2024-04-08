//
//	trgtypes.cpp - some utility methods for handling Tiger names.
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
#include <string.h>
#include <tchar.h>

#include "tgrtypes.h"

#if defined(__cplusplus)
//extern "C" {
#endif

static FieldDef prefixes[] =
{
	{ _T(""),						_T("") },
	{ _T("East"),				_T("E") },
	{ _T("North"),			_T("N") },
	{ _T("Northeast"),	_T("NE") },
	{ _T("Northwest"),	_T("NW") },
	{ _T("South"),			_T("S")	},
	{ _T("Southeast"),	_T("SE") },
	{ _T("Southwest"),	_T("SW") },
	{ _T("West"),				_T("W") }
};

FieldDef *TigerGetPrefix( unsigned char code )
{
	if( code < sizeof( prefixes ) / sizeof( prefixes[ 0 ] ) )
	{
		return( &prefixes[ code ] );
	}
	
	return( 0 );
}

int TigerGetPrefixCode( const TCHAR * abbrev)
{
	FieldDef *prefix = prefixes;

	for( int i = 0; i < sizeof( prefixes ) / sizeof( prefixes[ 0 ] ); i++ )
	{
		if( ::_tcscmp( prefix->abbrev, abbrev ) == 0 )
			return( i );
		prefix++;
	}

	return( -1 );
}

static FieldDef types[] =
{
	{ _T(""),						_T("") },				// zero is undefined
	{ _T("ACCESS"),			_T("Acss") },		// MEC
	{ _T("ACRE"),				_T("Acre") },
	{ _T("ACRES"),			_T("Acrs") },		// MEC
	{ _T("AIRFIELD"),		_T("Arfd") },		// MEC
	{ _T("AIRSTRIP"),		_T("Arsp") },		// MEC
	{ _T("AIRPORT"),		_T("Arpt") },		// MEC
	{ _T("ALLEY"),			_T("Aly") },
	{ _T("ANNEX"),			_T("Anx") },
	{ _T("APARTMENTS"),	_T("Apts") },		// MEC
	{ _T("ARCADE"),			_T("Arc") },
	{ _T("AVENUE"),			_T("Ave") },
	{ _T("AVE"),				_T("Ave") },
	{ _T("BASIN"),			_T("Bsn") },		// MEC
	{ _T("BAY"),				_T("Bay") },		// MEC
	{ _T("BAYOU"),			_T("Byu") },
	{ _T("BYU"),				_T("Byu") },
	{ _T("BEACH"),			_T("Bch") },
	{ _T("BEND"),				_T("Bnd") },
	{ _T("BLUFF"),			_T("Blf") },
	{ _T("BOG"),				_T("Bog") },		// MEC
	{ _T("BOTTOM"),			_T("Btm") },
	{ _T("BOUNDARY"),		_T("Bdry") },		// MEC
	{ _T("BOULEVARD"),	_T("Blvd") },
	{ _T("BRANCH"),			_T("Br") },
	{ _T("BRIDGE"),			_T("Brg") },
	{ _T("BROOK"),			_T("Brk") },
	{ _T("BROOKS"),			_T("Brks") },		// MEC
	{ _T("BURG"),				_T("Bg") },
	{ _T("BYPASS"),			_T("Byp") },
	{ _T("Calle"),			_T("C") },			// Tiger
	{ _T("CAMP"),				_T("Cp") },
	{ _T("CANAL"),			_T("Cnl") },		// MEC
	{ _T("CANYON"),			_T("Cyn") },
	{ _T("CAPE"),				_T("Cpe") },
	{ _T("CAUSEWAY"),		_T("Cswy") },
	{ _T("CENTER"),			_T("Ctr") },
	{ _T("CIRCLE"),			_T("Cir") },
	{ _T("CLIFFS"),			_T("Clfs") },
	{ _T("CLUB"),				_T("Clb") },
	{ _T("COMMON"),			_T("Cmn") },			// MEC
	{ _T("COMMONS"),		_T("Cmns") },			// MEC
	{ _T("CONDOMINIUM"),		_T("Cndo") },	// MEC
	{ _T("CONDOMINIUMS"),		_T("Cnds") },	// MEC
	{ _T("CONNECTOR"),		_T("Cntr") },		// MEC
	{ _T("CORNER"),			_T("Cor") },
	{ _T("CORNERS"),		_T("Cors") },
	{ _T("COTTAGES"),		_T("Ctgs") },		// MEC
	{ _T("COURSE"),			_T("Crse") },
	{ _T("CRSE"),				_T("Crse") },
	{ _T("COURT"),			_T("Ct") },
	{ _T("COURTS"),			_T("Cts") },
	{ _T("COVE"),				_T("Cv") },
	{ _T("CREEK"),			_T("Crk") },
	{ _T("CRESCENT"),		_T("Cres") },
	{ _T("CREST"),			_T("Crst") },		// MEC
	{ _T("CROSSING"),		_T("Xing") },
	{ _T("CROSSROAD"),	_T("Csrd") },		// MEC
	{ _T("DALE"),				_T("Dl") },
	{ _T("DAM"),				_T("Dm") },
	{ _T("DIVIDE"),			_T("Dv") },
	{ _T("DRIVE"),			_T("Dr") },
	{ _T("DRIVEWAY"),		_T("Drwy") },		// MEC
	{ _T("ENTRANCE"),		_T("Entr") },		// MEC
	{ _T("ESTATES"),		_T("Ests") },
	{ _T("EXPRESSWAY"),	_T("Expy") },
	{ _T("EXTENSION"),	_T("Ext") },
	{ _T("FAIRGROUNDS"),	_T("Frgd") },		// MEC
	{ _T("FALL"),				_T("Fall") },
	{ _T("FALLS"),			_T("Fls") },
	{ _T("FERRY"),			_T("Fry") },
	{ _T("FIELD"),			_T("Fld") },
	{ _T("FIELDS"),			_T("Flds") },
	{ _T("FLATS"),			_T("Flt") },
	{ _T("FLOWAGE"),		_T("Flwg") },		// MEC
	{ _T("FORD"),				_T("Frd") },
	{ _T("FOREST"),			_T("Frst") },
	{ _T("FORGE"),			_T("Frg") },
	{ _T("FORK"),				_T("Frk") },
	{ _T("FORKS"),			_T("Frks") },
	{ _T("FORT"),				_T("Ft") },
	{ _T("FREEWAY"),		_T("Fwy") },
	{ _T("GARDENS"),		_T("Gdns") },
	{ _T("GLADE"),			_T("Gld") },		// MEC
	{ _T("GLEN"),				_T("Gln") },
	{ _T("GREEN"),			_T("Grn") },
	{ _T("GROVE"),			_T("Grv") },
	{ _T("HARBOR"),			_T("Hbr") },
	{ _T("HAVEN"),			_T("Hvn") },
	{ _T("HEATH"),			_T("Hth") },		// MEC
	{ _T("HEIGHTS"),		_T("Hts") },
	{ _T("HIGHWAY"),		_T("Hwy") },
	{ _T("HILL"),				_T("Hl") },
	{ _T("HILLS"),			_T("Hls") },
	{ _T("HOLLOW"),			_T("Holw") },
	{ _T("INLET"),			_T("Inlt") },
	{ _T("ISLAND"),			_T("Is") },
	{ _T("ISLANDS"),		_T("Iss") },
	{ _T("JUNCTION"),		_T("Jct") },
	{ _T("KEY"),				_T("Ky") },
	{ _T("KNOLLS"),			_T("Knis") },
	{ _T("KNOLL"),			_T("Knll") },	// MEC
	{ _T("LAKE"),				_T("Lk") },
	{ _T("LAKES"),			_T("Lks") },
	{ _T("LANDING"),		_T("Lndg") },
	{ _T("LANE"),				_T("Ln") },
	{ _T("LEDGES"),			_T("Ldgs") },		// MEC
	{ _T("LIGHT"),			_T("Lgt") },
	{ _T("LINE"),				_T("Line") },		// MEC
	{ _T("LOAF"),				_T("Lf") },
	{ _T("LOCKS"),			_T("Lcks") },
	{ _T("LODGE"),			_T("Ldg") },
	{ _T("LOOP"),				_T("Loop") },
	{ _T("MALL"),				_T("Mall") },
	{ _T("MANOR"),			_T("Mnr") },
	{ _T("MARSH"),			_T("Mrsh") },		// MEC
	{ _T("MEADOWS"),		_T("Mdws") },
	{ _T("MILL"),				_T("Ml") },
	{ _T("MILLS"),			_T("Mls") },
	{ _T("MISSION"),		_T("Msn") },
	{ _T("MOTORWAY"),		_T("Mtwy") },		// Tiger
	{ _T("MOUNT"),			_T("Mt") },
	{ _T("MOUNTAIN"),		_T("Mtn") },
	{ _T("NECK"),				_T("Nck") },
	{ _T("ORCHARD"),		_T("Orch") },
	{ _T("OUTLET"),			_T("Otlt") },		// MEC
	{ _T("OVAL"),				_T("Oval") },
	{ _T("OVERLOOK"),		_T("Ovlk") },		// MEC
	{ _T("OVERPASS"),		_T("Ovps") },		//Tiger
	{ _T("PARK"),				_T("Park") },
	{ _T("PARKWAY"),		_T("Pky") },
	{ _T("PASS"),				_T("Pass") },
	{ _T("PATH"),				_T("Path") },
	{ _T("PIER"),				_T("Pier") },		// MEC
	{ _T("PIKE"),				_T("Pike") },
	{ _T("PINES"),			_T("Pnes") },
	{ _T("PLACE"),			_T("Pl") },
	{ _T("PLAIN"),			_T("Pln") },
	{ _T("PLAINS"),			_T("Plns") },
	{ _T("PLAZA"),			_T("Plz") },
	{ _T("POINT"),			_T("Pt") },
	{ _T("POND"),				_T("Pond") },		// MEC
	{ _T("PONDS"),			_T("Pnds") },		// MEC
	{ _T("PORT"),				_T("Prt") },
	{ _T("PRESERVE"),		_T("Prsv") },		// MEC
	{ _T("PROMENADE"),	_T("Prmd") },		// MEC
	{ _T("PRAIRIE"),		_T("Pr") },
	{ _T("RADIAL"),			_T("Radl") },
	{ _T("Ramp"),				_T("Ramp") },		// Tiger
	{ _T("RAILROAD"),		_T("RR") },			// MEC
	{ _T("RR"),					_T("RR") },			// MEC
	{ _T("RANCH"),			_T("Rnch") },
	{ _T("RAPIDS"),			_T("Rpds") },
	{ _T("REST"),				_T("Rst") },
	{ _T("RESERVOIR"),	_T("Rsvr") },		// MEC
	{ _T("RIDGE"),			_T("Rdg") },
	{ _T("RIVER"),			_T("Riv") },
	{ _T("ROAD"),				_T("Rd") },
	{ _T("ROUTE"),			_T("Rt") },			// MEC
	{ _T("ROW"),				_T("Row") },
	{ _T("RUN"),				_T("Run") },
	{ _T("RUE"),				_T("Rue") },		// Tiger
	{ _T("SCHOOL"),			_T("Schl") },		// MEC
	{ _T("SHOAL"),			_T("Shl") },
	{ _T("SHOALS"),			_T("Shls") },
	{ _T("SHORE"),			_T("Shr") },
	{ _T("SHORES"),			_T("Shrs") },
	{ _T("SIDING"),			_T("Sdg") },		// MEC
	{ _T("SKYWAY"),			_T("Skwy") },		// Tiger
	{ _T("SLOUG"),			_T("Sloug") },		// 2023
	{ _T("SPRING"),			_T("Spg") },
	{ _T("SPRINGS"),		_T("Spgs") },
	{ _T("STRIP"),			_T("Strp") },		// MEC
	{ _T("SQUARE"),			_T("Sq") },
	{ _T("STATION"),		_T("Sta") },
	{ _T("STREAM"),			_T("Strm") },
	{ _T("STREET"),			_T("St") },
	{ _T("SUMMIT"),			_T("Smt") },
	{ _T("SWAMP"),			_T("Swmp") },		// MEC
	{ _T("TERRACE"),		_T("Ter") },
	{ _T("THROUGHWAY"),	_T("Thwy") },		// Tiger
	{ _T("TRAFFICWAY"),	_T("Tfwy") },		// Tiger
	{ _T("TRACE"),			_T("Trce") },
	{ _T("TRACK"),			_T("Trak") },
	{ _T("TRAIL"),			_T("Trl") },
	{ _T("TRAILER"),		_T("Trlr") },
	{ _T("TUNNEL"),			_T("Tunl") },
	{ _T("TURNPIKE"),		_T("Tpke") },
	{ _T("UNION"),			_T("Un") },
	{ _T("UNDERPASS"),	_T("Unp") },		// Tiger
	{ _T("VALLEY"),			_T("Vly") },
	{ _T("VIADUCT"),		_T("Via") },
	{ _T("VIEW"),				_T("Vw") },
	{ _T("VILLAGE"),		_T("Vlg") },
	{ _T("VILLE"),			_T("Vl") },
	{ _T("VISTA"),			_T("Vis") },
	{ _T("WALK"),				_T("Walk") },
	{ _T("WALL"),				_T("Wall") },		// Tiger
	{ _T("Way"),				_T("Way") },
	{ _T("WELLS"),			_T("Wls") },
	{ _T("WHARF"),			_T("Whrf") },	// MEC
	{ _T("WOODS"),			_T("Wds") }		// MEC
};

FieldDef *TigerGetType( unsigned char code )
{
	if( code < sizeof( types ) / sizeof( types[ 0 ] ) )
	{
		return( &types[ code ] );
	}
	
	return( 0 );
}

int TigerGetTypeCode( const TCHAR * abbrev)
{
	FieldDef *type = types;

	for( int i = 0; i < sizeof( types ) / sizeof( types[ 0 ] ); i++ )
	{
		int cmp = ::wcscmp/*_tcscmp*/(type->abbrev, abbrev);
		if( cmp == 0 )
			return( i );
		type++;
	}

	return( -1 );
}

#if defined(__cplusplus)
//}
#endif
