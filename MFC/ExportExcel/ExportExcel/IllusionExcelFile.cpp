#include "stdafx.h"
#include "IllusionExcelFile.h"

COleVariant
covTrue((short)TRUE),
covFalse((short)FALSE),
covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

//类的静态数据成员，Excel进程实例
CApplication IllusionExcelFile::excel_application_;


IllusionExcelFile::IllusionExcelFile() :
	already_preload_(FALSE)
{
}

IllusionExcelFile::~IllusionExcelFile()
{
	//关闭Excel文件
	CloseExcelFile();
}


//初始化EXCEL文件
BOOL IllusionExcelFile::InitExcel()
{
	//创建Excel服务器(启动Excel) 
	if (!excel_application_.CreateDispatch(_T("Excel.Application"), NULL))
	{
		AfxMessageBox(_T("创建Excel服务失败,你可能没有安装EXCEL，请检查!"));
		return FALSE;
	}

	excel_application_.put_DisplayAlerts(FALSE);
	return TRUE;
}

//释放Excel资源
void IllusionExcelFile::ReleaseExcel()
{
	excel_application_.Quit();
	excel_application_.ReleaseDispatch();
	excel_application_ = NULL;
}

//打开Excel文件
BOOL IllusionExcelFile::OpenExcelFile(const CString& file_name)
{
	//先关闭
	CloseExcelFile();

	//利用模板文件建立新文档 
	excel_books_.AttachDispatch(excel_application_.get_Workbooks(), true);
	LPDISPATCH lpDis = NULL;
	lpDis = excel_books_.Add(COleVariant(file_name));
	if (lpDis)
	{
		excel_work_book_.AttachDispatch(lpDis);
		//得到Worksheets 
		excel_sheets_.AttachDispatch(excel_work_book_.get_Worksheets(), true);

		//记录打开的文件名称
		open_excel_file_ = file_name;

		return TRUE;
	}

	return FALSE;
}

//关闭打开的Excel 文件,默认情况不保存文件
void IllusionExcelFile::CloseExcelFile(BOOL if_save)
{
	//如果已经打开，关闭文件
	if (open_excel_file_.IsEmpty() == FALSE)
	{
		//如果保存,交给用户控制,让用户自己存，如果自己SAVE，会出现莫名的等待
		if (if_save)
		{
			ShowInExcel(TRUE);
		}
		else
		{
			//关闭工作簿
			excel_work_book_.Close(COleVariant(short(FALSE)), COleVariant(open_excel_file_), covOptional);
			excel_books_.Close();
		}

		//打开文件的名称清空
		open_excel_file_.Empty();
	}

	excel_current_range_.ReleaseDispatch();
	excel_work_sheet_.ReleaseDispatch();
	excel_sheets_.ReleaseDispatch();
	excel_work_book_.ReleaseDispatch();
	excel_books_.ReleaseDispatch();
}

void IllusionExcelFile::SaveasXSLFile(const CString &xls_file)
{
	excel_work_book_.SaveAs(COleVariant(xls_file),
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		0,
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		covOptional);
	return;
}


int IllusionExcelFile::GetSheetCount()
{
	return excel_sheets_.get_Count();
}


CString IllusionExcelFile::GetSheetName(long table_index)
{
	CWorksheet sheet;
	sheet.AttachDispatch(excel_sheets_.get_Item(COleVariant((long)table_index)), true);
	CString name = sheet.get_Name();
	sheet.ReleaseDispatch();
	return name;
}

//按照序号加载Sheet表格,可以提前加载所有的表格内部数据
BOOL IllusionExcelFile::LoadSheet(long table_index, BOOL pre_load)
{
	LPDISPATCH lpDis = NULL;
	excel_current_range_.ReleaseDispatch();
	excel_work_sheet_.ReleaseDispatch();
	lpDis = excel_sheets_.get_Item(COleVariant((long)table_index));
	if (lpDis)
	{
		excel_work_sheet_.AttachDispatch(lpDis, true);
		excel_current_range_.AttachDispatch(excel_work_sheet_.get_Cells(), true);
	}
	else
	{
		return FALSE;
	}

	already_preload_ = FALSE;
	//如果进行预先加载
	if (pre_load)
	{
		PreLoadSheet();
		already_preload_ = TRUE;
	}

	return TRUE;
}

//按照名称加载Sheet表格,可以提前加载所有的表格内部数据
BOOL IllusionExcelFile::LoadSheet(const CString& sheet, BOOL pre_load)
{
	LPDISPATCH lpDis = NULL;
	excel_current_range_.ReleaseDispatch();
	excel_work_sheet_.ReleaseDispatch();
	lpDis = excel_sheets_.get_Item(COleVariant(sheet));
	if (lpDis)
	{
		excel_work_sheet_.AttachDispatch(lpDis, true);
		excel_current_range_.AttachDispatch(excel_work_sheet_.get_Cells(), true);

	}
	else
	{
		return FALSE;
	}
	
	already_preload_ = FALSE;
	//如果进行预先加载
	if (pre_load)
	{
		PreLoadSheet();
		already_preload_ = TRUE;
	}

	return TRUE;
}

