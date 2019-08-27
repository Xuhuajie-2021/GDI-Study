#pragma once

//本章主要是字体的例子

void OnGDIFontChoose(HDC hdc,int xmax, int ymax)
{
	CFontDialog dlg;
	if (dlg.DoModal()!=IDOK)
	{
		return;
	}

	LOGFONT lf;
	memcpy_s(&lf, sizeof(LOGFONT),dlg.m_cf.lpLogFont,sizeof(LOGFONT));
	HFONT hf = ::CreateFontIndirect(&lf);

	SelectObject(hdc, hf);
	SetTextColor(hdc, dlg.GetColor());

	CString msg(_T("输出文本"));
	RECT r;
	r.top = r.left = 0;
	r.right = xmax;
	r.bottom = ymax;
	DrawText(hdc, msg, msg.GetLength(), &r, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	DeleteObject(hf);
}


void OnGDIPlusFontChoose(HDC hdc, int xmax, int ymax)
{
	CFontDialog dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	LOGFONT lf;
	memcpy_s(&lf, sizeof(LOGFONT), dlg.m_cf.lpLogFont, sizeof(LOGFONT));
	Font f(hdc, &lf);
	COLORREF col = dlg.GetColor();
	Color c(255, GetRValue(col), GetGValue(col), GetBValue(col));
	SolidBrush sb(c);
	StringFormat sf;
	sf.SetAlignment(StringAlignmentCenter);
	sf.SetLineAlignment(StringAlignmentCenter);
	Graphics g(hdc);
	CString msg(_T("输出文本"));
	RectF r(0, 0, xmax, ymax);
	g.DrawString(msg, -1, &f,r, &sf, &sb);
}

void DrawFontText(HDC hdc, int xmax, int ymax)
{
	FontFamily ff(_T("微软雅黑"));
	Font f(&ff, 16, FontStyleStrikeout, UnitPixel);
	StringFormat sf;
	sf.SetAlignment(StringAlignmentCenter);
	sf.SetLineAlignment(StringAlignmentCenter);
	Graphics g(hdc);
	CString msg(_T("输出文本"));
	RectF r(0, 0, xmax, ymax);
	SolidBrush sb(Color::Red);
	g.DrawString(msg, -1, &f, r, &sf, &sb);
}

void DrawFontEnum(HDC hdc, int xmax, int ymax)
{
	InstalledFontCollection ifc;
	int count = ifc.GetFamilyCount();
	FontFamily pffs[500];
	int found;
	ifc.GetFamilies(count, pffs, &found);
	CString str;
	for (int i = 0; i < count;++i)
	{
		TCHAR fn[50];
		pffs[i].GetFamilyName(fn);
		str.Append(fn);
		str.Append(_T(" "));
	}
	Graphics g(hdc);
	Font f(_T("Arial"), 16);
	RectF r(0, 0, xmax, ymax);
	g.DrawString(str, -1, &f, r, NULL,&SolidBrush(Color::Black));
}

void DrawFontHint(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	FontFamily ff(_T("Arial"));
	Font f(&ff, 60, FontStyleRegular, UnitPixel);

	for (int i = 0; i < 6;i++)
	{
		g.SetTextRenderingHint((TextRenderingHint)i);
		g.DrawString(_T("Render"), -1, &f, PointF(0, 0), &SolidBrush(Color::Red));
		g.TranslateTransform(0, f.GetHeight(0.0f));
	}
}

void DrawFontPrivate(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);

	PrivateFontCollection pfc;
	if (pfc.AddFontFile(_T("C:\\Windows\\Font\\Zhuanti.ttf")) != Ok)
	{
		MessageBox(NULL, _T("添加字体出错，请确认是否存在"),_T("W"),0);
		return;
	}

	FontFamily ff[1];
	int numF;
	int count= pfc.GetFamilyCount();
	WCHAR fn[50];
	pfc.GetFamilies(count, ff, &numF);

	ff[0].GetFamilyName(fn);
	Font f(fn, 45, NULL, UnitPixel, &pfc);
	g.DrawString(fn, -1, &f, PointF(10, 10), &SolidBrush(Color::Green));
}

