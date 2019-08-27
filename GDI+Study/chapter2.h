#pragma once

//������ͼ������ʹ��
void GDIPlusDrawRectangles(HDC hdc)
{
	Graphics graphics(hdc);
	Pen blue(Color(255, 0, 255, 0), 3);
	RectF r1(10, 10, 100, 50);
	RectF r2(40, 40, 100, 50);
	RectF r3(80, 40, 50, 100);
	RectF rs[] = { r1, r2, r3 };
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

Color getRandomColor()
{
	return Color(rand() % 255, rand() % 255, rand() % 255);
}

//���
void DrawEllipsePoint(HDC hdc, Point t)
{
	Graphics graphics(hdc);
	SolidBrush redbursh(Color::Red);
	graphics.FillEllipse(&redbursh, t.X - 5, t.Y - 5, 10, 10);
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
	graphics.DrawBezier(&orange, t[0], t[1], t[2], t[3]);

	for (int i = 0; i < t_size; ++i)
	{
		DrawEllipsePoint(hdc, t[i]);
	}
}

void DrawArcPie(HDC hdc, int xmax, int ymax)
{
	Graphics graphics(hdc);
	Rect t = GetRandomRect(xmax, ymax);
	//�Ȼ����α߿����Ӷ���ߵ���֪��
	Pen black(Color::Black); //Ĭ��һ����
	graphics.DrawRectangle(&black, t);
	//������
	Pen red(Color::Red, 3);
	graphics.DrawArc(&red, t, 0/*��ʼλ��*/, 90/*��Ҫ���Ļ��ȴ�С*/);
	//������
	Pen green(Color::Green, 1);
	graphics.DrawPie(&green, t, 90/*��ʼλ��*/, 90/*��Ҫ���Ļ��ȴ�С*/);
}

//�ð�͸����ɫ��� ���sinx �� x�������
void FillSinRegion(HDC hdc, int xmax, int ymax)
{
	const REAL Pi = 3.1415926f;
	//��0 �� 2pi
	//����1����=��������,��50px ->xmax-50px ��
	REAL perX = (xmax - 100)*1.0 / (2 * Pi);
	//����ȵ�λ1=��������
	REAL perY = (ymax - 100)*1.0 / 2;

	GraphicsPath tpath(FillModeAlternate);
	for (float i = 0.0f; i < 2 * Pi + 0.1;i+=Pi/180)
	{
		REAL x = i*perX + 50;
		REAL y = sin(i)*perY + ymax / 2;

		tpath.AddLine(x, y, x, y);
	}

	Graphics graphics(hdc);
	SolidBrush blue(Color(255 / 2, 0, 0, 255));
	graphics.FillPath(&blue, &tpath);





	/*
	//���㣬������Խ��Խ��ȷ������ȡ500+1�㡣��ҿ������Ը���
	const int counts = 500;
	Point t[counts * 2];
	t[0].X = 50;
	t[0].Y = ymax / 2;
	//����
	REAL stepX = (2 * Pi) / counts;
	REAL step = stepX*perX;
	//��������ֵ
	for (int i = 1; i < counts; i++)
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


	Pen r(Color::Red);
	graphics.DrawPolygon(&r, t, counts * 2);
	graphics.FillClosedCurve(&blue, t, counts * 2);
	*/
}

void  PrintText(HDC hdc, int xmax, int ymax)
{
	TCHAR s[32];
	_tcscpy_s(s, _T("Hello GDI+"));

	RectF t(10, 10, 200, 50);


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
