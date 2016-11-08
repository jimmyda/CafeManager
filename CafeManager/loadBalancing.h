#pragma once

// 현재 생각하고 있는 로드 밸런싱 알고리즘
/*
# Least Connection (최소 접속 방식) 
+ 오픈 커넥션이 가장 적은 서버로 사용자 요구를 연결하는 방식 
+ 균등한 트래픽 유지하기 위해 처리 속도가 빠른 서버가 더 많은 접속을 받게 됨 
+ 서버들의 성능이 비슷하게 구성되었을 때 효과적인 트래픽 분산이 가능

CafeManager에 적용 시켜 보면
바리스타 중 가장 적은 업무를 하고 있을 때 그 바리스타에게 주문 할당
숙련도가 높은 (제조 시간이 낮은) 바리스타가 있을 경우 더 많은 주문 할당
요구되는 메뉴가 균등하게 주문 되었을 때 or 바리스타가 처리 가능한 메뉴가 
균등하게 주문 되었을 때 효과적으로 분산 가능
*/


// main에 선언 된 거 이 파일에서 쓰려고 할 때 extern 함수는 static으로
extern vector<menu> men;
extern vector<barista> bari;
extern queue<order> ord;

#define MAX_ORDER 10 // 바리스타 개인이 받을 수 있는 최대 주문량

int selectBarista(order ord) {
	// 어떤식으로 들어올지 모르니 우선은 만든 커피 수가 올꺼라 가정
	// 초기값은 최대값으로 설정
	int least = MAX_ORDER + 1;
	int id;

	// 현재 그냥 바리스타 주문 적은 애한테 분배하는 식

	for (int i = 0; i < bari.size(); i++) {
		// 가장 현재 주문량이 적은 바리스타를 찾기 위해 loop로 업무량 확인
		if (least > bari[i].currentWork()) {
			least = bari[i].currentWork();
			id = i; // 해당 바리스타에 index를 저장 혹은 바리스타 자체를 찾을 수도 잇음
		}
	}

	return id;
}

void loadBalancing() {
	// 큐에 잇는 주문이 다 빌 때까지
	while (!ord.empty()) {
		// 가장 앞에잇는 주문을 가져옴
		order curOrd = ord.front();
		// 배열에 담긴 바리스타의 아이디(인덱스)
		int baristaId;
		// 로드 밸런싱 알고리즘을 통해 현재 주문번호에 맞는 바리스타를 선택함
		baristaId = selectBarista(curOrd);
		// 바리스타 클래스내에서 doWork()를 통해 수행한 변경사항 변경
		// 선택된 바리스타에게 주문 할당
		bari[baristaId].doWork(curOrd.getDrinkName(), curOrd.getNumOfDrink());
		// 주문 완료 큐에서 꺼냄
		ord.pop();
	}
}

