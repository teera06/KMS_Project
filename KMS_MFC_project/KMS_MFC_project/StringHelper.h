#pragma once

#include <string>

class CStringHelper
{
public:
	// constrcuter destructer
	CStringHelper();
	~CStringHelper();

	// delete Function
	CStringHelper(const CStringHelper& _Other) = delete;
	CStringHelper(CStringHelper&& _Other) noexcept = delete;
	CStringHelper& operator=(const CStringHelper& _Other) = delete;
	CStringHelper& operator=(CStringHelper&& _Other) noexcept = delete;

	static std::string ToUpper(const std::string& View);
};

