#pragma once

//本章是画笔与画刷的例子

const REAL PI = 3.1415926f;

void DrawPenTexture(HDC hdc,int x,int y)
{
	Graphics graphics(hdc);
	Image image(L"simple_texture.png");

	TextureBrush tBrush(&image);

	Pen texturePen(&tBrush, 30);
	graphics.DrawEllipse(&texturePen, 100, 20, 200, 100);

}

void DrawPenStyle(HDC hdc, int x, int y)
{
	Graphics graphics(hdc);
	Pen pen(Color::Red, 5);
	for (int i = 0; i < 5; ++i)
	{
		pen.SetDashStyle(static_cast<DashStyle>(i));
		graphics.DrawLine(&pen, 10, 30 * i + 20, 300, 30 * i + 20);
	}

	//使用自定义线型
	REAL dashVals[2] = {
		5.0f,  //线长5个像素
		2.0f   //间隔2个像素 }
	};
	pen.SetDashPattern(dashVals, 2);
	pen.SetColor(Color::Green);
	graphics.DrawLine(&pen, 10, 170, 300, 170);
}

void DrawPenAlign(HDC hdc, int x, int y)
{
	Pen redPen_1(Color::Red, 1);
	Pen blackPen_8(Color::Black, 8);
	Pen greenPen_16(Color::Green, 16);

	Graphics graphics(hdc);
	//画框
	graphics.DrawRectangle(&redPen_1, 10, 10, 100, 100);
	graphics.DrawRectangle(&redPen_1, 120, 10, 100, 100);

	//左边Center也是默认的方式
	blackPen_8.SetAlignment(PenAlignmentCenter);
	greenPen_16.SetAlignment(PenAlignmentCenter);
	graphics.DrawEllipse(&greenPen_16, 10, 10, 100, 100);
	graphics.DrawEllipse(&blackPen_8, 10, 10, 100, 100);

	//右边设置为insert
	blackPen_8.SetAlignment(PenAlignmentInset);
	greenPen_16.SetAlignment(PenAlignmentInset);
	graphics.DrawEllipse(&greenPen_16, 120, 10, 100, 100);
	graphics.DrawEllipse(&blackPen_8, 120, 10, 100, 100);

}

void DrawScalePen(HDC hdc, int x, int y)
{
	Pen p1(Color::Blue,5);
	Pen p2(Color::Red, 5);
	Pen p3(Color::Green, 5);
	Matrix m(1, 0, 0, 2, 0, 0);
	p1.MultiplyTransform(&m);
	p2.SetTransform(&m);
	p3.ScaleTransform(1, 2);
	
	Graphics graphics(hdc);
	graphics.DrawRectangle(&p1, 10, 10, 100, 100);
	graphics.DrawRectangle(&p2, 150, 10, 100, 100);
	graphics.DrawRectangle(&p3, 290, 10, 100, 100);
}

void DrawRotatePen(HDC hdc, int x, int y)
{
	Pen p(Color::Blue, 5);
	p.ScaleTransform(1, 6); 
	Graphics graphics(hdc);
	graphics.DrawEllipse(&p, 50, 50, 200, 200);

	p.RotateTransform(60,MatrixOrderAppend);
	graphics.DrawEllipse(&p, 300, 50, 200, 200);
	p.RotateTransform(60, MatrixOrderAppend);
	graphics.DrawEllipse(&p, 300, 300, 200, 200);
	p.RotateTransform(60, MatrixOrderAppend);
	graphics.DrawEllipse(&p, 50, 300, 200, 200);

}

void DrawLineCap(HDC hdc, int x, int y)
{
	Graphics graphics(hdc);
	GraphicsPath startPath, endPath;
	Rect r(-10, -5, 20, 10);
	startPath.AddRectangle(r);

	endPath.AddLine(0, -20, 10, 0);
	endPath.AddLine(0, -20, -10, 0);
	endPath.AddLine(0, -10, 10, 0);
	endPath.AddLine(0, -10, 10, 0);

	CustomLineCap startCap(NULL, &startPath);
	CustomLineCap endCap(NULL, &endPath);
	Pen p(Color::Blue, 2);
	p.SetCustomStartCap(&startCap);
	p.SetCustomEndCap(&endCap);

	graphics.DrawLine(&p, 150, 30, 350, 30);

	//以点（300,300）为圆心绘制直线
	for (float i = 0.0f; i < 6.28f; i += 0.15f)
	{
		graphics.DrawLine(&p, 300.0f, 300.0f, 300 + 200.0f*cos(i), 300 + 200.0f*sin(i));
	}

}

