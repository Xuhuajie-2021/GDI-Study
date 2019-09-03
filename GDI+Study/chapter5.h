#pragma once

//路径与区域

void DrawPathConstruct(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	const int counts = 6;
	PointF data[counts] = { PointF(40, 140), PointF(275, 200),
		PointF(105, 225), PointF(190, 300), PointF(50, 350), PointF(20, 180) };
	BYTE typeline[counts] = {
		PathPointTypeLine, PathPointTypeLine, PathPointTypeLine,
		PathPointTypeLine, PathPointTypeLine, PathPointTypeLine
	};
	GraphicsPath p(data, typeline, counts);
	Pen pen(Color::Blue, 2);
	g.DrawPath(&pen, &p);

	g.TranslateTransform(360, 0);
	GraphicsPath p2;
	for (int i = 0; i < counts;++i)
	{
		p2.AddLine(data[i], data[i]);
	}
	g.DrawPath(&pen, &p2);

	g.TranslateTransform(360, 0);
	BYTE typeline2[counts]=
	{
		PathPointTypeStart,
		PathPointTypeBezier,
		PathPointTypeBezier,
		PathPointTypeBezier,
		PathPointTypeLine,
		PathPointTypeLine
	};
	GraphicsPath p3(data, typeline2, counts);
	g.DrawPath(&pen, &p3);
}

void DrawPathLink(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	GraphicsPath p;

	RectF r1(20, 20, 100, 200);
	RectF r2(40, 40, 100, 200);

	p.AddArc(r1, 0.0f, 180.0f);
	//p.CloseFigure();
	p.AddArc(r2, 0.0f, 180.0f);
	//p.CloseFigure();
	p.CloseAllFigures();
	Pen pen(Color::Blue, 2);
	g.DrawPath(&pen, &p);
}

void DrawPathFillPath(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	GraphicsPath path1, path2;
	Pen pen(Color(128, 0, 0, 255), 5);
	SolidBrush brush(Color::Red);

	//添加3条直线：开放的图形
	path1.AddLine(10, 10, 10, 50);
	path1.AddLine(10, 50, 50, 50);
	path1.AddLine(50, 50, 50, 10);

	path1.StartFigure();

	RectF rect(110, 10, 40, 40);
	path1.AddRectangle(rect);

	g.DrawPath(&pen, &path1);
	g.FillPath(&brush, &path1);

	path2.AddArc(0, 0, 150, 120, 30, 120);
	path2.AddEllipse(50, 50, 50, 100);
	g.DrawPath(&pen, &path2);
	g.FillPath(&brush, &path2);
}

//子路径的概念
void DrawPathSubPath(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	GraphicsPath path1, path2;
	Pen pen(Color(128, 0, 0, 255), 2);
	SolidBrush brush(Color::Red);

	path1.AddRectangle(Rect(20,20,60,30));

	path1.AddLine(100, 20, 160, 50);
	path1.AddArc(180, 20, 60, 30, 0.0f, 180);

	path1.AddRectangle(Rect(260,20,60,30));

	path1.AddLine(340, 20, 400, 50);
	path1.AddArc(340, 20, 60, 30, 0, 180);
	path1.CloseFigure();

	path1.AddRectangle(Rect(420, 20, 60, 30));


	g.DrawPath(&pen, &path1);
	//g.FillPath(&brush, &path1);

	g.TranslateTransform(0, 200);

	GraphicsPathIterator it(&path1);
	BOOL isClosed;
	INT count;
	count = it.NextSubpath(&path2, &isClosed);
	g.DrawPath(&pen, &path2);

	count = it.NextSubpath(&path2, &isClosed);
	g.DrawPath(&pen, &path2);

	g.TranslateTransform(0, 200);
	it.Rewind();
	count = it.NextSubpath(&path2, &isClosed);
	g.DrawPath(&pen, &path2);
	count = it.NextSubpath(&path2, &isClosed);
	g.DrawPath(&pen, &path2);
	INT start, end;
	count = it.NextSubpath(&start, &end, &isClosed);

}

