#pragma once

//转换
void DrawTranslate(HDC hdc, int xmax, int ymax)
{
	Matrix matrix;
	matrix.Scale(1, 2, MatrixOrderAppend);
	matrix.Rotate(30.0);
	matrix.Translate(5, 0, MatrixOrderAppend);

	REAL r[9];
	matrix.GetElements(r);
}

void DrawCoordinate(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	g.TranslateTransform(100, 50);
	Pen penArrow(Color::Red);
	penArrow.SetLineCap(LineCapFlat, LineCapTriangle, DashCapFlat);
	DrawEllipsePoint(hdc, Point(100, 0));
	g.DrawLine(&penArrow, 0, 0, 0, 150);
	g.DrawLine(&penArrow, 0, 0, 150, 0);
	Pen pen(Color::Green);
	g.DrawLine(&pen, 0, 0, 160, 80);
}

void DrawGetDpiXY(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	REAL x= g.GetDpiX();
	REAL y=g.GetDpiY();
	x++; y++;
}

void DrawTransfromCar(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	const int Width = xmax / 2;
	const int Height = ymax / 2;

	g.SetSmoothingMode(SmoothingModeAntiAlias);
	FontFamily ff(_T("Times New Roman"));
	Font font(&ff, 14, FontStyleBold, UnitPixel);

	g.TranslateTransform(Width/2, Height/2);
	const int circle = Height / 2 - 2;
	g.FillEllipse(&SolidBrush(Color(125, 0, 0, 0)), Rect(-circle, -circle, Height - 4, Height - 4));

	g.RotateTransform(225);
	for (int x = 0; x < 60; ++x)
	{
		g.FillRectangle(&SolidBrush(Color::Yellow), -1.5, -1 * (Height / 2 - 2), 3, 18);
		g.RotateTransform(4.5);
	}


	g.ResetTransform();
	g.TranslateTransform(Width / 2, Height / 2);
	g.RotateTransform(225);
	int sp = 0;
	CString tmp;
	for (int x = 0; x < 7;++x)
	{
		tmp.Format(_T("%d"), sp);
		g.FillRectangle(&SolidBrush(Color::Red), -3, -1 * (Height / 2 - 2), 6, 25);
		g.DrawString(tmp, -1, &font, PointF(tmp.GetLength()*(-6), (Height / -2) + 25), &SolidBrush(Color::Green));
		g.RotateTransform(45);
		sp += 20;
	}

	


	g.ResetTransform();
	g.TranslateTransform(Width / 2, Height / 2);
	REAL angle;
	angle = 30 * 2.25f + 225;
	g.RotateTransform(angle);
	Pen pen(Color::Blue, 14);
	pen.SetEndCap(LineCapArrowAnchor);
	pen.SetStartCap(LineCapRoundAnchor);
	//g.DrawLine(&pen, 0, 0, 0, 100);

	g.DrawLine(&pen, PointF(0, 0), PointF(0, (-1)*(Height/2.75f)));

	g.ResetTransform();
	g.TranslateTransform(Width / 2, Height / 2);
	g.FillEllipse(&SolidBrush(Color::Black), -6, -9, 14, 14);
	g.FillEllipse(&SolidBrush(Color::Red), -7, -7, 14, 14);

	pen.SetWidth(4);
	pen.SetColor(Color::Black);
	pen.SetEndCap(LineCapRound);
	pen.SetStartCap(LineCapFlat);
	g.DrawLine(&pen, PointF(Height/15.75f,Height/3.95f),PointF(Height/10.75f,Height/5.2f));
 	pen.SetColor(Color::Red);
 
 	g.DrawLine(&pen, PointF(Height / 15.75f, Height / 3.95f), PointF(Height / 15.75f, Height / 4.6f));
}

