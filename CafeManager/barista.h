#pragma once
#include "menu.h"

class barista {
private:
	int totalMade;		// 바리스타가 만든 총 커피의 수
	int numOfCofMade;	// 오늘 만든 커피의 수
	int rank;	// 바리스타의 랭크 (0 ~ 5, 변수명이 어렵고 길어서 바꿈)

public:
	// 생성자
	barista() {	//  디폴트 생성자
		totalMade = -1;
		numOfCofMade = -1;
		rank = -1;
		// to do something

	}
	barista(int prof) {
		totalMade = 0;
		numOfCofMade = 0;
		rank = prof;
		// to do something

	}

	// accessor
	int getNumOfCofMade() { return numOfCofMade; }
	int getRank() { return rank; }
	int getTotalMade() { return totalMade; }

	// mutator
	void setRank(int prof) { rank = prof; }
	void incNumOfCofMade() { numOfCofMade++; }	// numOfCofMade++
	void incNumOfCofMade(int numOfCof) { numOfCofMade += numOfCof; }

												// function
	// 바리스타가 선택되었을 때 
	// 바리스타 클래스내에서 바꿔주어야할 부분 work로 모아둔거
	void doWork(string drinkName, int numOfDrink); 
	int currentWork();
	void endOfDay();
};

// 하루가 끝나면 전날까지 만들었던 총 커피수에 오늘만든 커피수를 더해준다
void barista::endOfDay() {
	totalMade += numOfCofMade;
	numOfCofMade = 0;
}

/* 이런식으로 함수 추가 구현
void barista::funcName(type param, ..) {

}
*/

void barista::doWork(string drinkName, int numOfDrink) {
	//this->incNumOfCofMade(numOfDrink);
	/***************************************************
	   this 사용해주지 않아도 됩니다
	   헤더 내부에서는 헤더 내부 private 변수에 바로 접근가능합니다
	***************************************************/
	numOfCofMade += numOfDrink;
}

int barista::currentWork() {
	//return this->getNumOfCofMade();
	/***************************************************
	   이것도 마찬가지이고 이 함수는 그냥 getNumOfCofMade() 접근자와 똑같은 함수이기 때문에 삭제하시고
	   getNumOfCofMade() 사용해주세요(같은 내용 함수 이중 호출)
	***************************************************/
	return numOfCofMade;
}