// ACSDataDisplay.cpp : implementation file
//

#include "pch.h"
#include "MapViewSD.h"
#include "afxdialogex.h"
#include "ACSDataDisplay.h"


// ACSDataDisplay dialog

IMPLEMENT_DYNAMIC(ACSDataDisplay, CDialogEx)

ACSDataDisplay::ACSDataDisplay(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	
	/*m_ImageList.Create(MAKEINTRESOURCE(IDB_MENU_IMAGES_24), 16, 1, RGB(255, 255, 255));
	m_Grid.SetImageList(&m_ImageList);*/

	m_Grid.SetVirtualMode(FALSE);
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


	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(ACSDataDisplay, CDialogEx)
END_MESSAGE_MAP()


// ACSDataDisplay message handlers
