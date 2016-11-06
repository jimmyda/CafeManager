#pragma once
#include "menu.h"
#include <vector>

class barista {
private:
	int totalMade;		// 바리스타가 만든 총 커피의 수
	int numOfCofMade;	// 오늘 만든 커피의 수
	int proficiency;	// 바리스타의 숙련도 (0 ~ 5)
	int numOfMakableMenu;	// // 바리스타가 만들 수 있는 메뉴의 수
	vector<menu> makable;	// 바리스타가 만들수 있는 제조 메뉴, 이걸통해 숙련도에 따른 바리스타의 음료 제조 시간을 미리 계산해 둘수 있도록

public:
	// 생성자
	barista() {	//  디폴트 생성자
		totalMade = -1;
		numOfCofMade = -1;
		proficiency = -1;
		numOfMakableMenu = -1;
		// to do something

	}
	barista(int prof, int num) {
		totalMade = 0;
		numOfCofMade = 0;
		proficiency = prof;
		numOfMakableMenu = num;
		// to do something

	}

	// accessor
	int getNumOfCofMade() { return numOfCofMade; }
	int getProficiency() { return proficiency; }
	int getTotalMade() { return totalMade; }
	int getNumOfMakeableMenu() { return numOfMakableMenu; }

	// mutator
	void setProficiency(int prof) { proficiency = prof; }
	void incNumOfCofMade() { numOfCofMade++; }	// numOfCofMade++

												// function
	void endOfDay();
	int baristaMakeTime(string drink);	// 숙련도에 따른 바리스타의 음료 제조 시간
};


// 하루가 끝나면 전날까지 만들었던 총 커피수에 오늘만든 커피수를 더해준다
void barista::endOfDay() {
	totalMade += numOfCofMade;
	numOfCofMade = 0;
}

// 숙련도에 따른 바리스타의 음료 제조 시간
int barista::baristaMakeTime(string drink) {
	// to do something
	int makeTime = -1;


	/*
	switch (proficiency) {
	case 0:

	case 1:

	case 2:

	case 3:

	case 4:

	case 5:

	}
	*/
	return makeTime;

}

/* 이런식으로 함수 추가 구현
void barista::funcName(type param, ..) {

}
*/

