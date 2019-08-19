// GDI+Study.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GDI+Study.h"

#include <objidl.h>
#include <gdiplus.h> 
#include <commdlg.h>
#include<stdlib.h>
#include<time.h>
#include <cmath>
#pragma comment(lib, "gdiplus.lib")  
using namespace Gdiplus;
using namespace std;

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������



void GDIDrawLine(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID,3,RGB(255,0,0));
	hPenOld=(HPEN)::SelectObject(hdc, hPen); //��DC�Ż��ʶ���
	::MoveToEx(hdc, 50, 50, NULL);
	::LineTo(hdc, 700, 50);
	::SelectObject(hdc, hPenOld); //���Ǹ���ϰ��
	::DeleteObject(hPen);        //�ͷŻ���
	hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	hPenOld = (HPEN)::SelectObject(hdc, hPen); //��DC�Ż��ʶ���
	::MoveToEx(hdc, 50, 100, NULL);
	::LineTo(hdc, 700, 100);
	::SelectObject(hdc, hPenOld); //���Ǹ���ϰ��
	::DeleteObject(hPen);        //�ͷŻ���
}

void GDIPlusDrawLine(HDC hdc)
{
	Graphics graphics(hdc);
	Pen blue(Color(255, 0, 255, 0), 3);
	PointF p1(10, 10);
	PointF p2(10, 100);
	PointF p3(50, 50);
	PointF p4(10, 10);
	PointF point[] = { p1, p2, p3, p4 };
	graphics.DrawLines(&blue, point, sizeof(point) / sizeof(point[0]));

}

void GDIPlusDrawRectangles(HDC hdc)
{
	Graphics graphics(hdc);
	Pen blue(Color(255, 0, 255, 0), 3);
	RectF r1(10,10,100,50);
	RectF r2(40,40,100,50);
	RectF r3(80,40,50,100);
	RectF rs[] = { r1, r2, r3};
	graphics.DrawRectangles(&blue, rs, sizeof(rs) / sizeof(rs[0]));

}

void GDIPlusDrawLineS(HDC hdc)
{
	Graphics graphics(hdc);
	Pen blue(Color(255, 0, 255, 0), 3);
	PointF p1(10, 10);
	PointF p2(10, 100);
	PointF p3(50, 50);
	PointF p4(10, 10);
	PointF point[] = { p1, p2, p3, p4 };
	graphics.DrawLines(&blue, point, sizeof(point) / sizeof(point[0]));

}

Point GetRandomPoint(int xmax, int ymax)
{
	Point t;
	t.X = rand() % xmax;
	t.Y = rand() % ymax;
	return t;
}

Rect GetRandomRect(int xmax, int ymax)
{
	Rect t;
	Point t1 = GetRandomPoint(xmax, ymax);
	Point t2 = GetRandomPoint(xmax, ymax);

	if (t1.X < t2.X)
	{
		t.X = t1.X;
		t.Width = t2.X - t1.X;
		if (t1.Y<t2.Y)
		{
			t.Y = t1.Y;
			t.Height = t2.Y - t1.Y;
		}
		else
		{
			t.Y = t2.Y;
			t.Height = t1.Y - t2.Y;
		}
	}
	else
	{
		t.X = t2.X;
		t.Width = t1.X - t2.X;
		if (t1.Y < t2.Y)
		{
			t.Y = t1.Y;
			t.Height = t2.Y - t1.Y;
		}
		else
		{
			t.Y = t2.Y;
			t.Height = t1.Y - t2.Y;
		}
	}

	return t;
}

//���
void DrawEllipsePoint(HDC hdc, Point t)
{
	Graphics graphics(hdc);
	SolidBrush redbursh(Color::Red);
	graphics.FillEllipse(&redbursh, t.X-5, t.Y-5, 10, 10);
}

void DrawCurves(HDC hdc, int xmax, int ymax)
{
	Graphics graphics(hdc);
	Point t[] = { GetRandomPoint(xmax, ymax),
		GetRandomPoint(xmax, ymax), GetRandomPoint(xmax, ymax), GetRandomPoint(xmax, ymax) };

	int t_size = sizeof(t) / sizeof(t[0]);
	//������
	Pen green(Color::Green, 3);
	graphics.DrawCurve(&green, t, t_size);
	//���������̶�
	Pen blue(Color::Blue, 3);
	graphics.DrawCurve(&blue, t, t_size, 1.3f);
	//���պ�����
	Pen gray(Color::Gray, 3);
	graphics.DrawClosedCurve(&gray, t, t_size);
	//������������
	Pen orange(Color::Orange, 3);
	graphics.DrawBezier(&orange, t[0],t[1],t[2],t[3]);

	for (int i = 0; i < t_size;++i)
	{
		DrawEllipsePoint(hdc, t[i]);
	}
}

