#include "pch.h"
#include "afxwin.h"
#include "drawline.hpp"
#include "atltypes.h"

#include "gdiplusgraphics.h"

static CPoint cpts[ 10000 ];

void DrawMarker(CPoint &pt, CDC* dc)
{
  CPoint newPt;
  const int pixels = 20;

  newPt.x = pt.x - pixels;
  newPt.y = pt.y;
  dc->MoveTo(newPt);
  newPt.x = pt.x + pixels;
  dc->LineTo(newPt);

  newPt.x = pt.x;
  newPt.y = pt.y - pixels;
  dc->MoveTo(newPt);
  newPt.y = pt.y + pixels;
  dc->MoveTo(newPt);
}

void DrawLine( const Transform &transform, CDC *dc, XY_t pts[], int nPts, bool drawDir)
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
  if (drawDir)
  {
    DrawMarker(cpts[nPts - 1], dc);
  }

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
