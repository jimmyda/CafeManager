#pragma once
#include "myTime.h"

class barista {
private:
	int totalMade;		// 바리스타가 만든 총 커피의 수
	int numOfCofMade;	// 오늘 만든 커피의 수
	int rank;	// 바리스타의 랭크 (0 ~ 5, 변수명이 어렵고 길어서 바꿈)
	bool doing; // flag(바리스타가 음료를 만드는 중이면 true 아니면 false)
	myTime finishMakingTime;

public:
	// 생성자
	barista() {	//  디폴트 생성자
		totalMade = -1;
		numOfCofMade = -1;
		rank = -1;
		doing = false;
		finishMakingTime.setTime("06:00:00");
		// to do something
	}
	barista(int prof) {
		totalMade = 0;
		numOfCofMade = 0;
		rank = prof;
		doing = false;
	}

	// accessor
	int getNumOfCofMade() { return numOfCofMade; }
	int getRank() { return rank; }
	int getTotalMade() { return totalMade; }
	bool getDoing() { return doing; }	// 음료를 제조중인지 확인
	myTime getFinishMakingTime() { return finishMakingTime; }

	// mutator
	void setRank(int prof) { rank = prof; }
	void setFinishMakingTime(myTime t) { finishMakingTime = t; }
	void incNumOfCofMade() { numOfCofMade++; }	// numOfCofMade++
	void incNumOfCofMade(int numOfCof) { numOfCofMade += numOfCof; }

	// function
	void doWork() { doing = true; }	// 바리스타가 음료제조를 시작
	void endWork() { doing = false; }	// 바리스타가 음료제조를 완료
	int currentWork();
	void endOfDay();
};

// 하루가 끝나면 전날까지 만들었던 총 커피수에 오늘만든 커피수를 더해준다
void barista::endOfDay() {
	totalMade += numOfCofMade;
	numOfCofMade = 0;
}

int barista::currentWork() {
	return numOfCofMade;
}