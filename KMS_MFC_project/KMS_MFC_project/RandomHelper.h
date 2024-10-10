#pragma once
#include <random>
#include <time.h>

class RandomHelper
{
public:
	static RandomHelper MainRandom;

	// constrcuter destructer
	RandomHelper();
	~RandomHelper();

	// delete Function
	RandomHelper(const RandomHelper& _Other) = delete;
	RandomHelper(RandomHelper&& _Other) noexcept = delete;
	RandomHelper& operator=(const RandomHelper& _Other) = delete;
	RandomHelper& operator=(RandomHelper&& _Other) noexcept = delete;

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

