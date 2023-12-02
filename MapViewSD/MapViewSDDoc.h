
// MapViewSDDoc.h : interface of the CMapViewSDDoc class
//


#pragma once

#include "range.hpp"
#include "geodb.hpp"
#include "tigerdb.hpp"
#include <afxdb.h>

class CMapViewSDDoc : public CDocument
{
protected: // create from serialization only
	CMapViewSDDoc() noexcept;
	DECLARE_DYNCREATE(CMapViewSDDoc)

// Attributes
public:
	CDatabase odbcDB;
	TigerDB/*GeoDB*/* db;
	Range2D range;
	BOOL isOpen;
#if defined( DO_PTS )
	int nPts;
	XY_t points[3000];
#endif

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(const TCHAR*);
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMapViewSDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
