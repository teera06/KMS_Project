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
	// �޸���Ʈ������ ���� �˰����� ����մϴ�.
	// �Ϻ��� � ���б������� ���� �˰���
	// �̰� ����ߴ� => �ð��� ���ؼ� ������ �����Դϴ�.
	// seed�� �ð����� ���ȴ�.
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));
};

