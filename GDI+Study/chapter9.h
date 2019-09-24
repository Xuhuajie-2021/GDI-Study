#pragma once

void DrawImageSetNoOp(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Image image(L"colortable.bmp");
	int width = image.GetWidth();
	int height = image.GetHeight();
	g.DrawImage(&image, 0, 0);

	g.TranslateTransform(width + 10, 0);
	ImageAttributes imAtt;
	ColorMatrix brushMatrix =  //red to green
	{
		0, 1, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};
	imAtt.SetColorMatrix(&brushMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, width, height, UnitPixel, &imAtt);

	imAtt.SetNoOp(ColorAdjustTypeBitmap);
	g.TranslateTransform(width + 10, 0);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, width, height, UnitPixel, &imAtt);

	imAtt.ClearNoOp(ColorAdjustTypeBitmap);
	g.TranslateTransform(width + 10, 0);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, width, height, UnitPixel, &imAtt);
}

void DrawSimpleMetafile(HDC hdc, int xmax, int ymax)
{
	Pen greenPen(Color::Green, 10);
	Pen redPen(Color::Red, 10);
	Pen bluePen(Color::Blue, 10);
	SolidBrush solidBrush(Color::Blue);
	SolidBrush redBrush(Color::Red);
	SolidBrush greenBrush(Color::Green);
	Metafile mf(L"test.emf",hdc);
	Graphics g(&mf);
	g.ScaleTransform(0.8f, 0.8f);

	Rect r(0, 0, 75, 95);
	Rect r2(40, 0, 75, 95);
	Rect r3(80, 0, 75, 95);

	g.SetSmoothingMode(SmoothingModeHighQuality);
	g.DrawEllipse(&redPen, r);
	g.FillEllipse(&redBrush, r);

	g.DrawEllipse(&greenPen, r2);
	g.FillEllipse(&greenBrush, r2);

	g.DrawEllipse(&bluePen, r3);
	g.FillEllipse(&solidBrush, r3);

	FontFamily ff(L"Arial");
	Font f(&ff, 24, FontStyleRegular, UnitPixel);
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);

	CString str = L"GDI+";

	g.DrawString(str, -1, &f, PointF(-80, 0), &redBrush);
	g.DrawString(str, -1, &f, PointF(-80, f.GetHeight(0.0f)), &greenBrush);
	g.DrawString(str, -1, &f, PointF(-80, f.GetHeight(0.0f)*2), &solidBrush);

}

void DrawSetColorMatrices(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Image image(L"test.emf");
	ImageAttributes imAtt;

	RectF rect;
	Unit unit;
	image.GetBounds(&rect, &unit);

	g.DrawImage(&image, 0.0f, 0.0f, rect.Width, rect.Height);

	ColorMatrix redMatrix =
	{
		1.5, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};

	ColorMatrix greenMatrix =
	{
		1, 0, 0, 0, 0,
		0, 1.5, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};

	ColorMatrix blueMatrix =
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1.5, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};


	ColorMatrix grayMatrix =
	{
		1.5, 0, 0, 0, 0,
		0, 1.5, 0, 0, 0,
		0, 0, 1.5, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};

	imAtt.SetColorMatrices(&redMatrix, &greenMatrix, ColorMatrixFlagsAltGray, ColorAdjustTypeDefault);
	g.TranslateTransform(image.GetWidth() + 10, 0);
	g.DrawImage(&image, RectF(0, 0, image.GetWidth(), image.GetHeight()),
		rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt);

	imAtt.SetColorMatrices(&blueMatrix, &grayMatrix, ColorMatrixFlagsAltGray, ColorAdjustTypePen);
	g.ResetTransform();
	g.TranslateTransform(0, image.GetHeight());
	g.DrawImage(&image, RectF(0, 0, image.GetWidth(), image.GetHeight()),
		rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt);

	g.TranslateTransform(image.GetWidth()+10, 0);
	imAtt.ClearColorMatrices(ColorAdjustTypePen);

	g.DrawImage(&image, RectF(0, 0, image.GetWidth(), image.GetHeight()),
		rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt);
}

void DrawGammaadjust(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap image(L"beauty.jpg");
	int width = image.GetWidth();
	int height = image.GetHeight();

	CString str;
	Font f(L"宋体", 12);
	PointF o(width + 10, height + 20);
	SolidBrush blackBrush(Color::Black);

	ImageAttributes imatt;
	for (float i = 0.0f; i < 3.0f;i+=0.1f)
	{
		g.FillRectangle(&SolidBrush(Color::White), 0, 0, xmax, ymax);
		g.DrawImage(&image, 0, 0);
		imatt.SetGamma(i, ColorAdjustTypeBitmap);
		g.DrawImage(&image, Rect(width + 10, 0, width, height),
			0, 0, width, height, UnitPixel, &imatt);
		
		str.Format(L"正在修改Gamma值，Gamma=%0.2f", i);
		g.DrawString(str, -1, &f, o, &blackBrush);
		Sleep(1000);
	}
}