void DrawFontBaseLine(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	FontFamily ff(_T("Arial"));
	//默认是UnitPoint
	Font f(&ff, 80, FontStyleRegular, UnitPixel);
	Pen pen(Color::Blue, 1);
	SolidBrush brush(Color::Blue);

	REAL ybaseline = ymax / 2;
	g.DrawLine(&pen, PointF(0, ybaseline), PointF(xmax, ybaseline));

	REAL cyLineSpace = f.GetHeight(0.0);
	int iCellSpace = ff.GetLineSpacing(FontStyleRegular);
	int iCellAscent = ff.GetCellAscent(FontStyleRegular);
	REAL cyAscent = cyLineSpace*iCellAscent / iCellSpace;
	REAL Delta = cyLineSpace*(iCellSpace - iCellAscent - ff.GetCellDescent(FontStyleRegular)) / iCellSpace;
	g.DrawLine(&pen, PointF(0, ybaseline - cyAscent), PointF(xmax, ybaseline - cyAscent));
	g.DrawLine(&pen, PointF(0, ybaseline - 2*cyAscent), PointF(xmax, ybaseline - 2*cyAscent));

	g.SetTextRenderingHint(TextRenderingHintAntiAlias);
	g.DrawString(_T("AaFfgSs{"), -1, &f, PointF(0, ybaseline - cyAscent), &brush);
	g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	g.DrawString(_T("AaFfgSs{"), -1, &f, PointF(0, ybaseline - 2 * (cyAscent+Delta)), &brush);
}

void DrawFontMeasure(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);

	FontFamily ff(_T("Arial"));
	Font font(&ff, 30, FontStyleRegular, UnitPixel);
	Font font2(&ff, 18, FontStyleRegular, UnitPixel);

	RectF lR(10, 10, 200, 100);
	SolidBrush brush(Color::Black);

	RectF boundRect;
	int codepointfitted = 0;
	int linefilled = 0;
	CString str(_T("123456789ABCDEFGHIJKLMOPQRSTUVWXYZ"));
	//测量文本
	g.MeasureString(str, -1, &font, lR, NULL, &boundRect, &codepointfitted, &linefilled);
	CString tmp;
	tmp.Format(_T("欲输出的字符串未\n\"%s\"\n共%d字符,\n其中在输定的输出矩阵中，\n只输出了%d行，共%d个字符"),
				str, str.GetLength(), linefilled, codepointfitted);

	g.DrawRectangle(&Pen(Color(0, 255, 255), 2), lR);
	g.DrawRectangle(&Pen(Color(0, 0, 0), 1), boundRect);

	g.DrawString(str, -1, &font, boundRect, NULL, &brush);
	g.DrawString(tmp, -1, &font2, PointF(10, 180), NULL, &brush);

}

void DrawFontOutClip(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);

	FontFamily ff(_T("Arial"));
	Font font(&ff, 30, FontStyleRegular, UnitPixel);
	Font font2(&ff, 18, FontStyleRegular, UnitPixel);

	RectF lR(10, 10, 130, 80);
	SolidBrush brush(Color::Black);

	RectF boundRect;
	int codepointfitted = 0;
	int linefilled = 0;
	CString str(_T("123456789ABCDEFGHIJKLMOPQRSTUVWXYZ"));
	StringFormat sf;
	sf.SetTrimming(StringTrimmingEllipsisWord);
	sf.SetFormatFlags(StringFormatFlagsNoClip);
	//测量文本
	g.MeasureString(str, -1, &font, lR, &sf, &boundRect, &codepointfitted, &linefilled);
	CString tmp;
	tmp.Format(_T("欲输出的字符串未\n\"%s\"\n共%d字符,\n其中在输定的输出矩阵中，\n只输出了%d行，共%d个字符"),
		str, str.GetLength(), linefilled, codepointfitted);

	g.DrawRectangle(&Pen(Color(0, 255, 255), 2), lR);
	g.DrawRectangle(&Pen(Color(0, 0, 0), 1), boundRect);

	g.DrawString(str, -1, &font, boundRect, &sf, &brush);
	g.DrawString(tmp, -1, &font2, PointF(10, 180), NULL, &brush);

}

