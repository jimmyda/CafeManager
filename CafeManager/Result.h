#pragma once
#include <iostream>

using namespace std;

/*
결과물을 출력하는 result Observer에서 사용하는 클래스.
결과물에 담길 정보들을 나타낸다.
*/

class Result
{
public:
	int order;
	int baristaId;

	Result(int tmp_order, int tmp_baristaId)
	{
		order = tmp_order;
		baristaId = tmp_baristaId;
	}

};