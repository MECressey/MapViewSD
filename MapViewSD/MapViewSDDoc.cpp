
// MapViewSDDoc.cpp : implementation of the CMapViewSDDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MapViewSD.h"
#endif

#include "MapViewSDDoc.h"

#include "geopoint.hpp"
#include "tstring.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMapViewSDDoc

IMPLEMENT_DYNCREATE(CMapViewSDDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapViewSDDoc, CDocument)
END_MESSAGE_MAP()


// CMapViewSDDoc construction/destruction

CMapViewSDDoc::CMapViewSDDoc() noexcept
{
	odbcDB.SetQueryTimeout(60 * 10);
	//odbcDB.Open( _T("TigerData"), FALSE, TRUE, _T("ODBC;UID=guest;PWD="), FALSE ); // Access MDB
	odbcDB.Open(_T("TigerBase"), FALSE, TRUE, _T("ODBC;UID=guest;PWD="), FALSE);  // SQL Server
	odbcDB.SetSynchronousMode(TRUE);
	this->db = new TigerDB(&odbcDB)/*GeoDB*/;
	ASSERT(this->db != 0);

	this->isOpen = FALSE;
#if defined( DO_PTS )
	this->nPts = 3;
	this->points[0].x = 150.0;
	this->points[0].y = 1100.0;
	this->points[1].x = 950.0;
	this->points[1].y = 1500.0;
	this->points[2].x = 500.0;
	this->points[2].y = 1950.0;
#endif

}

CMapViewSDDoc::~CMapViewSDDoc()
{
	if (this->db != 0)
	{
		if (this->db->IsOpen())
			this->db->Close();
	}
	delete this->db;
}

void CMapViewSDDoc::OnCloseDocument()
{
	ASSERT(this->db != 0);
	if (this->db->IsOpen())
		this->db->Close();
}

BOOL CMapViewSDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

BOOL CMapViewSDDoc::OnOpenDocument(const TCHAR* lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	ASSERT(this->db != 0);

	if (this->db->Open(TString(lpszPathName), 0/*1*/, 0) != 0)
		return(FALSE);
	this->range = this->db->GetRange();

	this->isOpen = TRUE;
	return TRUE;
}


// CMapViewSDDoc serialization

void CMapViewSDDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMapViewSDDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMapViewSDDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMapViewSDDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMapViewSDDoc diagnostics

#ifdef _DEBUG
void CMapViewSDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapViewSDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMapViewSDDoc commands