#pragma once

void DrawFadeInOut(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap bitmap(L"beauty.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();

	g.DrawImage(&bitmap, Rect(width+60, 0, width, height), 0, 0, width, height, UnitPixel);

	ColorMatrix colorMatrix =
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};
	ImageAttributes imageAtt;
	for (float i = 0.0f; i <= 1.0f;i+=0.02)
	{
// 		colorMatrix.m[0][0] = i;
// 		colorMatrix.m[1][1] = i;
// 		colorMatrix.m[2][2] = i;
		colorMatrix.m[3][3] = i;
		Sleep(20);
		imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		g.DrawImage(&bitmap, Rect(30, 0, width, height), 0, 0, width, height, UnitPixel, &imageAtt);


	}

	Sleep(1000);
	for (float i = 1.0f; i >=0.0f; i -= 0.02)
	{
// 		colorMatrix.m[0][0] = i;
// 		colorMatrix.m[1][1] = i;
// 		colorMatrix.m[2][2] = i;
		colorMatrix.m[3][3] = i;

		imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		g.DrawImage(&bitmap, Rect(30, 0, width, height), 0, 0, width, height, UnitPixel, &imageAtt);


	}
}


//最大值 Max(R,G,B) 平均值 (R+G+B)/3 加权 r=30% g=59% b11%
void DrawGrayImage(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap bitmap(L"wifeson.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();

	g.DrawImage(&bitmap, Rect(0, 0, width, height));

	Color color;
	for (int i = width; i > 0;i--)
	{
		for (int j = height; j > 0;j--)
		{
			bitmap.GetPixel(i, j, &color);
			int middle = (color.GetRed() + color.GetGreen() + color.GetBlue()) / 3;
			Color temp;
			temp.SetValue(color.MakeARGB(255, middle, middle, middle));
			bitmap.SetPixel(i, j, temp);
		}
	}
	g.DrawImage(&bitmap, Rect(width+10, 0, width, height));

	for (int i = width; i > 0; i--)
	{
		for (int j = height; j > 0; j--)
		{
			bitmap.GetPixel(i, j, &color);
			int R = color.GetRed();
			int G = color.GetG();
			int B = color.GetB();

			if (R <= 127) R = 0;
			else if (R >= 192) R = 255;
			else R = 4 * R - 510;

			if (G <= 63) G = 254 - 4 * G;
			else if (G <= 127) G = 4 * G - 254;
			else if (G <= 191) G = 255;
			else G = 1022 - 4 * G;

			if (B <= 63) B = 255;
			else if (B >= 128) B = 0;
			else if (B >= 67 && B <= 127) B = 510 - 4 * G;

			Color temp;
			temp.SetValue(color.MakeARGB(255, R, G, B));
			bitmap.SetPixel(i, j, temp);
		}
	}
	g.DrawImage(&bitmap, Rect(2*width + 20, 0, width, height));
}

void DrawRevertImage(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap bitmap(L"wifeson.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();

	Color color;
	for (int i = width; i > 0; i--)
	{
		for (int j = height; j > 0; j--)
		{
			bitmap.GetPixel(i, j, &color);
			int R = 255-color.GetRed();
			int G = 255-color.GetG();
			int B = 255-color.GetB();
			Color temp;
			temp.SetValue(color.MakeARGB(255, R, G, B));
			bitmap.SetPixel(i, j, temp);
		}
	}
	g.DrawImage(&bitmap, Rect(0, 0, width, height));

	for (int i = width; i > 0; i--)
	{
		for (int j = height; j > 0; j--)
		{
			bitmap.GetPixel(i, j, &color);
			int R = 255 - color.GetRed();
			int G = 255 - color.GetG();
			int B = 255 - color.GetB();
			Color temp;
			temp.SetValue(color.MakeARGB(255, R, G, B));
			bitmap.SetPixel(i, j, temp);
		}
	}
	g.DrawImage(&bitmap, Rect(width+10, 0, width, height));
}

void DrawEmBoss(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap bitmap(L"wifeson.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();

	Color color,colorLeft;
	for (int i = width; i > 0; i--)
	{
		for (int j = height; j > 0; j--)
		{
			bitmap.GetPixel(i, j, &color);
			bitmap.GetPixel(i-1, j-1, &colorLeft);
			int R = max(67,min(255,abs(color.GetR()-colorLeft.GetR()+128)));
			int G = max(67, min(255, abs(color.GetG() - colorLeft.GetG() + 128)));
			int B = max(67, min(255, abs(color.GetB() - colorLeft.GetB() + 128)));
			Color temp;
			temp.SetValue(color.MakeARGB(255, R, G, B));
			bitmap.SetPixel(i, j, temp);
		}
	}
	g.DrawImage(&bitmap, Rect(0, 0, width, height));

	Bitmap* bim2 = bitmap.Clone(0, 0, width, height, PixelFormatDontCare);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			bim2->GetPixel(i, j, &color);
			bim2->GetPixel(i + 1, j + 1, &colorLeft);
			int R = max(67, min(255, abs(color.GetR() - colorLeft.GetR() + 128)));
			int G = max(67, min(255, abs(color.GetG() - colorLeft.GetG() + 128)));
			int B = max(67, min(255, abs(color.GetB() - colorLeft.GetB() + 128)));
			Color temp;
			temp.SetValue(color.MakeARGB(255, R, G, B));
			bim2->SetPixel(i, j, temp);
		}
	}
	g.DrawImage(bim2, Rect(width + 10, 0, width, height));
}


void DrawCanvas(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap bitmap(L"wifeson.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();

	g.DrawImage(&bitmap, Rect(10, 0, width, height));

	Color color;
	srand(time(0));
	for (int i = 0; i < width-4; i++)
	{
		for (int j = 0; j < height-4; j++)
		{
			int add = rand() % 5;
			bitmap.GetPixel(i+add, j+add, &color);
			bitmap.SetPixel(i, j, color);
		}
	}
	g.DrawImage(&bitmap, Rect(width+20, 0, width, height));

	
}

void DrawWoods(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap bitmap(L"wifeson.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();

	g.DrawImage(&bitmap, Rect(10, 0, width, height));

	Color color;
	srand(time(0));
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			bitmap.GetPixel(i, j, &color);
			int average = (color.GetR() + color.GetG() + color.GetB()) / 3;
			if (average>=255/2)
			{
				bitmap.SetPixel(i, j, Color());
			}
			else
			{
				bitmap.SetPixel(i, j, Color(Color::White));
			}
		}
	}
	g.DrawImage(&bitmap, Rect(width + 20, 0, width, height));


}

float distance(const CPoint& p1, const CPoint& p2)
{
	float i = pow(p2.x - p1.x, 2.0f) + pow(p2.y - p1.y, 2.0f);
	return sqrt(i);
}

void DrawLight(HDC hdc, int xmax, int ymax, CPoint center)
{
	Graphics g(hdc);
	Bitmap bitmap(L"wifeson.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();

	//g.DrawImage(&bitmap, Rect(10, 0, width, height));

	//强光半径，80
	float R = 80.0f;

	Color color,colorTmp;
	srand(time(0));
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			CPoint temp(i, j);
			if (distance(temp,center)<R)
			{
				bitmap.GetPixel(i, j, &color);
				int r = color.GetR() + 220 * (1 - distance(temp, center) / R);
				r = max(0, min(r, 255));
				int g = color.GetG() + 220 * (1 - distance(temp, center) / R);
				g = max(0, min(r, 255));
				int b = color.GetB() + 220 * (1 - distance(temp, center) / R);
				b = max(0, min(r, 255));
				colorTmp.SetValue(colorTmp.MakeARGB(255, r, g, b));
				bitmap.SetPixel(i, j, colorTmp);
			}
		}
		
	}
	
	g.DrawImage(&bitmap, Rect(0, 0, width, height));

}