void DrawPathGetPoint(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	GraphicsPath path;
	Point pts[] = { Point(200, 200), Point(250, 240),
		Point(200, 300), Point(300, 310), Point(250, 350) };

	path.AddLine(20, 100, 150, 200);
	path.AddRectangle(Rect(40,30,80,60));
	path.AddEllipse(Rect(200,30,200,100));
	path.AddCurve(pts,5);

	Pen pen(Color::Green);
	g.DrawPath(&pen, &path);

	INT count = path.GetPointCount();
	Point* dataps = new Point[count];
	path.GetPathPoints(dataps, count);

	for (int i = 0; i < count;i++)
	{
		DrawEllipsePoint(hdc, dataps[i]);
	}

}

void DrawPathSubPathRange(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	SolidBrush brush(Color::Green);
	Pen pen(Color(128, 0, 0, 255), 2);
	GraphicsPath path;
	path.AddRectangle(Rect(20,20,60,30));

	path.AddLine(100, 20, 160, 50);
	path.SetMarker();

	path.AddArc(180, 20, 60, 30, 0, 180);

	path.AddRectangle(Rect(260,20,60,30));
	path.SetMarker();

	path.AddLine(340, 20, 400, 50);
	path.AddArc(340, 20, 60, 30, 0, 180);

	g.FillPath(&brush, &path);
	g.DrawPath(&pen, &path);

	GraphicsPathIterator it(&path);
	int count = it.GetSubpathCount();

	int start, end, n;
	n = it.NextMarker(&start, &end);
	PointF* pts = new PointF[n];
	BYTE* type = new BYTE[n];
	it.CopyData(pts, type, start, end);


	g.TranslateTransform(0, 300);
	GraphicsPath p2(pts, type, n);
	g.FillPath(&brush, &p2);
	g.DrawPath(&pen, &p2);
	for (int i = 0; i < n;i++)
	{
		DrawEllipsePoint(hdc, Point(pts[i].X, pts[i].Y));
	}
	delete []pts;
	delete []type;

	n = it.NextMarker(&start, &end);
	pts = new PointF[n];
	type = new BYTE[n];
	it.CopyData(pts, type, start, end);
	GraphicsPath p3(pts, type, n);
	g.FillPath(&brush, &p3);
	g.DrawPath(&pen, &p3);
	for (int i = 0; i < n; i++)
	{
		DrawEllipsePoint(hdc, Point(pts[i].X, pts[i].Y));
	}

}

void DrawPathFlatten(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);

	Point pts[] = { Point(20, 50), Point(60, 70),
		Point(80, 10), Point(120, 50) };
	GraphicsPath path;
	path.AddCurve(pts, 4);
	path.AddEllipse(160, 10, 150, 80);
	path.AddBezier(20, 100, 20, 150, 50, 80, 100, 60);

	Pen pen(Color::Black, 3);
	g.DrawPath(&pen, &path);

	//获取所有的特征点
	PathData pd;
	path.GetPathData(&pd);
	for (int i = 0; i < pd.Count;i++)
	{
		DrawEllipsePoint(hdc, Point(pd.Points[i].X, pd.Points[i].Y));
	}

	//去曲线
	path.Flatten(NULL, 14);
	g.TranslateTransform(0, 300);
	g.DrawPath(&pen, &path);

}

void DrawPathOutline(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Pen bluepen(Color::Blue);
	Pen greenpen(Color::Green, 10);

	PointF pts[] = { PointF(20, 20), PointF(160, 100), PointF(140, 60), PointF(60, 100) };
	GraphicsPath path;
	path.AddClosedCurve(pts, 4);
	g.DrawPath(&bluepen, &path);

	g.TranslateTransform(0, 300);
	path.Widen(&greenpen);
	path.Outline();
	g.DrawPath(&greenpen, &path);
}

