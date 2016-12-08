#pragma once
#include <string>

using namespace std;

class menu {
private:
	string drinkName;	// ������ �̸�
	int makeTime;	// ���Ḧ ����µ� �ɸ��� �ð�
	int drinkPrice;	// ������ ����, ��� ����� ���� ���� ���߿� ������ ������ �����Ϸ��� ���
	int makeableRank; // �� ���Ḧ ����µ� �ʿ��� �ٸ���Ÿ ��ũ
public:
	// ������
	menu() {	//  ����Ʈ ������
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
};