//得到列的总数 
int IllusionExcelFile::GetColumnCount()
{
	CRange range;
	CRange usedRange;
	usedRange.AttachDispatch(excel_work_sheet_.get_UsedRange(), true);
	range.AttachDispatch(usedRange.get_Columns(), true);
	int count = range.get_Count();
	usedRange.ReleaseDispatch();
	range.ReleaseDispatch();
	return count;
}

//得到行的总数
int IllusionExcelFile::GetRowCount()
{
	CRange range;
	CRange usedRange;
	usedRange.AttachDispatch(excel_work_sheet_.get_UsedRange(), true);
	range.AttachDispatch(usedRange.get_Rows(), true);
	int count = range.get_Count();
	usedRange.ReleaseDispatch();
	range.ReleaseDispatch();
	return count;
}

//检查一个CELL是否是字符串
BOOL IllusionExcelFile::IsCellString(long irow, long icolumn)
{
	CRange range;
	range.AttachDispatch(excel_current_range_.get_Item(COleVariant((long)irow), COleVariant((long)icolumn)).pdispVal, true);
	COleVariant vResult = range.get_Value2();
	//VT_BSTR标示字符串
	if (vResult.vt == VT_BSTR)
	{
		return TRUE;
	}
	return FALSE;
}

//检查一个CELL是否是数值
BOOL IllusionExcelFile::IsCellInt(long irow, long icolumn)
{
	CRange range;
	range.AttachDispatch(excel_current_range_.get_Item(COleVariant((long)irow), COleVariant((long)icolumn)).pdispVal, true);
	COleVariant vResult = range.get_Value2();
	//好像一般都是VT_R8
	if (vResult.vt == VT_INT || vResult.vt == VT_R8)
	{
		return TRUE;
	}
	return FALSE;
}

// 只有字符串VT_BSTR 和 8字节实数 VT_R8 的形式！
CString IllusionExcelFile::GetCellString(long irow, long icolumn)
{

	COleVariant vResult;
	CString str;

	if (already_preload_ == FALSE)
	{
		CRange range;
		range.AttachDispatch(excel_current_range_.get_Item(COleVariant((long)irow), COleVariant((long)icolumn)).pdispVal, true);
		vResult = range.get_Value2();
		range.ReleaseDispatch();
	}
	//如果数据预先加载
	else
	{
		long read_address[2];
		VARIANT val;
		read_address[0] = irow;
		read_address[1] = icolumn;
		ole_safe_array_.GetElement(read_address, &val);
		vResult = val;
	}
	//字符串
	if (vResult.vt == VT_BSTR)		//VT_BSTR
	{
		str = vResult.bstrVal;

		//AfxMessageBox(_T("VT_BSTR"));
	}
	//整数
	else if (vResult.vt == VT_INT)
	{
		str.Format(_T("%d"), vResult.pintVal);
	}
	//8字节的数字 
	else if (vResult.vt == VT_R8)	//VT_R8
	{
		str.Format(_T("%0.6lf"), vResult.dblVal);

		//AfxMessageBox(_T("VT_R8"));
	}
	//时间格式
	else if (vResult.vt == VT_DATE)
	{
		SYSTEMTIME st;
		VariantTimeToSystemTime(vResult.date, &st);
		CTime tm(st);
		str = tm.Format(_T("%Y-%m-%d"));
	}
	//单元格空的
	else if (vResult.vt == VT_EMPTY)
	{
		str = _T("");
	}

	return str;
}

double IllusionExcelFile::GetCellDouble(long irow, long icolumn)
{
	double rtn_value = 0;
	COleVariant vresult;
	//字符串
	if (already_preload_ == FALSE)
	{
		CRange range;
		range.AttachDispatch(excel_current_range_.get_Item(COleVariant((long)irow), COleVariant((long)icolumn)).pdispVal, true);
		vresult = range.get_Value2();
		range.ReleaseDispatch();
	}
	//如果数据依据预先加载了
	else
	{
		long read_address[2];
		VARIANT val;
		read_address[0] = irow;
		read_address[1] = icolumn;
		ole_safe_array_.GetElement(read_address, &val);
		vresult = val;
	}

	if (vresult.vt == VT_R8)
	{
		rtn_value = vresult.dblVal;
	}

	return rtn_value;
}

//VT_R8
int IllusionExcelFile::GetCellInt(long irow, long icolumn)
{
	int num;
	COleVariant vresult;

	if (already_preload_ == FALSE)
	{
		CRange range;
		range.AttachDispatch(excel_current_range_.get_Item(COleVariant((long)irow), COleVariant((long)icolumn)).pdispVal, true);
		vresult = range.get_Value2();
		range.ReleaseDispatch();
	}
	else
	{
		long read_address[2];
		VARIANT val;
		read_address[0] = irow;
		read_address[1] = icolumn;
		ole_safe_array_.GetElement(read_address, &val);
		vresult = val;
	}
	
	num = static_cast<int>(vresult.dblVal);

	return num;
}