void DrawArcPie(HDC hdc,int xmax, int ymax)
{
	Graphics graphics(hdc);
	Rect t = GetRandomRect(xmax, ymax);
	//�Ȼ����α߿����Ӷ���ߵ���֪��
	Pen black(Color::Black); //Ĭ��һ����
	graphics.DrawRectangle(&black, t);
	//������
	Pen red(Color::Red, 3);
	graphics.DrawArc(&red, t, 0, 90);
	//������
	Pen green(Color::Green, 1);
	graphics.DrawPie(&green, t, 90, 90);
}

//�ð�͸����ɫ��� ���sinx �� x�������
void FillSinRegion(HDC hdc, int xmax, int ymax)
{
	const REAL Pi = 3.1415926;
	//��0 �� 2pi
	//����1����=��������,��50px ->xmax-50px ��
	REAL perX = (xmax - 100)*1.0 / (2 * Pi);
	//����ȵ�λ1=��������
	REAL perY = (ymax - 100)*1.0/2;

	//���㣬������Խ��Խ��ȷ������ȡ500+1�㡣��ҿ������Ը���
	const int counts = 500;
	Point t[counts*2];
	t[0].X = 50;
	t[0].Y = ymax / 2;
	//����
	REAL stepX = (2 * Pi) / counts;
	REAL step = stepX*perX ;
	//��������ֵ
	for (int i = 1; i < counts ; i++)
	{
		t[i].X = t[i - 1].X + step;
		REAL v = sin(i*stepX);
		t[i].Y = ymax / 2 - v*perY;
	}
	//��x��
	t[counts].X = t[counts - 1].X;
	t[counts].Y = ymax / 2;
	for (int i = 1; i < counts; i++)
	{
		t[counts + i].X = t[counts + i - 1].X - step;
		t[counts + i].Y = ymax / 2;
	}

	Graphics graphics(hdc);
	SolidBrush blue(Color(255 / 2, 0, 0, 255));
 	Pen r(Color::Red);
 	graphics.DrawPolygon(&r, t, counts*2);
	graphics.FillClosedCurve(&blue,t,counts*2);

}

void  PrintText(HDC hdc, int xmax, int ymax)
{
	TCHAR s[32];
	_tcscpy_s(s, _T("Hello GDI+"));

	RectF t(10,10,200,50);

	
	Font f(_T("Arial"), 26);
	StringFormat Fmt;
	Fmt.SetAlignment(StringAlignmentCenter);
	Fmt.SetLineAlignment(StringAlignmentCenter);

	SolidBrush red(Color::Red);
	Graphics graphics(hdc);
	graphics.DrawString(s, _tcslen(s), &f, t, &Fmt, &red);

	Pen black(Color::Black);
	graphics.DrawRectangle(&black, t);

}


void OnPrintOut()
{
	//Ҫ��ӡ���ĵ���Ϣ
	DOCINFO docInfo;
	ZeroMemory(&docInfo, sizeof(docInfo));
	docInfo.cbSize = sizeof(docInfo);

	docInfo.lpszDocName = _T("TestPrint");

	PRINTDLG printDlg;
	ZeroMemory(&printDlg, sizeof(printDlg));
	printDlg.lStructSize = sizeof(printDlg);
	printDlg.Flags = PD_RETURNDC;

	if (PrintDlg(&printDlg))
	{
		StartDoc(printDlg.hDC, &docInfo);
		StartPage(printDlg.hDC);

		//��ʼ�ڴ�ӡ��������
		Graphics graphics(printDlg.hDC);
		
		//���ԵĻ��ŵ�cppĿ¼������ŵ�exeĿ¼
		Image image(_T("test.png"));
		graphics.DrawImage(&image, 0, 0);

		Pen blue(Color(255, 0, 0, 255));
		graphics.DrawRectangle(&blue, 200, 500, 200, 150);
		graphics.DrawEllipse(&blue, 200, 500, 200, 150);
		EndPage(printDlg.hDC);
		EndDoc(printDlg.hDC);
	}

	if (printDlg.hDevMode)
	{
		GlobalFree(printDlg.hDevMode);
	}
	if (printDlg.hDevNames)
	{
		GlobalFree(printDlg.hDevNames);
	}
	if (printDlg.hDC)
	{
		DeleteDC(printDlg.hDC);
	}
}


// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GDISTUDY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	// Initialize GDI+  
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//��ʼ������
	srand((unsigned)time(NULL));

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDISTUDY));

	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDISTUDY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GDISTUDY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			OnPrintOut();
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		PrintText(hdc, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
