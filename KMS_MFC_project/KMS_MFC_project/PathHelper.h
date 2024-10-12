#pragma once
class CPathHelper
{
public:
	CPathHelper();
	~CPathHelper();

	void MoveToSearchChild(const CString& _path);

	void Move(const CString& _path);

	CString GetCurPath() 
	{
		return Path;
	}

	void test()
	{
		AfxMessageBox(Path);
	}

private:
	CString Path;
};

