#pragma once
class CPathHelper
{
public:
	CPathHelper();
	~CPathHelper();

	void MoveToSearchChild(const CString& _path);

	void test()
	{
		AfxMessageBox(Path);
	}

private:
	CString Path;
};