void DrawPenAlpha(HDC hdc, int , int )
{
	Graphics graphics(hdc);
	Pen blue(Color::Blue);
	Pen red(Color::Red);


	int y = 256;
	for (int x = 0; x < 256;x+=5)
	{
		graphics.DrawLine(&blue, 0, y, x, 0);
		graphics.DrawLine(&red, 256, x, y, 256);
		y -= 5;
		Sleep(120);
	}

	for (y = 0; y < 256;y++)
	{
		Pen p(Color(y, 0, 255, 0));
		graphics.DrawLine(&p, 0, y, 256, y);
		Sleep(20);
	}

	for (int x = 0; x < 256; x++)
	{
		Pen p(Color(x, 255, 0, 255));
		graphics.DrawLine(&p, x, 100, x, 200);
		Sleep(20);
	}
}

/*R =A*sin(N*Angle)
  X = R*cos(Angle)
  Y = R*sin(Angle)
*/
void DrawLeaf(HDC hdc, int xmax, int ymax)
{
	//中心
	Point center(xmax / 2, ymax / 2);
	const int leafNum = 5;
	const REAL PI = 3.1415926f;
	const int leafLen = 100;
	GraphicsPath tmpPath(FillModeAlternate);
	for (float i = 0.0f; i < PI * 2 + 0.1f;i+=PI/180)
	{
		REAL r, x, y,x2,y2;
		r = abs(leafLen*cos(leafNum*i));
		x = r*cos(i);
		y = r*sin(i);

		x2 = center.X + x;
		y2 = center.Y + y;

		tmpPath.AddLine(x2, y2, x2, y2);
	}
	Graphics g(hdc);
	g.FillPath(&SolidBrush(Color::Green), &tmpPath);
}

void DrawBrushHatch(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	int row = 0;
	int colomn = 0;
	Font f(_T("Arial"), 16);
	int size = 100;
	int coloum_num = xmax / size;
	for (int i = 0; i < 53;i++)
	{
		if (colomn>coloum_num-1)
		{
			colomn = 0;
			row++;
		}
		HatchBrush b(HatchStyle(i), Color::Black, Color::White);
		RectF r(colomn * size, row * size, size-5, size-5);
		g.FillRectangle(&b, r);
		CString str;
		str.Format(_T("%d"), i);
		StringFormat fmt;
		fmt.SetAlignment(StringAlignmentCenter);
		fmt.SetLineAlignment(StringAlignmentCenter);
		
		g.DrawString(str, str.GetLength(), &f, r, &fmt, &SolidBrush(Color::Red));
		colomn++;
	}

}

void DrawBrushTexture(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	RectF r1(10, 10, 200, 200);
	RectF r2(210, 10, 200, 200);
	RectF r3(410, 10, 200, 200);
	RectF r4(610, 10, 200, 200);

	Pen pen_b(Color::Blue, 2);
	Image image(_T("texture.png")); //32*32

	//默认
	TextureBrush tBrush(&image);
	g.FillEllipse(&tBrush, r1);
	g.DrawEllipse(&pen_b, r1);

	//图片小于目标区域（被裁减）
	TextureBrush tBrush2(&image,Rect(0,0,20,32));
	g.FillEllipse(&tBrush2, r2);
	g.DrawEllipse(&pen_b, r2);

	//图片缩放
	TextureBrush tBrush3(&image, Rect(0, 0, 20, 32));
	tBrush3.SetTransform(&Matrix(0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f));
	g.FillEllipse(&tBrush3, r3);
	g.DrawEllipse(&pen_b, r3);

	//图片大于目标区域(会失败)
	TextureBrush tBrush4(&image, Rect(0, 0, 50, 50));
	g.FillEllipse(&tBrush4, r4);
	g.DrawEllipse(&pen_b, r4);

}

