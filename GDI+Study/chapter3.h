#pragma once


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

	//ʹ���Զ�������
	REAL dashVals[2] = {
		5.0f,  //�߳�5������
		2.0f   //���2������ }
	};
	pen.SetDashPattern(dashVals, 2);
	pen.SetColor(Color::Green);
	graphics.DrawLine(&pen, 10, 170, 300, 170);
}