void DrawRegionFromPath(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);
	g.SetSmoothingMode(SmoothingModeAntiAlias);

	FontFamily ff(_T("隶书"));
	GraphicsPath path;
	path.AddString(_T("文字区域"),-1,&ff,FontStyleRegular,100,Point(0,0),NULL);

	Pen pen(Color::Red);
	g.DrawPath(&pen, &path);

	g.TranslateTransform(0, 80);
	Region region(&path);
	g.FillRegion(&SolidBrush(Color::Red),&region);

	g.TranslateTransform(0, 80);
	Region region2(&path);
	Matrix matrix;
	matrix.Rotate(30);
	region2.Transform(&matrix);
	g.FillRegion(&SolidBrush(Color::Red), &region2);
}

void DrawRegionCalculate(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	SolidBrush redBrush(Color::Red);
	SolidBrush greenBrush(Color::Green);

	Pen pen(Color(155, 255, 255, 0));

	Point pts[] = {
		Point(75, 0),
		Point(100, 50),
		Point(150, 50),
		Point(112, 75),
		Point(150, 150),
		Point(75, 120),
		Point(10, 150),
		Point(37, 75),
		Point(0, 50),
		Point(50, 50),
		Point(75, 50)
	};

	GraphicsPath path;
	path.AddLines(pts, 11);

	Matrix matrix;
	matrix.Scale(0.5f, 0.5f);
	path.Transform(&matrix);

	RectF tmp;
	path.GetBounds(&tmp);

	Rect r(0, 20, tmp.Width, 50);

	g.FillPath(&redBrush, &path);
	g.TranslateTransform(tmp.Width + 10.0f, 0);
	g.FillRectangle(&greenBrush, r);

	Region region(&path);
	region.Intersect(r);

	g.TranslateTransform(tmp.Width + 10, 0);
	g.FillRegion(&redBrush, &region);

	g.DrawRectangle(&pen, tmp);


	Region region2(&path);
	region2.Union(r);

	g.TranslateTransform(tmp.Width + 10, 0);
	g.FillRegion(&redBrush, &region2);
	g.DrawRectangle(&pen, tmp);

	g.TranslateTransform(-(tmp.Width + 10) * 3, tmp.Height);
	Region region3(&path);
	region3.Xor(r);
	g.FillRegion(&redBrush, &region3);
	g.DrawRectangle(&pen, tmp);

	Region region4(&path);
	region4.Complement(r);
	g.TranslateTransform(tmp.Width + 10, 0);
	g.FillRegion(&redBrush, &region4);
	g.DrawRectangle(&pen, tmp);

	Region region5(&path);
	region5.Exclude(r);
	g.TranslateTransform(tmp.Width + 10, 0);
	g.FillRegion(&redBrush, &region5);
	g.DrawRectangle(&pen, tmp);
}

void DrawRegionGetRects(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush redBrush(Color::Red);
	Pen pen(Color::Green);
	GraphicsPath path;
	Rect r;
	path.AddEllipse(10, 0, 80, 120);
	Region region(&path);
	g.FillRegion(&redBrush, &region);

	Matrix matrix;
	g.GetTransform(&matrix);
	path.GetBounds(&r, &matrix);

	int count = region.GetRegionScansCount(&matrix);

	Rect* pRect = new Rect[count];
	region.GetRegionScans(&matrix, pRect, &count);
	g.TranslateTransform(r.Width + 10, 0);
	for (int i = 0; i < count;++i)
	{
		g.DrawRectangle(&pen, pRect[i]);
	}

}

void DrawRegionHitTest(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	SolidBrush redBrush(Color::Red);
	PointF pts[] = {
		PointF(20, 20),
		PointF(160, 100),
		PointF(140, 60),
		PointF(60, 100)
	};

	GraphicsPath path;
	path.AddClosedCurve(pts, 4);
	Matrix matrix;
	matrix.Scale(2.0f, 1.0f);
	g.SetTransform(&matrix);
	Region region(&path);
	g.FillRegion(&redBrush, &region);

	Point p(xmax, ymax);
	if (region.IsVisible(p,&g))
	{
		return;
	}

	DrawEllipsePoint(hdc, p);
}