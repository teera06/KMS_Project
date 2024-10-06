#pragma once

#include <string>
#include <string_view>

class UStringHelper
{
public:
	// constrcuter destructer
	UStringHelper();
	~UStringHelper();

	// delete Function
	UStringHelper(const UStringHelper& _Other) = delete;
	UStringHelper(UStringHelper&& _Other) noexcept = delete;
	UStringHelper& operator=(const UStringHelper& _Other) = delete;
	UStringHelper& operator=(UStringHelper&& _Other) noexcept = delete;

	static std::string ToUpper(std::string& View);
};

