#pragma once
#include <string>

using namespace std;

class order {
private:
	int orderNum;		// 주문번호
	int customerNum;	// 고객번호
	string orderTime;	// 주문시간
	string drinkName;	// 음료이름
	int numOfDrink;		// 주문수량
public:
	// 생성자
	order() {	//  디폴트 생성자
		orderNum = -1;
		customerNum = -1;
		orderTime = "empty";
		drinkName = "empty";
		numOfDrink = -1;
	}
	order(int order, int customer, string time, string name, int num) {
		orderNum = order;
		customerNum = customer;
		orderTime = time;
		drinkName = name;
		numOfDrink = num;
	}

	// accessor
	int getOrderNum() { return orderNum; }
	int getCustomerNum() { return customerNum; }
	string getOrderTime() { return orderTime; }
	string getDrinkName() { return drinkName; }
	int getNumOfDrink() { return numOfDrink; }

	// mutator


	// function
	// 주문시간은 HH:MM:SS string type 으로 받아진다
	int getOrderTimeHour();		// 시간을 return
								//int getOrderTimeMin();	// 분을 return
								//int getOrderTimeSec();	// 초를 return
};


// 시간을 return
int order::getOrderTimeHour() {
	//to do something
	int hour = -1;

	return hour;
}


/* 이런식으로 함수 추가 구현
void order::funcName(type param..) {

}
*/