//
//	MapViewSDView.h - interface of the CMapViewSDView class (generated by Visual Studio)
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

#include "mapwin.hpp"
#include "layerdlg.h"
#include "linedlg.h"
#include "GEODB.HPP"
#include "AcsSexAgeDialog.h"

class CMapViewSDView : public CView, protected GeoDB::SpatialObjectFilter
{
protected: // create from serialization only
	CMapViewSDView() noexcept;
	DECLARE_DYNCREATE(CMapViewSDView)

// Attributes
public:
	CMapViewSDDoc* GetDocument() const;

// Operations
public:
	MapWindow* mapWin;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMapViewSDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPen pens[13];
	CBrush hydroBrush,
				 parkBrush,
				 isleBrush,
				 placeBrush,
				 tractBrush,
				 bgBrush,
				 countyBrush,
				 faceBrush;
	CFont font;
	int			pan_overlap;
	double		zoom_factor;
	MapProjection* mapProjs[2];
	MapProjection* mapProj;
	XY_t* pts;
	BOOL doWindow,
		doPick,
		doInfo;
	CPoint pt;
	double sDist,
		tDist;
	CPen pen,
		hPen;
	CBrush brush;
	CRect rect;
	LineDlg* lineDlg;
	LayerDlg *layerDlg;
	int doProj;
	BOOL doTest;
	BOOL doThining;
	BOOL doShortPath;
	int pickCount;
	long startId;
	XY_t startPt;
	int startDir;
	double startDist;
	AcsSexAgeDialog *acsSexAgeDlg;

	void DoPan(double horizontal, double vertical);
	void DisplayInfo(TigerDB::Chain* line);
	void DisplayInfo(TigerDB::Polygon* poly);
	void DisplayInfo(TigerDB::GNISFeature* );

	CPen* GetPen(TigerDB::Chain *line/*int code*/);
	CBrush* GetBrush(int code);
	bool drawGNISFeature(int code);
	friend LayerDlg;

	virtual bool filter(GeoDB::SpatialObj *so);  // SpatialObjectFilter

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	//afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnPanDown();
	afx_msg void OnPanLeft();
	afx_msg void OnPanRight();
	afx_msg void OnPanUp();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMapLayers();
	afx_msg void OnUpdateMapLayers(CCmdUI* pCmdUI);
	afx_msg void OnLineInfo();
	afx_msg void OnUpdateLineInfo(CCmdUI* pCmdUI);
	afx_msg void OnMapProj();
	afx_msg void OnThinPts();
	afx_msg void OnSearchUserid();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateSearchUserid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsShortpath(CCmdUI* pCmdUI);
	afx_msg void OnToolsShortpath();
	afx_msg void OnUpdateToolsThining(CCmdUI* pCmdUI);
	afx_msg void OnToolsThining();
	afx_msg void OnZoomDataextent();
	afx_msg void OnAcsSex();
	afx_msg void OnUpdateAcsSex(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in MapViewSDView.cpp
inline CMapViewSDDoc* CMapViewSDView::GetDocument() const
   { return reinterpret_cast<CMapViewSDDoc*>(m_pDocument); }
#endif

