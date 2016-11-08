#include <iostream>
#include <fstream>
#include <queue>
#include "barista.h"
#include "order.h"
#include "myTime.h"
#include "loadBalancing.h"

using namespace std;

// fstream functions
void loadMenuFile(string fileName);
void loadBaristaFile(string fileName);
void loadOrderFile(string fileName);

vector<menu> men;		// 모든 메뉴 정보를 저장해둘 vector형 자료구조
vector<barista> bari;	// 모든 바리스타 정보 저장해둘 vector형 자료구조
queue<order> ord;		// 모든 주문정보를 저장해둘 queue형 자료구조

string drinkName;	// 메뉴 이름

// main 안에 깔끔하게 해서 구분하기 편하게 하기 위해 테스트 함수 따로 뺀거
void test();

int main() {

	loadMenuFile("menu.txt");
	loadBaristaFile("barista.txt");
	loadOrderFile("order.txt");
	cout << endl;

	// loadBalancing
	loadBalancing();

	// test
	test();
	
	return 0;
}

// 이거 UI 클래스라도 만들든지 해서 쉽게 변경 가능하게 할 필요 있음
// 박현준 : 나중에 지워야할 부분이라 괜찮아요
void test() {
	int i;

	for (i = 0; i < men.size(); i++)
		cout << i << "번 메뉴, 메뉴이름 :" << men[i].getDrinkName() << " 만드는 시간 :" << men[i].getMakeTime() << "초" << endl;
	cout << endl;

	for (i = 0; i < bari.size(); i++)
		cout << i << "번 바리스타, 숙련도 :" << bari[i].getRank() << endl;
	cout << endl;

	for (i = 0; i < bari.size(); i++) {
		cout << i << "번 바리스타, 주문량 : " << bari[i].getNumOfCofMade() << endl;
	}

	while (!ord.empty()) {
		cout << "주문번호 : " << ord.front().getOrderNum() << " 주문시각 : " << ord.front().getOrderTime()
			<< " 주문메뉴 :" << ord.front().getDrinkName() << " 주문수량 :" << ord.front().getNumOfDrink() << endl;
		ord.pop();
	}
	cout << endl;

	// myTime.h 관련 테스트 and 사용법
	myTime t1 = "08:30:00";
	myTime t2 = "25:62:80"; // 잘못된 데이터가 들어왔을경우 getSec()을 호출해주면 바른 데이터로 바뀐다(근데 그럴일은 없을듯..)
	cout << t1 << " " << t2 << endl;
	cout << t2.getHour() << ":" << t2.getMin() << ":" << t2.getSec() << endl;
	cout << t1 << " " << t2 << endl;
	myTime t3 = "08:30:00";
	if (t1 == t3) // 쉽게 시간이 같은지(주문시간과 진행시간) 비교 가능
		cout << "같습니다" << endl;
	cout << endl;

	
}

/****************************
메뉴에 대한 데이터를 읽어온다
****************************/
void loadMenuFile(string fileName) {

	int i;
	int numOfMenu;	// 총 메뉴의 숫자
	int makeTime, drinkPrice;	// 메뉴를 만드는데 걸리는 시간, 메뉴의 가격
	int makableRank;	// 이 메뉴를 만드는데 필요한 바리스타 랭크

	cout << fileName << " loading" << endl;
	ifstream in(fileName);
	if (in.fail()) {
		cout << fileName << " open fail" << endl;
		return;
	}

	in >> numOfMenu;
	for (i = 0; i < numOfMenu; i++) {
		in >> drinkName >> makeTime >> drinkPrice >> makableRank;
		menu temp(drinkName, makeTime, drinkPrice, makableRank);
		men.push_back(temp);
	}
	cout << fileName << " load complete" << endl;
	in.close();
}

/********************************
바리스타에 대한 데이터를 읽어온다
********************************/
void loadBaristaFile(string fileName) {

	int i, j;
	int numOfBarista;	// 총 바리스타의 숫자
	int rank;	// 바리스타의 랭크 (0 ~ 5)
		
	cout << fileName << " loading" << endl;
	ifstream in(fileName);
	if (in.fail()) {
		cout << fileName << " open fail" << endl;
		return;
	}

	in >> numOfBarista;
	for (i = 0; i < numOfBarista; i++) {
		in >> rank;
		barista temp(rank);
		bari.push_back(temp);
	}
	cout << fileName << " load complete" << endl;
	in.close();
}

/*********************************
주문에 대한 데이터를 큐에 저장한다
**********************************/
void loadOrderFile(string fileName) {

	int orderNum;		// 주문번호
	int customerNum;	// 고객번호
	string orderTime;	// 주문시간
	int numOfDrink;		// 주문수량

	cout << fileName << " loading" << endl;
	ifstream in(fileName);
	if (in.fail()) {
		cout << fileName << " open fail" << endl;
		return;
	}

	while (!in.eof()) {
		in >> orderNum >> customerNum >> orderTime >> drinkName >> numOfDrink;
		order temp(orderNum, customerNum, orderTime, drinkName, numOfDrink);
		ord.push(temp);
	}
	cout << fileName << " load complete" << endl;
	in.close();
}