#pragma once
#include <string>
#include "myTime.h"

using namespace std;

class order {
private:
	int orderNum;		// 주문번호
	int customerNum;	// 고객번호
	myTime orderTime;	// 주문시간
	string drinkName;	// 음료이름
	int numOfDrink;		// 주문수량
public:
	// 생성자
	order() {	//  디폴트 생성자
		orderNum = -1;
		customerNum = -1;
		orderTime.setTime("00:00:00");
		drinkName = "empty";
		numOfDrink = -1;
	}
	order(int order, int customer, string time, string name, int num) {
		orderNum = order;
		customerNum = customer;
		orderTime.setTime(time);
		drinkName = name;
		numOfDrink = num;
	}

	// accessor
	int getOrderNum() { return orderNum; }
	int getCustomerNum() { return customerNum; }
	myTime getOrderTime() { return orderTime; }
	string getDrinkName() { return drinkName; }
	int getNumOfDrink() { return numOfDrink; }

	// 주문이 들어온 시,분,초에 접근가능
	int getHour() { return orderTime.getHour(); }
	int getMin() { return orderTime.getMin(); }
	int getSec() { return orderTime.getSec(); }

	// mutator


	// function
	// 시간의 비교연산은 myTime.h로 구현 예정
	
};


/* 이런식으로 함수 추가 구현
void order::funcName(type param..) {

}
*/