void DrawFontTabs(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	StringFormat sf;
	FontFamily ff(_T("Arial"));
	Font f(&ff, 30, FontStyleBold, UnitPixel);
	SolidBrush solidBrush(Color::Black);

	CString str = _T("A\tB\tC\tD");
	g.DrawString(str, -1, &f, PointF(0, 10), &sf, &solidBrush);

	//设置tab信息
	g.TranslateTransform(0, 30.0f);
	REAL tabs[] = { 40.0f, 30.0f, 40.0f };
	sf.SetTabStops(0.0f, 3, tabs);
	g.DrawString(str, -1, &f, PointF(0, 10), &sf, &solidBrush);

	//设置tab信息
	g.TranslateTransform(0, 30.0f);
	REAL tabs2[] = { 60.0f, 60.0f, 60.0f };
	sf.SetTabStops(0.0f, 3, tabs2);
	g.DrawString(str, -1, &f, PointF(0, 10), &sf, &solidBrush);
}

//尝试自己画出阴影字
void DrawFontShadow(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	FontFamily ff(_T("华文楷体"));
	Font f(&ff, 100, FontStyleBold, UnitPixel);
	SolidBrush foreb(Color::Red);
	SolidBrush backb(Color(100,0,0,0));

	//先画阴影
	g.DrawString(_T("阴影字"), 6, &f, PointF(50.0f, 50.0f), &backb);
	//再画字体
	g.TranslateTransform(-10.0f, -5.0f);
	g.DrawString(_T("阴影字"), -1, &f, PointF(50.0f, 50.0f), &foreb);


	//先画阴影
	g.ResetTransform();
	g.TranslateTransform(0,1.5*f.GetHeight(0.0f));
	HatchBrush hatchBrush((HatchStyle)2, Color::Black, Color::White);
	for (int i = 0; i < 40;i++)
	{
		g.DrawString(_T("阴影字"), 6, &f, PointF(50.0f + i + 2, 50.0f + i + 2), &hatchBrush);
	}
	g.DrawString(_T("阴影字"), -1, &f, PointF(50.0f, 50.0f), &foreb);

}

void DrawFontGridant(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	g.SetTextRenderingHint(TextRenderingHintSystemDefault);
	FontFamily ff(_T("Arial"));
	Font f(&ff, 100, FontStyleRegular, UnitPixel);

	CString str = _T("阴影字ABC123");
	StringFormat sf;
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);
	CharacterRange* pRange = new CharacterRange[str.GetLength()];
	for (int i = 0; i < str.GetLength(); ++i)
	{
		pRange[i].First = i;
		pRange[i].Length = 1;
	}
	sf.SetMeasurableCharacterRanges(str.GetLength(), pRange);

	Region* pRegion = new Region[str.GetLength()];
	g.MeasureCharacterRanges(str, -1, &f, RectF(0, 0, xmax, ymax), &sf, str.GetLength(), pRegion);
	RectF rect;
	REAL startpos = 0.0f;
	for (int i = 0; i < str.GetLength(); ++i)
	{
		pRegion[i].GetBounds(&rect, &g);
		LinearGradientBrush lgb(rect, Color::Red, Color::Blue, LinearGradientModeHorizontal);

		g.DrawString(CString(str.GetAt(i)), -1, &f, RectF(rect.X-rect.Width/5.0 , 0.0f, 2*rect.Width, rect.Height), &sf, &lgb);
		startpos += rect.Width;
	}

}

void DrawFontGridant2(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	g.SetTextRenderingHint(TextRenderingHintSystemDefault);
	FontFamily ff(_T("Arial"));
	Font f(&ff, 100, FontStyleRegular, UnitPixel);

	CString str = _T("阴影字ABC123");
	StringFormat sf;
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);

	RectF outbound;
	RectF drawRect = {0,0,0,0};

	for (int i = 0; i < str.GetLength(); ++i)
	{
		g.MeasureString(CString(str.GetAt(i)), 1, &f, RectF(0, 0, xmax, ymax), &outbound);
		if (i == 0)
		{
			outbound.Width -= outbound.Width / 6;
			drawRect = outbound;
			g.FillRectangle(&SolidBrush(Color(100, 0, 0, 0)), drawRect);
		}
		else
		{
			drawRect.X += outbound.Width;
			drawRect.Width = outbound.Width;
		}
		
		LinearGradientBrush lgb(drawRect, Color::Red, Color::Blue, LinearGradientModeHorizontal);
		g.FillRectangle(&SolidBrush(Color(100, 0, 0, 0)), drawRect);
		g.DrawString(CString(str.GetAt(i)), -1, &f, drawRect, &sf, &lgb);
		
	}

}