void DrawMirrorText(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	FontFamily ff(_T("华文楷体"));
	Font font(&ff, 48, FontStyleRegular, UnitPixel);
	FontFamily ff2(_T("Courier New"));
	Font font2(&ff2, 16, FontStyleRegular, UnitPixel);
	SolidBrush redBrush(Color::Red);

	RectF layoutRect(0, 0, xmax / 4, ymax / 4);
	StringFormat sf;
	//行距 = 上部+下部+行间距
	int ascent = ff.GetLineSpacing(FontStyleRegular) - ff.GetCellAscent(FontStyleRegular);
	int ascent2 = ff.GetLineSpacing(FontStyleRegular) - ff.GetCellAscent(FontStyleRegular);
	int asPixel = font.GetSize()*ascent / ff.GetEmHeight(FontStyleRegular);
	int asPixel2 = font2.GetSize()*ascent2 / ff2.GetEmHeight(FontStyleRegular);

	g.TranslateTransform(0, layoutRect.Height);
	g.DrawString(_T("镜像输出"),-1,&font,PointF(0,-font.GetHeight(0.0f)+asPixel2),&sf,&redBrush);

	g.TranslateTransform(200, 0);
	for (int i = 0; i < 3;i++)
	{
		CString s;
		s.Format(_T("Line %d........."),i);
		g.DrawString(s, -1, &font2, PointF(0, font2.GetHeight(0.0f)*i), &sf, &redBrush);
	}

	g.TranslateTransform(-200, 0);
	g.ScaleTransform(1, -1);
	g.DrawString(_T("镜像输出"), -1, &font, PointF(0, -asPixel), &sf, &SolidBrush(Color::Gray));
	g.TranslateTransform(200, 0);
	for (int i = 0; i < 3; i++)
	{
		CString s;
		s.Format(_T("Line %d........."), i);
		g.DrawString(s, -1, &font2, PointF(0, font2.GetHeight(0.0f)*i), &sf, &SolidBrush(Color::Gray));
	}

	g.ResetTransform();
	g.TranslateTransform(xmax / 2, ymax / 2 + font.GetHeight(0.0) * 2);
	g.DrawString(_T("镜像输出"), -1, &font, PointF(0,0), &sf, &redBrush);
	g.ScaleTransform(-1, 1);
	g.DrawString(_T("镜像输出"), -1, &font, PointF(0, 0), &sf, &SolidBrush(Color::Gray));

}

void DrawMatrixPos(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Pen pen(Color::Blue,4);
	Pen pen2(Color::Gray);

	FontFamily ff(_T("宋体"));
	Font font(&ff, 20, FontStyleRegular, UnitPixel);
	SolidBrush redBrush(Color::Red);

	Rect r(-40, -65, 80, 130);
	Matrix matrix;
	g.TranslateTransform(xmax / 2, ymax / 2);

	g.RotateTransform(20);
	g.GetTransform(&matrix);
	g.DrawEllipse(&pen, r);
	REAL x[6] = { 0 };
	CString msg;
	matrix.GetElements(x);
	for (int i = 0; i < 6; i++)
	{
		msg.Format(_T("%10.2f"), x[i]);
		if (i % 2)
		{
			g.TranslateTransform(0, font.GetHeight(0.0f));
		}
		else
		{
			g.TranslateTransform(100, 0);
		}
		g.DrawString(msg, -1, &font, PointF(0, 0), NULL, &SolidBrush(Color::Black));
	}

	g.ResetTransform();
	g.DrawLine(&pen2, 0, ymax / 2, xmax, ymax / 2);
	g.DrawLine(&pen2, xmax / 2, 0, xmax / 2, ymax);

	g.TranslateTransform(xmax / 2, ymax / 2);
	g.RotateTransform(20,MatrixOrderAppend);
	g.DrawEllipse(&pen, r);

}

//对路径的点进行变换
void DrawPathMatrix(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	FontFamily ff(_T("隶书"));
	GraphicsPath path;
	SolidBrush redBrush(Color::Red);
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);

	path.AddString(_T("文字特效"), -1, &ff, FontStyleRegular, 80, Point(0, 0), NULL);
	int count = path.GetPointCount();
	Point* pts = new Point[count];
	path.GetPathPoints(pts, count);

	BYTE* ptys = new BYTE[count];
	path.GetPathTypes(ptys, count);

	GraphicsPath* path2 = path.Clone();

	Pen pen(Color::Green);
	

	Matrix matrix;
	matrix.Scale(0.5f, 3.0f);
	matrix.TransformPoints(pts, count);

	GraphicsPath newPath(pts, ptys, count);
	g.DrawPath(&pen, &newPath);
	g.DrawPath(&pen, &path);
	
}

void DrawMatrixRotate(HDC hdc, int xmax, int ymax)
{
	Rect r(-80, -30, 160, 60);
	Matrix matrix;
	matrix.Translate(xmax / 2, ymax / 2);
	Graphics g(hdc);
	matrix.Rotate(30);
	g.SetTransform(&matrix);
	Pen pen(Color::Green);
	g.DrawEllipse(&pen, r);

	g.ResetTransform();
	g.DrawLine(&pen, 0, ymax / 2, xmax, ymax / 2);
	g.DrawLine(&pen, xmax / 2, 0, xmax / 2, ymax);

}

