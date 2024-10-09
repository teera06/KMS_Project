#include "pch.h"
#include "StringHelper.h"

UStringHelper::UStringHelper()
{
}

UStringHelper::~UStringHelper()
{
}

std::string UStringHelper::ToUpper(const std::string& View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}
