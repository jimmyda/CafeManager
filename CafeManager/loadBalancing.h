#pragma once

// 로드 밸런싱 알고리즘
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
		
		if (bari[minIndex].getDoing()) {
			bari[minIndex].setFinishMakingTime(bari[minIndex].getFinishMakingTime() + men[menuIndex].getMakeTime());

		}
		else {
			bari[minIndex].setFinishMakingTime(ord.getOrderTime() + men[menuIndex].getMakeTime());
		}
		bari[minIndex].incNumOfCofMade();
		cout << "주문: " << men[menuIndex].getDrinkName() << endl;
		cout << "요구 Rank: " << men[menuIndex].getRank() << endl;
		cout << "몇번 바리스타 :" << minIndex << " 완료시간:"<< bari[minIndex].getFinishMakingTime() << endl;
		cout << endl;
		workIndex.push(make_pair(minIndex, bari[minIndex].getFinishMakingTime().getTimeSec()));
		bari[minIndex].doWork();
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

			if (bari[minIndex].getDoing()) {
				bari[minIndex].setFinishMakingTime(bari[minIndex].getFinishMakingTime() + men[menuIndex].getMakeTime());
				
			}
			else {
				bari[minIndex].setFinishMakingTime(ord.getOrderTime() + men[menuIndex].getMakeTime());
			}
			bari[minIndex].incNumOfCofMade();
			cout << "주문: " << men[menuIndex].getDrinkName() << endl;
			cout << "요구 Rank: " << men[menuIndex].getRank() << endl;
			cout << "몇번 바리스타 :" << minIndex << " 완료시간:" << bari[minIndex].getFinishMakingTime() << endl;
			cout << endl;
			workIndex.push(make_pair(minIndex, bari[minIndex].getFinishMakingTime().getTimeSec()));
			bari[minIndex].doWork();
		}
	}
}

void start() {
	int totalMake = 0;	// 모든 바리스타 만든 총 음료수
	myTime curTime = "08:30:00";	// 진행 현재 시각(시간에 흐름에 따라 진행)
	int barinumber;
	
	// 큐에 잇는 주문이 다 빌 때까지
	while (!ord.empty()) {
		order curOrd = ord.front(); // 가장 앞에잇는 주문을 가져옴
		
		if (curOrd.getOrderTime() == curTime) {		// 맨 앞의 주문이 현재 시각과 같을경우
			cout << "현재시간 :" << curTime << endl;
			if (workIndex.size() == bari.size()) {
				string curDrinkName = curOrd.getDrinkName();
				int curMakeTime;
				int curRank;
				for (int i = 0; i < men.size(); i++) {
					if (curDrinkName == men[i].getDrinkName()) {
						curMakeTime = men[i].getMakeTime();
						curRank = men[i].getRank();
						break;
					}
				}
				
				int bariNum;
				int bariTime;
				// prirority_queue에서 제조가능한 바리스타 찾는 loop
				priority_queue< pair<int, int> > tempQ;
				while (true) {
					bariNum = workIndex.top().first;
					barinumber = bariNum;
					bariTime = workIndex.top().second;
					// 바리스타가 해당 주문을 제조 가능하지 못하면 tempQ에 빼둠
					if (bari[bariNum].getRank() < curRank) {
						tempQ.push(make_pair(bariNum, bariTime));
						tempQ.pop();
					}
					// 찾으면 break
					else
						break;
				}
				// 꺼내 두었던 바리스타들 다시 priority_queue에 넣는거
				while (!tempQ.empty()) {
					workIndex.push(make_pair(tempQ.top().first, tempQ.top().second));
					tempQ.pop();
				}

				bariTime = bariTime + curMakeTime;
				workIndex.pop();
				workIndex.push(make_pair(bariNum, bariTime));	
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
				bari[workIndex.top().first].endWork();
				workIndex.pop();
			}
			++curTime;	// 시간을 1분 늘려줌
		}
	}
	cout << endl;
	cout << "<로드밸런싱 결과>" << endl;
	for (int i = 0; i <= barinumber; i++)
	{
		cout << i << "번 바리스타(Rank " << bari[i].getRank() << ", " << bari[i].getNumOfCofMade() << "개 제작): " << "[";
		for (int j = 0; j < ((double)bari[i].getNumOfCofMade() / totalMake) * 10.0; j++)
			cout << "*";
		for (int k = 10; k >((double)bari[i].getNumOfCofMade() / totalMake) * 10.0; k--)
			cout << " ";
		cout << "]" << endl;
	}
}
