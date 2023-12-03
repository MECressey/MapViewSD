
// MapViewSDView.h : interface of the CMapViewSDView class
//

#pragma once

#include "mapwin.hpp"
#include "layerdlg.h"
#include "linedlg.h"

class CMapViewSDView : public CView
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
	CPen pens[12];
	CBrush polyBrush;
	CFont font;
	int			pan_overlap;
	double		zoom_factor;
	MapProjection* mapProjs[1];
	MapProjection* mapProj;
#if defined( DO_TIGER )
	CArray<GeoPoint, GeoPoint> geoPts;
#endif
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
	LayerDlg layerDlg;
#if ! defined( DO_TIGER )
	ObjHandle pickObj;
#endif
	int doProj;
	BOOL doTest;
	BOOL doThining;
	BOOL doShortPath;
	int pickCount;
	long startId;
	XY_t startPt;
	int startDir;
	double startDist;

	void DoPan(double horizontal, double vertical);
	void DisplayInfo(TigerDB::Chain* line);
	void DisplayInfo(TigerDB::Polygon* poly);
	void DisplayInfo(TigerDB::GNISFeature* );

	CPen* GetPen(int code);
	CBrush* GetBrush(int code);

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
};

#ifndef _DEBUG  // debug version in MapViewSDView.cpp
inline CMapViewSDDoc* CMapViewSDView::GetDocument() const
   { return reinterpret_cast<CMapViewSDDoc*>(m_pDocument); }
#endif

