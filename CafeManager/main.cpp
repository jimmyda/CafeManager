#include <iostream>
#include <fstream>
#include <queue>
#include "barista.h"
#include "order.h"

using namespace std;

vector<menu> men;		// 모든 메뉴 정보를 저장해둘 vector형 자료구조
vector<barista> bari;	// 모든 바리스타 정보 저장해둘 vector형 자료구조
queue<order> ord;		// 모든 주문정보를 저장해둘 queue형 자료구조

int main() {

	int i, j;
	int numOfMenu;	// 총 메뉴의 숫자
	int numOfBarista;	// 총 바리스타의 숫자
	string drinkName;	// 메뉴 이름
	int makeTime, drinkPrice;	// 메뉴를 만드는데 걸리는 시간, 메뉴의 가격
	int numOfMakableMenu;	// 바리스타가 만들 수 있는 메뉴의 수
	int proficiency;	// 바리스타의 숙련도 (0 ~ 5)
	int orderNum;		// 주문번호
	int customerNum;	// 고객번호
	string orderTime;	// 주문시간
	int numOfDrink;		// 주문수량

						/****************************
						메뉴에 대한 데이터를 받는다
						****************************/
	cout << "메뉴 데이터를 읽어옵니다." << endl;
	ifstream in("menu.txt");
	if (in.fail()) {
		cout << "menu file open fail" << endl;
		return 1;
	}

	in >> numOfMenu;
	for (i = 0; i < numOfMenu; i++) {
		in >> drinkName >> makeTime >> drinkPrice;
		menu temp(drinkName, makeTime, drinkPrice);
		men.push_back(temp);
	}
	cout << "메뉴 데이터 로딩 완료." << endl;
	in.close();

	/******************************
	바리스타에 대한 데이터를 받는다
	******************************/
	cout << "바리스타 데이터를 읽어옵니다." << endl;
	in.open("barista.txt");
	if (in.fail()) {
		cout << "barista file open fail" << endl;
		return 1;
	}

	in >> numOfBarista;
	for (i = 0; i < numOfBarista; i++) {
		in >> proficiency >> numOfMakableMenu;
		barista temp(proficiency, numOfMakableMenu);
		bari.push_back(temp);
		for (j = 0; j < numOfMakableMenu; j++) {
			in >> drinkName;
			// To do something  
			// 받은 음료 정보를 barista.h의 vector형 makable에 추가 저장하려고 생각중
		}

	}
	cout << "바리스타 데이터를 로딩 완료." << endl;
	in.close();

	/*********************************
	주문에 대한 데이터를 큐에 저장한다
	**********************************/
	cout << "주문 데이터를 큐로 읽어옵니다." << endl;
	in.open("order.txt");
	if (in.fail()) {
		cout << "order file open fail" << endl;
		return 1;
	}

	while (!in.eof()) {
		in >> orderNum >> customerNum >> orderTime >> drinkName >> numOfDrink;
		order temp(orderNum, customerNum, orderTime, drinkName, numOfDrink);
		ord.push(temp);
	}
	cout << "주문 데이터를 큐에 로딩 완료." << endl;
	in.close();

	// test
	for (i = 0; i < numOfMenu; i++)
		cout << i << "번 메뉴, 메뉴이름 :" << men[i].getDrinkName() << " 만드는 시간 :" << men[i].getMakeTime() << "초" << endl;
	cout << endl;

	for (i = 0; i < numOfBarista; i++)
		cout << i << "번 바리스타, 숙련도 :" << bari[i].getProficiency() << " 만들수 있는 메뉴 종류 :" << bari[i].getNumOfMakeableMenu() << endl;
	cout << endl;

	while (!ord.empty()) {
		cout << "주문번호 : " << ord.front().getOrderNum() << " 주문시각 : " << ord.front().getOrderTime()
			<< " 주문메뉴 :" << ord.front().getDrinkName() << " 주문수량 :" << ord.front().getNumOfDrink() << endl;
		ord.pop();
	}
	cout << endl;

	return 1;
}