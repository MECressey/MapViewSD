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

int nCpts = 1000;
static CPoint* cpts = new CPoint[1000]; /*[80000];    // This should not be hard-coded!*/

static void ResizeCPointArray(int size)
{
  if (size > nCpts)
  {
    delete[] cpts;
    nCpts = size;
    cpts = new CPoint[nCpts];
  }
}

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
  ResizeCPointArray(nPts);

  for( int i = 0; i < nPts; i++ )
  {
    XY_t pt;
    CPoint cPt;

 	  transform.Forward(&pt, pts[ i ] );
	  cPt.x = (int)pt.x;
 	  cPt.y = (int)pt.y;
	  cpts[ i ] = cPt;
  }

  dc->Polyline(cpts, nPts);
  if (drawDir)
  {
    DrawMarker(cpts[nPts - 1], dc);
  }
}

void DrawLine(const Transform &transform, CDC* dc, std::vector<XY_t>& pts, bool drawDir)
{
    ResizeCPointArray(pts.size());

    for (int i = 0; i < pts.size(); i++)
    {
        XY_t pt;
        CPoint cPt;

        transform.Forward(&pt, pts[i]);
        cPt.x = (int)pt.x;
        cPt.y = (int)pt.y;
        cpts[i] = cPt;
    }

    dc->Polyline(cpts, pts.size());
    if (drawDir)
    {
        DrawMarker(cpts[pts.size() - 1], dc);
    }
}

void DrawPolygon(const Transform& transform, CDC* dc, XY_t pts[], int nPts)
{
  XY_t pt;
  CPoint cPt;

  ResizeCPointArray(nPts);

  for (int i = 0; i < nPts; i++)
  {
    transform.Forward(&pt, pts[i]);
    cPt.x = (int)pt.x;
    cPt.y = (int)pt.y;
    cpts[i] = cPt;
  }

  dc->Polygon(cpts, nPts);
}

void DrawPolygon(const Transform &transform, CDC* dc, std::vector<XY_t>& pts)
{
  XY_t pt;
  CPoint cPt;

  ResizeCPointArray(pts.size());

  for (int i = 0; i < pts.size(); i++)
  {
    transform.Forward(&pt, pts[i]);
    cPt.x = (int)pt.x;
    cPt.y = (int)pt.y;
    cpts[i] = cPt;
  }

  dc->Polygon(cpts, pts.size());
}