#pragma once

void DrawColorMatrix(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Image image(L"ColorInput.bmp");
	ImageAttributes imageAttributes;

	UINT width = image.GetWidth();
	UINT height = image.GetHeight();

	ColorMatrix colorMatrix =
	{
		2.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	imageAttributes.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	g.DrawImage(&image, 0, 0);
	g.TranslateTransform(width + 10, 0);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, width, height, UnitPixel, &imageAttributes);

}

void DrawColorRemap(HDC hdc, int xmax, int ymax)
{
	Bitmap b(xmax/2-50, ymax/2);
	Graphics gimage(&b);
	//±³¾°À¶É«
	SolidBrush brush(Color::Blue);
	gimage.FillRectangle(&brush, 0, 0, xmax/2-50, ymax/2);
	brush.SetColor(Color::Yellow);
	gimage.FillRectangle(&brush,200, 100, 300, 200);
	brush.SetColor(Color::Green);
	gimage.FillEllipse(&brush, 100, 25, 150, 200);
	brush.SetColor(Color::Red);
	gimage.FillEllipse(&brush, 250, 50, 180, 120);

	gimage.FillRectangle(&brush, 250, 220, 180, 120);

	ImageAttributes ir;
	ColorMap colorMap[1];
	colorMap[0].oldColor = Color::Blue;
	colorMap[0].newColor = Color::White;

	ir.SetRemapTable(1, colorMap, ColorAdjustTypeBitmap);
	ir.SetOutputChannel(ColorChannelFlagsC, ColorAdjustTypeBitmap);
	Graphics g(hdc);
	g.DrawImage(&b, Rect(0, 0, xmax / 2 - 50, ymax / 2));

	g.TranslateTransform(xmax / 2, 0);

	g.DrawImage(&b, Rect(0, 0, xmax / 2 - 50, ymax / 2), 0, 0, xmax / 2 - 50, ymax / 2,UnitPixel,&ir);
}


void DrawKoutu(HDC hdc, int xmax, int ymax)
{
	Bitmap pic(_T("simple_texture.png"));
	ImageAttributes ir;
	ColorMap ma[1];
	pic.GetPixel(0, 0, &(ma[0].oldColor));
	ma[0].newColor = Color(0, 255, 0, 0);
	ir.SetRemapTable(1, ma, ColorAdjustTypeBitmap);

	Graphics g(hdc);
	g.FillRectangle(&SolidBrush(Color::Green),0, 0, pic.GetWidth(), pic.GetHeight());
	g.DrawImage(&pic, Rect(0, 0, pic.GetWidth(), pic.GetHeight()),
		0, 0, pic.GetWidth(), pic.GetHeight(), UnitPixel, &ir);

	g.TranslateTransform(pic.GetWidth() + 10, 0);
	g.FillRectangle(&SolidBrush(Color::Green), 0, 0, pic.GetWidth(), pic.GetHeight());
	g.DrawImage(&pic, Rect(0, 0, pic.GetWidth(), pic.GetHeight()));
}