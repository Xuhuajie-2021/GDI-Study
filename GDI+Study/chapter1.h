#pragma once

void GDIDrawLine(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hPenOld = (HPEN)::SelectObject(hdc, hPen); //��DC�Ż��ʶ���
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