void DrawOutPutChannel(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap image(L"beauty.jpg");
	int width = image.GetWidth();
	int height = image.GetHeight();

	g.DrawImage(&image, 0, 0, width/2, height/2);
	ImageAttributes imatt;
	imatt.SetOutputChannel(ColorChannelFlagsC, ColorAdjustTypeBitmap);
	g.TranslateTransform(width/2 + 10, 0);
	g.DrawImage(&image, Rect(0, 0, width/2, height/2), 0, 0, width, height, UnitPixel, &imatt);

	imatt.ClearOutputChannel(ColorAdjustTypeBitmap);
	imatt.SetOutputChannel(ColorChannelFlagsM, ColorAdjustTypeBitmap);
	g.TranslateTransform(width / 2 + 10, 0);
	g.DrawImage(&image, Rect(0, 0, width / 2, height / 2), 0, 0, width, height, UnitPixel, &imatt);

	imatt.ClearOutputChannel(ColorAdjustTypeBitmap);
	imatt.SetOutputChannel(ColorChannelFlagsY, ColorAdjustTypeBitmap);
	g.TranslateTransform(width / 2 + 10, 0);
	g.DrawImage(&image, Rect(0, 0, width / 2, height / 2), 0, 0, width, height, UnitPixel, &imatt);

	imatt.ClearOutputChannel(ColorAdjustTypeBitmap);
	imatt.SetOutputChannel(ColorChannelFlagsK, ColorAdjustTypeBitmap);
	g.TranslateTransform(width / 2 + 10, 0);
	g.DrawImage(&image, Rect(0, 0, width / 2, height / 2), 0, 0, width, height, UnitPixel, &imatt);
}

void DrawWrapMode(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap image(L"beauty.jpg");
	int width = image.GetWidth();
	int height = image.GetHeight();

	ImageAttributes imAtt;
	imAtt.SetWrapMode(WrapModeClamp, Color::Red);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, 0.5 * width, 2 * height,UnitPixel,&imAtt);
}

void DrawNineTest(HDC hdc, int xmax, int ymax)
{
	Metafile file(L"nine_1.emf", hdc);
	Graphics g(&file);
	//绘制三原色
	PointF pt(xmax / 2, ymax / 2);
	const REAL r = ymax*1.0f/6;
	RectF rect(r*(-1), (2 / 1.732 + 1)*r*(-1), 2 * r, 2 * r);
	
	g.TranslateTransform(pt.X, pt.Y);
	g.FillEllipse(&SolidBrush(Color::Red), rect);
	g.RotateTransform(120);
	g.FillEllipse(&SolidBrush(Color::Green), rect);
	g.RotateTransform(120);
	g.FillEllipse(&SolidBrush(Color::Blue), rect);
}

void DrawNineTest_2(HDC hdc, int xmax, int ymax)
{
	//DrawNineTest(hdc, xmax, ymax);//生成emf文件
	Image image(L"nine_1.emf");
	Graphics g(hdc);

	int w = image.GetWidth();
	int h = image.GetHeight();

	RectF r;
	Unit u;
	image.GetBounds(&r, &u);

	//g.DrawImage(&image, 0, 0);
	//g.DrawImage(&image, Rect(0, 0, r.Width, r.Height), r.X, r.Y, r.Width, r.Height,UnitPixel);
	//去掉所有的蓝色
	ColorMatrix cM = {
		1, 0, 0, 0, 0,
		1, 1, 1, 0, 0,
		1, 1, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};
	
	ImageAttributes imAtt;
	imAtt.SetColorMatrix(&cM);
	//imAtt.SetColorKey(Color::Green, Color::Green);
	g.DrawImage(&image, Rect(0, 0, r.Width, r.Height), r.X, r.Y, r.Width, r.Height, UnitPixel,&imAtt);

	Sleep(1000);

	//去掉所有的蓝色
	/*ColorMatrix cM2 = {
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};
	imAtt.SetColorMatrix(&cM2, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	g.DrawImage(&image, Rect(0, 0, r.Width, r.Height), r.X, r.Y, r.Width, r.Height, UnitPixel, &imAtt);

	Sleep(1000);

	ColorMatrix cM3 = {
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};
	imAtt.SetColorMatrix(&cM2, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	g.DrawImage(&image, Rect(0, 0, r.Width, r.Height), r.X, r.Y, r.Width, r.Height, UnitPixel, &imAtt);

	*/

}