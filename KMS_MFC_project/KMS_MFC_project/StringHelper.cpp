#include "pch.h"
#include "StringHelper.h"

CStringHelper::CStringHelper()
{
}

CStringHelper::~CStringHelper()
{
}

std::string CStringHelper::ToUpper(const std::string& View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	//CString a(Name.c_str());
	return Name;
}
