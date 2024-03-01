//
//	trgtypes.h - some utility methods for handling Tiger names.
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

#if defined(__cplusplus)
//extern "C" {
#endif

struct FieldDef
{
	const /*wchar_t*/ TCHAR *field;
	const /*wchar_t*/ TCHAR* abbrev;
};

FieldDef *TigerGetPrefix( unsigned char code );

int TigerGetPrefixCode( const TCHAR* abbrev);

FieldDef *TigerGetType( unsigned char code );

int TigerGetTypeCode( const TCHAR * abbrev);

#if defined(__cplusplus)
//}
#endif

