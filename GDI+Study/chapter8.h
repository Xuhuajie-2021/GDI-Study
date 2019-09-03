#pragma once

void DrawMetafile(HDC hdc, int xmax, int ymax)
{
	Metafile mf(L"图元文件示例.emf", hdc);
	{
		LinearGradientBrush R2BBrush(
			Point(0, 10), Point(200, 10),
			Color::Red, Color::Blue);
		LinearGradientBrush B2YBrush(
			Point(0, 10), Point(200, 10),
			Color::Blue, Color::Yellow);
		Graphics g(&mf);
		Pen bluePen(Color::Blue);

		Rect r(0, 0, 200, 200);
		Rect r2(0, 50, 100, 100);
		g.DrawArc(&bluePen, r2, 180, 180);
		Rect r3(100, 50, 100, 100);
		g.DrawArc(&bluePen, r3, 0, 180);
		g.FillPie(&R2BBrush, r, 0, 180);
		g.FillPie(&B2YBrush, r, 180, 180);
		g.FillPie(&R2BBrush, r2, 180, 180);
		g.FillPie(&B2YBrush, r3, 0, 180);

		//文本
		SolidBrush solidBrush(Color::Black);
		FontFamily ff(_T("隶书"));
		Font font(&ff, 27, FontStyleRegular, UnitPixel);
		g.DrawString(L"图元文件示例", -1, &font, PointF(20, 80), &solidBrush);
	}

	Graphics g2(hdc);
	g2.DrawImage(&mf, 200, 100);
}

void DrawImageCropScale(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Image image(L"head.png");

	UINT width = image.GetWidth();
	UINT height = image.GetHeight();

	Rect desRect(width + 10, 0, 1.4*width, 1.4*height);
	g.DrawImage(&image, 0, 0);
	g.DrawImage(&image, desRect, 0, 0, 0.65*width, 0.65*height, UnitPixel);

}

//加入差值
void DrawUsingInterpolationMode(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Image image(L"beauty.jpg");
	UINT width = image.GetWidth();
	UINT height = image.GetHeight();
	g.DrawImage(&image, 0, 0);

	g.TranslateTransform(width + 10, 0);
	g.SetInterpolationMode(InterpolationModeNearestNeighbor);
	g.DrawImage(&image, Rect(0, 0, 0.6*width, 0.6*height), 0, 0, width, height, UnitPixel);

	g.TranslateTransform(width*0.6 + 10, 0);
	g.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	g.DrawImage(&image, Rect(0, 0, 0.6*width, 0.6*height), 0, 0, width, height, UnitPixel);

	g.TranslateTransform(width*0.6 + 10, 0);
	g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	g.DrawImage(&image, Rect(0, 0, 0.6*width, 0.6*height), 0, 0, width, height, UnitPixel);

}

//图片的旋转
void DrawImageRotate(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap image(L"beauty.jpg");
	UINT width = image.GetWidth();
	UINT height = image.GetHeight();
	g.DrawImage(&image, 0, 0);

	image.RotateFlip(RotateNoneFlipX);
	g.TranslateTransform(width, 0);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, width, height, UnitPixel);

	image.RotateFlip(RotateNoneFlipY);
	g.TranslateTransform(0, height);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, width, height, UnitPixel);

	image.RotateFlip(RotateNoneFlipX);
	g.ResetTransform();
	g.TranslateTransform(0, height);
	g.DrawImage(&image, Rect(0, 0, width, height), 0, 0, width, height, UnitPixel);

}

void DrawImageSkewing(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap image(L"beauty.jpg");
	UINT width = image.GetWidth();
	UINT height = image.GetHeight();

	//距离左上
	const REAL left = 10.0f;
	const REAL top = 10.0f;

	//画正上方
	PointF ptup[3] = {
		PointF(left + width / 2, top),
		PointF(left + width / 2+width, top),
		PointF(left,top+height/2)
	};

	PointF ptr[3] = {
		PointF(left + width, top + height / 2),
		PointF(left + width / 2 + width, top),
		PointF(left + width, top + height / 2+height)
	};

	PointF ptface[3] = {
		PointF(left , top + height / 2),
		PointF(left+width, top + height / 2),
		PointF(left , top + height / 2 + height)
	};
	
	g.DrawImage(&image, ptup,3,0,0,width,height,UnitPixel);
	g.DrawImage(&image, ptr, 3, 0, 0, width, height, UnitPixel);
	g.DrawImage(&image, ptface, 3, 0, 0, width, height, UnitPixel);
}

void DrawImageThumbnail(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	Bitmap image(L"beauty.jpg");
	UINT width = image.GetWidth();
	UINT height = image.GetHeight();

	float shear = height / width;
	Image* pI = image.GetThumbnailImage(80, 80 * shear, NULL, NULL);

	TextureBrush b(pI);
	g.FillEllipse(&b, 0, 0, xmax, ymax);
}

void DrawImageClone(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap image(L"beauty.jpg");
	UINT width = image.GetWidth();
	UINT height = image.GetHeight();

	Rect Block[4];
	Block[0] = Rect(0, 0, width / 2, height / 2);
	Block[1] = Rect(width / 2, 0, width / 2, height / 2);
	Block[2] = Rect(0, height / 2, width / 2, height / 2);
	Block[3] = Rect(width / 2, height / 2, width / 2, height / 2);

	Bitmap* s[4];
	for (int i = 0; i < 4;++i)
	{
		s[i] = image.Clone(Block[i], PixelFormatDontCare);
		g.DrawImage(s[i], Block[i]);
		Sleep(1000);
	}

	
}