void DrawCircleTest2(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	GraphicsPath path;
	FontFamily ff(_T("宋体"));
	Font font(&ff, 20, FontStyleRegular, UnitPixel);
	path.AddString(_T("GDI+编程"), -1, &ff, FontStyleRegular, 20, Point(0, 0), NULL);
	Rect r;
	path.GetBounds(&r);

	Bitmap image(r.Width,r.Height);
	Graphics gimage(&image);
	Pen pen(Color::Green);
	gimage.DrawPath(&pen, &path);

	TextureBrush brsh(&image);
	Pen pen2(&brsh, font.GetHeight(0.0));
	g.DrawEllipse(&pen2, Rect(50,50,300,300));
}

void DrawCircleTest(HDC hdc, int xmax, int ymax)
{
	/*QString hw("hello world");
	int drawWidth = width() / 100;
	QPainter painter(this);
	QPen pen = painter.pen();
	pen.setWidth(drawWidth);
	pen.setColor(Qt::darkGreen);
	painter.setPen(pen);

	QPainterPath path(QPointF(0.0, 0.0));

	QPointF c1(width()*0.2, height()*0.8);
	QPointF c2(width()*0.8, height()*0.2);

	path.cubicTo(c1, c2, QPointF(width(), height()));

	//draw the bezier curve
	painter.drawPath(path);

	//Make the painter ready to draw chars
	QFont font = painter.font();
	font.setPixelSize(drawWidth * 2);
	painter.setFont(font);
	pen.setColor(Qt::red);
	painter.setPen(pen);

	qreal percentIncrease = (qreal)1 / (hw.size() + 1);
	qreal percent = 0;

	for (int i = 0; i < hw.size(); i++) {
		percent += percentIncrease;

		QPointF point = path.pointAtPercent(percent);
		qreal angle = path.angleAtPercent(percent);

		qreal rad = qreal(0.017453292519943295769)*angle; // PI/180

		// From the documentation:
		/**
		QTransform transforms a point in the plane to another point using the following formulas:
		x' = m11*x + m21*y + dx
		y' = m22*y + m12*x + dy
		**/
		// So the idea is to find the "new position of the character
		// After we apply the world rotation.
		// Then translate the painter back to the original position.
	/*
	qreal sina = std::sin(rad);
	qreal cosa = std::cos(rad);

	// Finding the delta for the penwidth
	// Don't divide by 2 because some space would be nice
	qreal deltaPenX = cosa * pen.width();
	qreal deltaPenY = sina * pen.width();
	// Finding new posision after rotation
	qreal newX = (cosa * point.x()) - (sina * point.y());
	qreal newY = (cosa * point.y()) + (sina * point.x());

	// Getting the delta distance
	qreal deltaX = newX - point.x();
	qreal deltaY = newY - point.y();
	// Applying the rotation with the translation.
	QTransform tran(cosa, sina, -sina, cosa, -deltaX + deltaPenX, -deltaY - deltaPenY);

	painter.setWorldTransform(tran);
	painter.drawText(point, QString(hw[i]));
	}*/
		

	Graphics g(hdc);
	GraphicsPath path;
	FontFamily ff(_T("宋体"));
	Pen pen(Color::Green);
	Font font(&ff, 20, FontStyleRegular, UnitPixel);
	CString str(_T("GDI+编程GDI+编程GDI+编程"));
	path.AddString(str, - 1, &ff, FontStyleRegular, 20, Point(300, 300), NULL);
	//对于每一个点的Y左边进行圆形计算
	int count = path.GetPointCount();
	Point* pts = new Point[count];
	BYTE* pbts = new BYTE[count];

	path.GetPathPoints(pts,count);
	path.GetPathTypes(pbts, count);

	REAL percentIncrease = (REAL)1 / count;
	REAL percent = 0;

	for (int i = 0; i < count;++i)
	{
		percent += percentIncrease;

		Point point = pts[i];
		REAL rad = 2 * 3.14f*i / count;
	
		REAL sina = std::sin(rad);
		REAL cosa = std::cos(rad);

		REAL deltaPenX = cosa * 20;
		REAL deltaPenY = sina * 20;
		// Finding new posision after rotation
		REAL newX = (cosa * point.X) - (sina * point.Y);
		REAL newY = (cosa * point.Y) + (sina * point.X);

		// Getting the delta distance
		REAL deltaX = newX - point.X;
		REAL deltaY = newY - point.Y;
		// Applying the rotation with the translation.
		Matrix matrix(cosa, sina, -sina, cosa, -deltaX + deltaPenX, -deltaY - deltaPenY);
		//matrix.Translate(0, sin(pts[i].X) * One);
		matrix.TransformPoints(&(pts[i]));

	}

	GraphicsPath path2(pts,pbts,count);
	
	g.DrawPath(&pen, &path2);
	//g.DrawPath(&pen, &path);
	
}