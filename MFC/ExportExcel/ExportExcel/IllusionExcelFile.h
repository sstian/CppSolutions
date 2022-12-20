/*
	2018.09.21 12:00
	OLE��ʽ��дExcel��
OLE��дEXCEL�Ƚ�����Ӧ�þ�������OLE�Ĵ��������߲�ȡԤ���أ�һ�μ������еĶ�ȡ���ݡ�
����MFCӦ�ó���->����->����ࣺ���Ϳ��е�MFC��->�ӿڣ�_Application, _Workbook, _Worksheet, Workbooks, Worksheets, Range

ʹ��ע�⣺���ļ�OpenExcelFile()������Excel�ļ�Ҫ���ڵ�ǰ·����Ϊ�û��ļ����µ�DocumentsĿ¼���磺C:\Users\Snow\Documents
*/

#pragma once

//OLE��ͷ�ļ� IllusionExcelFile.h
#include "CApplication.h"  
#include "CRange.h"
#include "CWorkbook.h"  
#include "CWorkbooks.h"  
#include "CWorksheet.h"  
#include "CWorksheets.h"  

/// Excel���ݸ�ʽ��������ں�ʱ�����ݸ�ʽ
enum ExcelFormat
{
	ExcelDate = 0x01,
	ExcelTime = 0x02,
	ExcelDateTime = ExcelDate | ExcelTime
};

///����OLE��ʽ��EXCEL��д
class IllusionExcelFile
{
public:

	//���캯������������
	IllusionExcelFile();
	virtual ~IllusionExcelFile();

protected:
	///�򿪵�Excel�ļ�����
	CString  open_excel_file_;

	///Excel BOOK���ϣ�����ļ�ʱ��
	CWorkbooks    excel_books_;
	///��ǰʹ�õ�BOOK����ǰ������ļ�
	CWorkbook     excel_work_book_;
	///Excel��sheets����
	CWorksheets   excel_sheets_;
	///��ǰʹ��sheet
	CWorksheet    excel_work_sheet_;
	///��ǰ�Ĳ�������
	CRange        excel_current_range_;

	///�Ƿ��Ѿ�Ԥ������ĳ��sheet������
	BOOL          already_preload_;
	///Create the SAFEARRAY from the VARIANT ret.
	COleSafeArray ole_safe_array_;

protected:
	///Excel�Ľ���ʵ��
	static CApplication excel_application_;

public:
	///��ʾ��Excel��
	void ShowInExcel(BOOL bShow);

	///���һ��CELL�Ƿ����ַ���
	BOOL    IsCellString(long iRow, long iColumn);
	///���һ��CELL�Ƿ�����ֵ
	BOOL    IsCellInt(long iRow, long iColumn);

	///�õ�һ��CELL��String
	CString GetCellString(long iRow, long iColumn);
	///�õ�����
	int     GetCellInt(long iRow, long iColumn);
	///�õ�double������
	double  GetCellDouble(long iRow, long iColumn);

	///ȡ���е�����
	int GetRowCount();
	///ȡ���е�����
	int GetColumnCount();

	///ͨ������ʹ��ĳ��sheet
	BOOL LoadSheet(long table_index, BOOL pre_load = FALSE);
	///ͨ������ʹ��ĳ��sheet��
	BOOL LoadSheet(const CString& sheet, BOOL pre_load = FALSE);
	///ͨ�����ȡ��ĳ��Sheet������
	CString GetSheetName(long table_index);

	///�õ�Sheet������
	int GetSheetCount();

	///���ļ�������Excel�ļ�Ҫ���ڵ�ǰ·����Ϊ�û��ļ����µ�DocumentsĿ¼���磺C:\Users\Snow\Documents
	BOOL OpenExcelFile(const CString& file_name);
	///�رմ򿪵�Excel�ļ�����ʱ���EXCEL�ļ���Ҫ
	void CloseExcelFile(BOOL if_save = FALSE);
	//���Ϊһ��Excwl�ļ�
	void SaveasXSLFile(const CString& xls_file);
	///ȡ�ô��ļ�������
	CString GetOpenFileName();
	///ȡ�ô�sheet������
	CString GetLoadSheetName();

	///д��һ��CELLһ��int
	void SetCellInt(long irow, long icolumn, int new_int);
	///д��һ��CELLһ��string
	void SetCellString(long irow, long icolumn, CString new_string);

public:
	///��ʼ��EXCEL OLE
	static BOOL InitExcel();
	///�ͷ�EXCEL�� OLE
	static void ReleaseExcel();
	///ȡ���е����ƣ�����27->AA
	static CString& GetColumnName(long iColumn);

protected:
	//Ԥ�ȼ���
	void PreLoadSheet();

public:
	//Excel���ڻ�ʱ���ʽ����ת��
	static void FormatDateTime(CTime& in_ctime, CString& in_strValue, ExcelFormat in_format);
};
