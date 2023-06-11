#if ! defined( TGRTYPES_H )
#define TGRTYPES_H

#if defined(__cplusplus)
//extern "C" {
#endif
//#include <afxwin.h>

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


#endif
