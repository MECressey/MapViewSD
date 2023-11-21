#include "pch.h"
#include "afxwin.h"
#include "drawline.hpp"
#include "atltypes.h"

#include "gdiplusgraphics.h"

static CPoint cpts[ 10000 ];

void DrawLine( const Transform &transform, CDC *dc, XY_t pts[], int nPts )
{
  XY_t pt;
  CPoint cPt;

  for( int i = 0; i < nPts; i++ )
  {
 	  transform.Forward( &pt, pts[ i ] );
	  cPt.x = (int)pt.x;
 	  cPt.y = (int)pt.y;
	  cpts[ i ] = cPt;
  }

  dc->Polyline( cpts, nPts );
/*
  transform.Forward( &pt, pts[ 0 ] );
  cPt.x = (int)pt.x;
  cPt.y = (int)pt.y;
  dc->MoveTo( cPt );
  for( int i = 1; i < nPts; i++ )
  {
 	transform.Forward( &pt, pts[ i ] );
	cPt.x = (int)pt.x;
 	cPt.y = (int)pt.y;
	dc->LineTo( cPt );
  }
*/
}

void DrawPolygon(const Transform& transform, CDC* dc, XY_t pts[], int nPts)
{
  XY_t pt;
  CPoint cPt;

  //Graphics* pGraphics = FromHDC(dc);

  for (int i = 0; i < nPts; i++)
  {
    transform.Forward(&pt, pts[i]);
    cPt.x = (int)pt.x;
    cPt.y = (int)pt.y;
    cpts[i] = cPt;
  }

  dc->Polygon(cpts, nPts);
}