void DrawBrushLinear(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	LinearGradientBrush l(Point(0, 0), Point(40, 0), Color::Red, Color::Blue);
	LinearGradientBrush l2(Point(0, 0), Point(40, 40), Color::Red, Color::Blue);

	g.FillRectangle(&l, 0, 0, 200, 200);
	g.FillRectangle(&l2,240, 0, 200, 200);

	Pen p(Color::Gray);
	for (int i = 0; i < 5;++i)
	{
		g.DrawRectangle(&p, 240 + i * 40, i * 40, 40, 40);
	}
}

void DrawBrushLinear2(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	const int counts = 3;
	Color colors[counts] = { Color::Red, Color::Green, Color::Blue };
	REAL ps[counts] = { 0.0f, 0.3f, 1.0f };

	LinearGradientBrush l(Point(0, 0), Point(180, 0), Color::Black, Color::White);
	l.SetInterpolationColors(colors, ps, counts);
	g.FillRectangle(&l, 0, 0, 180, 100);

	LinearGradientBrush l2(Point(0, 0), Point(60, 0), Color::Red, Color::Green);
	g.FillRectangle(&l2, 0, 120, 60, 100);

	LinearGradientBrush l3(Point(60, 0), Point(181, 0), Color::Green, Color::Blue);
	g.FillRectangle(&l3, 60, 120, 120, 100);

}

void DrawBrushLinear3(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	const int counts = 4;
	REAL facts[counts] = { 0.0f, 0.9f, 0.3f,0.0f };
	REAL ps[counts] = { 0.0f,0.1f, 0.6f, 1.0f };
	Rect r(0, 0, 200, 200);
	LinearGradientBrush l(r, Color::Red, Color::Blue,LinearGradientModeHorizontal);
	l.SetBlend(facts, ps, counts);
	g.FillRectangle(&l, r);

}

void DrawBrushLinear4(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	LinearGradientBrush l(Point(0,0), Point(250,0),Color::Red, Color::Blue);
	g.FillRectangle(&l, 0, 0, 250, 15);
	g.FillRectangle(&l,500, 0, 250, 15);

	int row = 1;
	for (REAL i = 0.0f; i < 1.0f;i+=0.1f)
	{
		l.SetBlendTriangularShape(i);
		g.FillRectangle(&l, 0, row*15, 250, 15);
		row++;
	}

	row = 1;
	for (REAL i = 0.0f; i < 1.0f; i += 0.1f)
	{
		l.SetBlendTriangularShape(1.0f,i);
		g.FillRectangle(&l, 500, row * 15, 250, 15);
		row++;
	}

}

void DrawBrushPath(HDC hdc, int xmax, int ymax)
{
	const int counts = 10;
	Point point[counts] = { Point(75, 0), Point(100, 50),
		Point(150, 50), Point(112, 75), Point(150, 150),
		Point(75, 100), Point(0, 150), Point(37, 75),
		Point(0, 50), Point(50,50)
	};
	Graphics g(hdc);
	GraphicsPath p;
	p.AddLines(point, counts);

	PathGradientBrush pb(&p);
	pb.SetCenterColor(Color::Red);

	Color colors[counts] = {
		Color::Black,Color::Green,Color::Blue,Color::White,Color::Black,
		Color::Green,Color::Blue,Color::White,Color::Black,Color::Green
	};
	pb.SetSurroundColors(colors, const_cast<int*>(&counts));
	g.FillPath(&pb, &p);

	for (int z = 0; z < 10;z++)
	{
		colors[z] = getRandomColor();
	}
	g.TranslateTransform(200.0f, 0.0f);
	pb.SetCenterColor(getRandomColor());
	pb.SetSurroundColors(colors, const_cast<int*>(&counts));
	g.FillPath(&pb, &p);

}

