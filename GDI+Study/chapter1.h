#pragma once

void GDIDrawLine(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hPenOld = (HPEN)::SelectObject(hdc, hPen); //往DC放画笔对象
	::MoveToEx(hdc, 50, 50, NULL);
	::LineTo(hdc, 700, 50);
	::SelectObject(hdc, hPenOld); //这是个好习惯
	::DeleteObject(hPen);        //释放画笔
	hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	hPenOld = (HPEN)::SelectObject(hdc, hPen); //往DC放画笔对象
	::MoveToEx(hdc, 50, 100, NULL);
	::LineTo(hdc, 700, 100);
	::SelectObject(hdc, hPenOld); //这是个好习惯
	::DeleteObject(hPen);        //释放画笔
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