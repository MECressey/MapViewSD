// ACSDataDisplay.cpp : implementation file
//

#include "pch.h"
#include "MapViewSD.h"
#include "afxdialogex.h"
#include "ACSDataDisplay.h"
#include <algorithm>


// ACSDataDisplay dialog

IMPLEMENT_DYNAMIC(ACSDataDisplay, CDialogEx)

ACSDataDisplay::ACSDataDisplay(CString& title, std::vector<CString>& headers, std::multimap<int, std::vector<int>>& rows, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACS_DIALOG, pParent), m_rows(rows), m_headers(headers), m_title(title)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//this->SetWindowText(title);
	//this->Create(ACSDataDisplay::IDD, pParent);
}

ACSDataDisplay::~ACSDataDisplay()
{
}

void ACSDataDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ACSDataDisplay)
	DDX_Control(pDX, IDC_GRID, m_Grid);             // associate the grid window with a C++ object
	//}}AFX_DATA_MAP
}

BOOL ACSDataDisplay::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	this->SetWindowText(m_title);

	m_ImageList.Create(MAKEINTRESOURCE(IDB_MENU_IMAGES_24), 16, 1, RGB(255, 255, 255));
	m_Grid.SetImageList(&m_ImageList);

	m_Grid.SetVirtualMode(FALSE);
	//m_Grid.SetColumnResize(TRUE);
	m_Grid.SetAutoSizeStyle();

	auto it = m_rows.begin();
	int rowCount = m_rows.size() /*it->second.size()*/ + 1 /* header row */;

	m_Grid.SetRowCount(rowCount);
	m_Grid.SetColumnCount(m_headers.size());
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetFixedColumnCount(1/*m_headers.size()*/);

	//COLORREF clr = RGB(128, 128, 128);

	int row = 0;
	int sexCol = -1;
	for (int pos = 0; pos < m_Grid.GetColumnCount(); pos++)
	{
		GV_ITEM Item;

		Item.mask = GVIF_TEXT;
		Item.row = row;
		Item.col = pos;

		//Item.iImage = rand() % m_ImageList.GetImageCount();
		//Item.mask |= (GVIF_IMAGE);
		Item.crBkClr = RGB(211, 211, 211);             // or - m_Grid.SetItemBkColour(row, col, clr);
		Item.crFgClr = RGB(255, 0, 0);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));				    
		Item.mask |= (GVIF_BKCLR | GVIF_FGCLR);

		Item.strText = m_headers[pos];
		// 2/26/25: this is sort of a hack.  The sex is passed in as 0 or 1 for male/female but I want it be M or F in the grid
		if (sexCol == -1)
		{
			if (Item.strText == _T("Sex"))
				sexCol = pos;
		}
		m_Grid.SetItem(&Item);
	}

	for (; it != m_rows.end(); it++)
	{
		row += 1;
		int col = 0;
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		CString str;
		Item.row = row;
		Item.col = col++;

		str.Format(_T("%d"), it->first);
		Item.strText = str;
		m_Grid.SetItem(&Item);
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			Item.row = row;
			Item.col = col++;

			if (Item.col == sexCol)
			{
				if (*it2 == 0)
					str = _T("M");
				else
					str = _T("F");
			}
			else
				str.Format(_T("%d"), *it2);
			Item.strText = str;
			m_Grid.SetItem(&Item);
		}
	}

#ifdef SAVE_FOR_NOW
	m_Grid.SetRowCount(3);
	m_Grid.SetColumnCount(5);
	m_Grid.SetFixedRowCount(2);
	m_Grid.SetFixedColumnCount(2);

	TRY{
	for (int row = 0; row < m_Grid.GetRowCount(); row++)
	{
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)
		{
			CString str;

			GV_ITEM Item;

			Item.mask = GVIF_TEXT;
			Item.row = row;
			Item.col = col;

			if (row < 3)
				str.Format(_T("Column %d"), col);
			else if (col < 4)
				str.Format(_T("Row %d"), row);
			else
				str.Format(_T("%d"), row * col);
			Item.strText = str;

/*			if (rand() % 10 == 1)
			{
				COLORREF clr = RGB(rand() % 128 + 128, rand() % 128 + 128, rand() % 128 + 128);
				Item.crBkClr = clr;             // or - m_Grid.SetItemBkColour(row, col, clr);
				Item.crFgClr = RGB(255, 0, 0);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));				    
				Item.mask |= (GVIF_BKCLR | GVIF_FGCLR);
			}
*/
/*			if (col < m_Grid.GetFixedColumnCount())
			{
				//Item.iImage = rand() % m_ImageList.GetImageCount();
				Item.mask |= (GVIF_IMAGE);
			}
			*/
			m_Grid.SetItem(&Item);
		}
	}
	m_Grid.AutoSizeRows();
	}
	CATCH(CException, e)
	{
		e->ReportError();
	}
	END_CATCH
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(ACSDataDisplay, CDialogEx)
END_MESSAGE_MAP()


// ACSDataDisplay message handlers