void IllusionExcelFile::SetCellString(long irow, long icolumn, CString new_string)
{
	COleVariant new_value(new_string);
	CRange start_range = excel_work_sheet_.get_Range(COleVariant(_T("A1")), covOptional);
	CRange write_range = start_range.get_Offset(COleVariant((long)irow - 1), COleVariant((long)icolumn - 1));
	write_range.put_Value2(new_value);
	start_range.ReleaseDispatch();
	write_range.ReleaseDispatch();

}

void IllusionExcelFile::SetCellInt(long irow, long icolumn, int new_int)
{
	COleVariant new_value((long)new_int);
	CRange start_range = excel_work_sheet_.get_Range(COleVariant(_T("A1")), covOptional);
	CRange write_range = start_range.get_Offset(COleVariant((long)irow - 1), COleVariant((long)icolumn - 1));
	write_range.put_Value2(new_value);
	start_range.ReleaseDispatch();
	write_range.ReleaseDispatch();
}



void IllusionExcelFile::ShowInExcel(BOOL bShow)
{
	excel_application_.put_Visible(bShow);
	excel_application_.put_UserControl(bShow);
}

//返回打开的EXCEL文件名称
CString IllusionExcelFile::GetOpenFileName()
{
	return open_excel_file_;
}

//取得打开sheet的名称
CString IllusionExcelFile::GetLoadSheetName()
{
	return excel_work_sheet_.get_Name();
}

//取得列的名称，比如27->AA
CString& IllusionExcelFile::GetColumnName(long icolumn)
{
	//static char column_name[64];
	static CString column_name;
	int str_len = 0;

	while (icolumn > 0)
	{
		int num_data = icolumn % 26;
		icolumn /= 26;
		if (num_data == 0)
		{
			num_data = 26;
			icolumn--;
		}
		//column_name[str_len] = (char)((num_data - 1) + 'A');
		column_name.SetAt(str_len, (num_data - 1) + _T('A'));
		str_len++;
	}
	//column_name[str_len] = '\0';
	//反转
	//_strrev(column_name);
	column_name.MakeReverse();

	return column_name;
}

//预先加载
void IllusionExcelFile::PreLoadSheet()
{

	CRange used_range;

	used_range = excel_work_sheet_.get_UsedRange();


	VARIANT ret_ary = used_range.get_Value2();
	if (!(ret_ary.vt & VT_ARRAY))
	{
		return;
	}
	//
	ole_safe_array_.Clear();
	ole_safe_array_.Attach(ret_ary);
}

//CTime表示的日期上限是3000年12月31日，下限是1970年1月1日 12:00:00 AM GMT。
//%a：周的英文缩写形式。
//%A：周的英文全名形式。
//%b： 月的英文缩写形式。
//%B：月的英文全名形式。
//%c： 完整的日期和时间。
//%d：十进制形式的日期（01 - 31）。
//%H：24小时制的小时（00 - 23）。
//%I： 12小时制的小时（00 - 11）。
//%j： 十进制表示的一年中的第几天（001 - 366）。
//%m： 月的十进制表示（01 - 12）。
//%M：十进制表示的分钟（00 - 59）。
//%p： 12小时制的上下午标示（AM / PM）。
//% S： 十进制表示的秒（00 - 59）。
//%U： 一年中的第几个星期（00 - 51），星期日是一周的第一天。
//%W： 一年中的第几个星期（00 - 51），星期一是一周的第一天。
//%w： 十进制表示的星期几（0 - 6）。
//%Y： 十进制表示的年。
void IllusionExcelFile::FormatDateTime(CTime & in_ctime, CString & in_strValue, ExcelFormat in_format)
{
	//初始化CTime
	CTime timecopy = in_ctime;
	in_ctime = CTime(1970, 1, 2, 0, 0, 0);

	int days;
	CTimeSpan cts;
	//格式化Excel中的日期或时间数据
	switch (in_format)
	{
		//自1899.12.30 00:00:00 起的天数（两端均不含）
	case ExcelDate:
		days = StrToInt(in_strValue.GetString());
		cts = CTimeSpan(days - 25570, 0, 0, 0);			//减去1899.12.30到1970.1.2的天数差值
		in_ctime += cts;
		break;

		//数值*24，四舍五入取整数为小时；余下小数*60，四舍五入取整数为分钟；余下小数*60，四舍五入后为秒数
	case ExcelTime:	
		double dtime = strtod(CW2A(in_strValue.GetString()), NULL);
		int hours, minutes, seconds;

		int totals = static_cast<int>(round(dtime * 24 * 60 * 60));
		seconds = totals % 60;
		totals /= 60;
		minutes = totals % 60;
		hours = totals /= 60;

		in_ctime = CTime(timecopy.GetYear(), timecopy.GetMonth(), timecopy.GetDay(), hours, minutes, seconds);
		break;
	//case ExcelDateTime:
	//	break;
	//default:
	//	break;
	}
}
