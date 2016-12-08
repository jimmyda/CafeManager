#pragma once
#include <string>
#include "myTime.h"

using namespace std;

class order {
private:
	int orderNum;		// �ֹ���ȣ
	int customerNum;	// ����ȣ
	myTime orderTime;	// �ֹ��ð�
	string drinkName;	// �����̸�
	int numOfDrink;		// �ֹ�����
public:
	// ������
	order() {	//  ����Ʈ ������
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

	// �ֹ��� ���� ��,��,�ʿ� ���ٰ���
	int getHour() { return orderTime.getHour(); }
	int getMin() { return orderTime.getMin(); }
	int getSec() { return orderTime.getSec(); }
};
