#pragma once

void DrawImageEncoder(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	SolidBrush brush(Color::Blue);
	FontFamily ff(L"华文楷体");
	Font f(&ff, 20, FontStyleRegular, UnitPixel);

	UINT num;
	UINT size;
	ImageCodecInfo* pIci;
	GetImageEncodersSize(&num, &size);
	pIci = (ImageCodecInfo*)malloc(size);

	GetImageEncoders(num, size, pIci);
	CString temp, Info;
	for (UINT j = 0; j < num;++j)
	{
		temp.Format(L"编码器名称：%s\t文件格式拓展名：%s\t",
			pIci[j].CodecName, pIci[j].FilenameExtension);
		temp.AppendChar('\n');
		Info += temp;
	}

	free(pIci);
	g.DrawString(Info, -1, &f,PointF(0, 0), NULL, &SolidBrush(Color::Black));

}

void DrawImageDecoder(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	SolidBrush brush(Color::Blue);
	FontFamily ff(L"华文楷体");
	Font f(&ff, 20, FontStyleRegular, UnitPixel);

	UINT num;
	UINT size;
	ImageCodecInfo* pIci;
	GetImageDecodersSize(&num, &size);
	pIci = (ImageCodecInfo*)malloc(size);

	GetImageDecoders(num, size, pIci);
	CString temp, Info;
	for (UINT j = 0; j < num; ++j)
	{
		temp.Format(L"编码器名称：%s\t文件格式拓展名：%s\t",
			pIci[j].CodecName, pIci[j].FilenameExtension);
		temp.AppendChar('\n');
		Info += temp;
	}

	free(pIci);
	g.DrawString(Info, -1, &f, PointF(0, 0), NULL, &SolidBrush(Color::Black));

}

void GetEncodeClsid(const CString & name, CLSID& id)
{
	UINT num, size;
	GetImageEncodersSize(&num, &size);
	ImageCodecInfo* pinfo = (ImageCodecInfo*)malloc(size);
	GetImageEncoders(num, size, pinfo);
	for (int j = 0; j < num;j++)
	{
		if (name==pinfo[j].MimeType)
		{
			id = pinfo[j].Clsid;
			return;
		}
	}


	delete pinfo;

}

void SaveBMP2PNG(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	CLSID encodeClsid;
	Status s;
	Image image(L"colorinput.bmp");
	RectF r(0, 0, image.GetWidth() / 2, image.GetHeight() / 2);
	g.DrawImage(&image, r);
	GetEncodeClsid(L"image/png", encodeClsid);

	s = image.Save(L"colorinput.png", &encodeClsid,NULL);

	if (s == Ok)
	{
		Image pn(L"colorinput.png");
		g.TranslateTransform(r.Width + 10, 0);
		g.DrawImage(&pn, 0, 0, image.GetWidth(), image.GetHeight());
	}

}

void DrawMultipleFrameImage(HDC hdc, int xmax, int ymax)
{
	EncoderParameters epts;
	ULONG paValue;
	Status s;

	epts.Count = 1;
	epts.Parameter[0].Guid = EncoderSaveFlag;
	epts.Parameter[0].Type = EncoderParameterValueTypeLong;

	epts.Parameter[0].NumberOfValues = 1;
	epts.Parameter[0].Value = &paValue;

	CLSID id;
	GetEncodeClsid(L"image/tiff", id);
	Image i1(L"beauty.jpg");
	Image i2(L"head.png");
	Image i3(L"colorinput.bmp");
	Image i4(L"colortable.bmp");

	paValue = EncoderValueMultiFrame;
	s = i1.Save(L"MultiFrame.tif", &id, &epts);

	paValue = EncoderValueFrameDimensionPage;
	s = i1.SaveAdd(&i2,&epts);

	paValue = EncoderValueFrameDimensionPage;
	s = i1.SaveAdd(&i3, &epts);

	paValue = EncoderValueFrameDimensionPage;
	s = i1.SaveAdd(&i4, &epts);

	paValue = EncoderValueFlush;
	s = i1.SaveAdd(&epts);

}

void DrawQueryImage(HDC hdc, int xmax, int ymax)
{
	Graphics g(hdc);
	SolidBrush brush(Color::Blue);
	FontFamily ff(L"宋体");
	Font f(&ff, 16, FontStyleRegular, UnitPixel);
	Image image(L"farmer.jpg");
	UINT count = image.GetPropertyCount();

	PROPID* ids = new PROPID[count];
	image.GetPropertyIdList(count, ids);

	CString tmp,msg;
	for (UINT j = 0; j < count;j++)
	{
		tmp.Format(L"第%d个可供查找的属性名的标记值为:%x\n",j,ids[j]);
		//msg += tmp;
	}
	//msg.AppendChar('\n\n');

	UINT size = 0;
	PropertyItem * item = nullptr;
	for (int i = 0; i < count;++i)
	{
		size = image.GetPropertyItemSize(ids[i]);
		tmp.Format(L"第%d个属性名对应的属性项需要%d个字节来描述\n", i, size);
		msg += tmp;
		item = (PropertyItem *)malloc(size);
		tmp.Format(L"第%d个属性名对应的属性项的信息为：\n", i);
		msg += tmp;
		image.GetPropertyItem(ids[i], size, item);
		tmp.Format(L"\t属性项的长度为%u\n\t 数据类型为%d\n",item->length,item->type);
		msg += tmp;
	}
	g.DrawString(msg, -1, &f, PointF(0, 0), NULL, &brush);


}