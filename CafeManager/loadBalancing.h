#pragma once

// 현재 생각하고 있는 로드 밸런싱 알고리즘
/*
# Least Connection (최소 접속 방식) 
+ 오픈 커넥션이 가장 적은 서버로 사용자 요구를 연결하는 방식 
+ 균등한 트래픽 유지하기 위해 처리 속도가 빠른 서버가 더 많은 접속을 받게 됨 
+ 서버들의 성능이 비슷하게 구성되었을 때 효과적인 트래픽 분산이 가능

CafeManager에 적용 시켜 보면
바리스타 중 가장 적은 업무를 하고 있을 때 그 바리스타에게 주문 할당
랭크가 높은 (제조할 수 있는 음료수가 많은) 바리스타가 있을 경우 더 많은 주문 할당
요구되는 메뉴가 균등하게 주문 되었을 때 or 바리스타가 처리 가능한 메뉴가 
균등하게 주문 되었을 때 효과적으로 분산 가능
*/


// main에 선언 된 거 이 파일에서 쓰려고 할 때 extern 함수는 static으로
extern vector<menu> men;
extern vector<barista> bari;
extern queue<order> ord;

priority_queue<pair <int, int> > workIndex;

//#define MAX_ORDER 10 // 바리스타 개인이 받을 수 있는 최대 주문량
/*
int searchMakeTime(string drinkName, int begin, int end) {
	int mid = (begin + end) / 2;
	if (drinkName == men[mid].getDrinkName()) {
		cout << "찾은 음료 이름 :" << drinkName << endl;
		return men[mid].getMakeTime();
	}
	else if (begin <= end){
		if (drinkName[0] == men[mid].getDrinkName()[0])
			
		else if (drinkName[0] < men[mid].getDrinkName()[0])
			searchMakeTime(drinkName, begin, mid);
		else
			searchMakeTime(drinkName, mid, end);
	}
}
*/

void selectBarista(order ord) {
	
	int numOfDrink = ord.getNumOfDrink();	// 주문 받은 수량
	int numOfBarista = bari.size();		// 총 바리스타의 수
	string drinkName = ord.getDrinkName();
	int menuIndex;

	for (int i = 0; i < men.size(); i++) {
		if (men[i].getDrinkName() == drinkName) {
			menuIndex = i;
			break;
		}
	}
//	int makeTime = searchMakeTime(drinkName, 0, men.size());

	if (numOfDrink == 1) { // 주문 받은 1개이면
	// 오름차순으로 정렬되있으므로 숙련도가 높은 barista부터 찾음(뒤부터 search)
		// 1. 바리스타랭크가 현재 음료를만들수 있는지, 가장 적게 만든사람

		int min = 1000;
		int minIndex;
		for (int i = numOfBarista - 1; i >= 0; i--) { // 바리스타 index는 0부터 이므로 numOfBarista-1
			if (bari[i].getRank() >= men[menuIndex].getRank() && bari[i].getNumOfCofMade() < min) {
				min = bari[i].getNumOfCofMade();
				minIndex = i;
			}
		}

		bari[minIndex].setFinishMakingTime(ord.getOrderTime() + men[menuIndex].getMakeTime());
		bari[minIndex].incNumOfCofMade();
		cout << "몇번 바리스타 :" << minIndex << " 완료시간:"<< bari[minIndex].getFinishMakingTime() << endl;
		workIndex.push(make_pair(minIndex, bari[minIndex].getFinishMakingTime().getTimeSec()));
		// 


		/*
		for (int i = numOfBarista - 1; i >= 0; i--) {
			if (!bari[i].getDoing()) {	// 일을 안하고 있으면
				bari[i].doWork();	// barista의 flag를 true로 바꿔줌
				//workIndex.push_back();
				break;
			}
			
		}
		*/
	}
	else {	// 주문 받은 수량이 여러개이면
		for (int i = 0; i < numOfDrink; i++) {
			int min = 1000;
			int minIndex;
			for (int i = numOfBarista - 1; i >= 0; i--) { // 바리스타 index는 0부터 이므로 numOfBarista-1
				if (bari[i].getRank() >= men[menuIndex].getRank() && bari[i].getNumOfCofMade() < min) {
					min = bari[i].getNumOfCofMade();
					minIndex = i;
				}
			}

			bari[minIndex].setFinishMakingTime(ord.getOrderTime() + men[menuIndex].getMakeTime());
			bari[minIndex].incNumOfCofMade();
			cout << "몇번 바리스타 :" << minIndex << " 완료시간:" << bari[minIndex].getFinishMakingTime() << endl;
			workIndex.push(make_pair(minIndex, bari[minIndex].getFinishMakingTime().getTimeSec()));
		}
	}
}

void findEndOrder() {
	// to do something

}

void start() {
	int totalMake = 0;	// 모든 바리스타 만든 총 음료수
	myTime curTime = "08:30:00";	// 진행 현재 시각(시간에 흐름에 따라 진행)
	
	// 큐에 잇는 주문이 다 빌 때까지
	while (!ord.empty()) {
		order curOrd = ord.front(); // 가장 앞에잇는 주문을 가져옴
		
		if (curOrd.getOrderTime() == curTime) {		// 맨 앞의 주문이 현재 시각과 같을경우
			cout << "현재시간 :" << curTime << endl;
			if (workIndex.size() == bari.size()) {
				string curDrinkName = curOrd.getDrinkName();
				int curMakeTime;
				for (int i = 0; i < men.size(); i++) {
					if (curDrinkName == men[i].getDrinkName()) {
						curMakeTime = men[i].getMakeTime();
						break;
					}
				}
				
				int bariNum = workIndex.top().first;
				int bariTime = workIndex.top().second;
				bariTime = bariTime + curMakeTime;
				workIndex.pop();
				workIndex.push(make_pair(bariNum, bariTime));
				//cout << workIndex.top().first << endl;
				//cout << workIndex.top().second << endl;
				
			}
			
			// 로드 밸런싱 알고리즘을 통해 현재 주문번호에 맞는 바리스타를 선택함
			selectBarista(curOrd);	// 현재 오더를 넘겨줌
			
			// 모든 바리스타 만든 총 음료수 update
			totalMake += curOrd.getNumOfDrink();
			//cout << "총 만든 커피수 :" << totalMake << endl;			
			// 주문 완료 큐에서 꺼냄
			ord.pop();
		}
		else {	// 맨 앞의 주문이 현재 시각과 다를 경우
			
			// 주문 완료시간(pop)
			while(!workIndex.empty() && (bari[workIndex.top().first].getFinishMakingTime() == curTime)){
				cout << "바리스타 번호 : "<< workIndex.top().first << " 종료시간 :" << curTime << endl;
				workIndex.pop();
			}

			++curTime;	// 시간을 1분 늘려줌
			

			// to do something
			// 어떤 바리스타가 제조중인 음료가 완료될 시간일 경우 바리스타의 플래그를 false로 만들어주고 제조완료 메세지 출력
			findEndOrder();
		}
		
	}
}

