#include "pch.h"
#include "PathHelper.h"


CPathHelper::CPathHelper()
{
	TCHAR CurPath[100];
	GetModuleFileName(nullptr, CurPath, 100);
	Path = CurPath;
	Path = Path.Left(Path.ReverseFind('\\'));
}

CPathHelper::~CPathHelper()
{
}

void CPathHelper::MoveToSearchChild(const CString& _path)
{
	while (true)
	{
		int StrLen = Path.GetLength() - _path.GetLength();

		if (StrLen <= 0)
		{
			AfxMessageBox(_T("(찾을려는 경로가 없습니다.)"));
			break;
		}
		CString CurDirectory =Path.Mid(StrLen);

		if (_path == CurDirectory)
		{
			break;
		}
		else
		{
			Path = Path.Left(Path.ReverseFind('\\'));
		}
	}
}

void CPathHelper::Move(const CString& _path)
{
	Path += "\\";
	Path += _path;
}
