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
