#pragma once
#include <string>

using namespace std;

class menu {
private:
	string drinkName;	// 음료의 이름
	int makeTime;	// 음료를 만드는데 걸리는 시간
	int drinkPrice;	// 음료의 가격, 사실 현재는 쓰진 않음 나중에 영수증 같은거 구현하려면 사용
	int makeableRank; // 이 음료를 만드는데 필요한 바리스타 랭크
public:
	// 생성자
	menu() {	//  디폴트 생성자
		drinkName = "empty";
		makeTime = -1;
		drinkPrice = -1;
		makeableRank = -1;
	}
	menu(string name, int time, int price, int rank) {
		drinkName = name;
		makeTime = time;
		drinkPrice = price;
		makeableRank = rank;
	}

	// accessor
	string getDrinkName() { return drinkName; }
	int getMakeTime() { return makeTime; }
	int getDrinkPrice() { return drinkPrice; }
	int getRank() { return makeableRank; }

	// mutator
	void setMakeTime(int time) { makeTime = time; }

	// function

};


/* 이런식으로 함수 추가 구현
void menu::funcName(type param, ..) {

}
*/

