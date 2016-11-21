#pragma once
#include <iostream>
#include <queue>
#include "Result.h"

using namespace std;

/*
로드 밸런싱 알고리즘에 의해 주문이 바리스타에게 접수 될 때마다 기록하고
결과를 출력하는 클래스
*/

class resultObserver
{
public :
	vector<Result> results;		//결과물들을 담는 자료구조
	int numOfOrders;			//통계를 내기 위한 전체 주문 수

	resultObserver(int size)
	{
		numOfOrders = size;
	}

	void insertResult(int order, int baristaId)
	{
		Result result(order, baristaId);
		results.push_back(result);
	}

	void showResult()
	{
		cout << "로드 밸런싱 결과" << endl;

		for (int i = 0; i < results.size(); i++)
		{
			cout << "주문 번호 : " << results.at(i).order << "는 바리스타 " << results.at(i).baristaId << "에게 접수되었습니다." << endl;
		}



	}
};