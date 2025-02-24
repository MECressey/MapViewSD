//
//	MapViewSDDoc.h - interface of the CMapViewSDDoc class (generated by Visual Studio)
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

#include "range.hpp"
#include "geodb.hpp"
#include "tigerdb.hpp"
#include "ACSSurveyData.h"
#include <afxdb.h>

class CMapViewSDDoc : public CDocument
{
protected: // create from serialization only
	CMapViewSDDoc() noexcept;
	DECLARE_DYNCREATE(CMapViewSDDoc)

// Attributes
public:
	CDatabase odbcDB;
	TigerDB *db;
	Range2D range;
	BOOL isOpen;
#if defined( DO_PTS )
	int nPts;
	XY_t points[3000];
#endif
	int stateFips;

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
