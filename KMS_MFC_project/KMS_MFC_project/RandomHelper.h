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
	// �޸���Ʈ������ ���� �˰����� ����մϴ�.
	// �Ϻ��� � ���б������� ���� �˰���
	// �̰� ����ߴ� => �ð��� ���ؼ� ������ �����Դϴ�.
	// seed�� �ð����� ���ȴ�.
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));
};

