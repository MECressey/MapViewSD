//
//	DrawLine.cpp - implementation of some methods use to draw objects in MapViewSD.
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
#include "afxwin.h"
#include "drawline.hpp"
#include "atltypes.h"

#include "gdiplusgraphics.h"

static CPoint cpts[80000];    // This should not be hard-coded!

void DrawMarker(CPoint &pt, CDC* dc)
{
  CPoint newPt;
  const int pixels = 10;

  newPt.x = pt.x - pixels;
  newPt.y = pt.y;
  dc->MoveTo(newPt);
  newPt.x = pt.x + pixels;
  dc->LineTo(newPt);

  newPt.x = pt.x;
  newPt.y = pt.y - pixels;
  dc->MoveTo(newPt);
  newPt.y = pt.y + pixels;
  dc->LineTo(newPt);
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
}

void DrawPolygon(const Transform& transform, CDC* dc, XY_t pts[], int nPts)
{
  XY_t pt;
  CPoint cPt;

  for (int i = 0; i < nPts; i++)
  {
    transform.Forward(&pt, pts[i]);
    cPt.x = (int)pt.x;
    cPt.y = (int)pt.y;
    cpts[i] = cPt;
  }

  dc->Polygon(cpts, nPts);
}