//伽马校正
void DrawBrushPathGamma(HDC hdc, int xmax, int ymax)
{
	const int counts = 10;
	Point point[counts] = { Point(75, 0), Point(100, 50),
		Point(150, 50), Point(112, 75), Point(150, 150),
		Point(75, 100), Point(0, 150), Point(37, 75),
		Point(0, 50), Point(50, 50)
	};
	Graphics g(hdc);
	GraphicsPath p;
	p.AddLines(point, counts);

	PathGradientBrush pb(&p);
	pb.SetCenterColor(Color::Red);

	Color colors[counts] = {
		Color::Black, Color::Green, Color::Blue, Color::White, Color::Black,
		Color::Green, Color::Blue, Color::White, Color::Black, Color::Green
	};
	pb.SetSurroundColors(colors, const_cast<int*>(&counts));
	g.FillPath(&pb, &p);


	g.TranslateTransform(200.0f, 0.0f);
	pb.SetGammaCorrection(TRUE);
	g.FillPath(&pb, &p);

}

void DrawBrushPathArea(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	//定义一个六边形，边长为50
	const REAL half = 50 * sin(PI*120.0f / 360.0f);
	const int counts = 10;
	PointF pts[counts] = { PointF(50, 0), PointF(50 * 1.5f, 0), PointF(50, 0),
		PointF(50 / 2, -half), PointF(-50 / 2, -half), PointF(-50, 0),
		PointF(-50 * 1.5f, 0), PointF(-50, 0), PointF(-50 / 2, half), PointF(50 / 2, half) };

	//构造画刷
	PathGradientBrush pb(pts, counts);
	for (int i = 0; i < counts;i++)
	{
		pts[i].X += 50 * 1.5f;
		pts[i].Y += half;
	}

	PathGradientBrush pb2(pts, counts);
	pb.SetWrapMode(WrapModeTile);
	pb2.SetWrapMode(WrapModeTile);

	pb.SetCenterColor(Color::Red);
	pb2.SetCenterColor(Color::Green);

	g.FillRectangle(&pb, 0, 0, xmax, ymax);
	g.FillRectangle(&pb2, 0, 0, xmax, ymax);

}

void DrawBrushPathFoucs(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	const int counts = 3;
	//指定三角形三顶点
	Point pts[counts] = { Point(100, 0), Point(200, 200), Point(0, 200) };
	PathGradientBrush pb(pts, counts);
	Color cs[counts-1] = { Color::Red, Color::Blue };
	REAL rs[counts - 1] = { 0.0f, 1.0f };
	pb.SetInterpolationColors(cs, rs, counts - 1);

	Rect r(0, 0, 200, 200);
	g.FillRectangle(&pb, r);

	REAL x, y;
	pb.GetFocusScales(&x, &y);
	//输出缩放因子
	Font f(_T("Arial"), 13);
	SolidBrush fs(Color::Black);
	CString str;
	str.Format(_T("x=%.2f y=%.2f"),x,y);
	g.DrawString(str, str.GetLength(), &f, PointF(0, 210), &fs);

	//平移并更改缩放因子
	g.TranslateTransform(200, 0);
	pb.SetFocusScales(0.6f, 0.6f);
	g.FillRectangle(&pb, r);
	str.Format(_T("x=%.2f y=%.2f"), 0.6f, 0.6f);
	g.DrawString(str, str.GetLength(), &f, PointF(0, 210), &fs);

	//平移并更改缩放因子
	g.TranslateTransform(200, 0);
	pb.SetFocusScales(0.1f, 0.8f);
	g.FillRectangle(&pb, r);
	str.Format(_T("x=%.2f y=%.2f"), 0.1f, 0.8f);
	g.DrawString(str, str.GetLength(), &f, PointF(0, 210), &fs);

	//平移并更改缩放因子
	g.TranslateTransform(200, 0);
	pb.SetFocusScales(1.0f, 1.0f);
	g.FillRectangle(&pb, r);
	str.Format(_T("x=%.2f y=%.2f"), 1.0f, 1.0f);
	g.DrawString(str, str.GetLength(), &f, PointF(0, 210), &fs);

	//平移并更改缩放因子
	g.TranslateTransform(200, 0);
	pb.SetFocusScales(2.0f, 1.5f);
	g.FillRectangle(&pb, r);
	str.Format(_T("x=%.2f y=%.2f"), 2.0f, 1.5f);
	g.DrawString(str, str.GetLength(), &f, PointF(0, 210), &fs);

}