void DrawSmooth(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	Bitmap bitmap(L"wifeson.jpg");
	Bitmap bitmap2(L"wifeson.jpg");

	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();


	ColorMatrix cm = {
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0.2, 0,
		0, 0, 0, 0, 1
	};
	ImageAttributes imageAttr;
	imageAttr.SetColorMatrix(&cm);


	g.DrawImage(&bitmap, Rect(10, 0, width, height),0,0,width,height,UnitPixel,&imageAttr);

	Color color, colorTmp;
	int R=0, G=0, B=0;
	for (int i = 1; i < width-1; i++)
	{
		for (int j = 1; j < height-1; j++)
		{
			for (int k = 0; k < 3;k++)
			{
				for (int z = 0; z < 3;z++)
				{
					bitmap.GetPixel(i-1+k, j-1+z, &color);
					R += color.GetR();
					G += color.GetG();
					B += color.GetB();
				}
			}
			R /= 9;
			G /= 9;
			B /= 9;

			colorTmp.SetValue(colorTmp.MakeARGB(255, R, G, B));
			bitmap.SetPixel(i, j, colorTmp);	
		}
	}
	g.DrawImage(&bitmap, Rect(width + 20, 0, width, height));

	float dep = 0.550f;
	for (int i = width; i > 0; i--)
	{
		for (int j = height; j > 0; j--)
		{
			bitmap2.GetPixel(i, j, &color);
			bitmap2.GetPixel(i - 1, j - 1, &colorTmp);
			int R = max(0, min(255, dep*(color.GetR() - colorTmp.GetR()) + color.GetR()));
			int G = max(0, min(255, dep*(color.GetG() - colorTmp.GetG()) + color.GetG()));
			int B = max(0, min(255, dep*(color.GetB() - colorTmp.GetB()) + color.GetB()));
			Color temp;
			temp.SetValue(color.MakeARGB(255, R, G, B));
			bitmap2.SetPixel(i, j, temp);
		}
	}
	g.DrawImage(&bitmap2, Rect(2 * width + 30, 0, width, height));
}