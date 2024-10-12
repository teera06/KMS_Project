#pragma once
#include <random>
#include <time.h>

class CRandomHelper
{
public:
	static CRandomHelper MainRandom;

	// constrcuter destructer
	CRandomHelper();
	~CRandomHelper();

	// delete Function
	CRandomHelper(const CRandomHelper& _Other) = delete;
	CRandomHelper(CRandomHelper&& _Other) noexcept = delete;
	CRandomHelper& operator=(const CRandomHelper& _Other) = delete;
	CRandomHelper& operator=(CRandomHelper&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> RandomCreate(_Min, _Max);
		return RandomCreate(MtGen);
	}

private:
	// 메르헨트위스터 난수 알고리즘을 사용합니다.
	// 일본의 어떤 수학교수님이 만든 알고리즘
	// 이걸 사용했다 => 시간에 의해서 언제나 난수입니다.
	// seed가 시간으로 계산된다.
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));
};

