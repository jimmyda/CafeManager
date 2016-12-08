#pragma once

// �ε� �뷱�� �˰���
/*
# Least Connection (�ּ� ���� ���) 
+ ���� Ŀ�ؼ��� ���� ���� ������ ����� �䱸�� �����ϴ� ��� 
+ �յ��� Ʈ���� �����ϱ� ���� ó�� �ӵ��� ���� ������ �� ���� ������ �ް� �� 
+ �������� ������ ����ϰ� �����Ǿ��� �� ȿ������ Ʈ���� �л��� ����

CafeManager�� ���� ���� ����
�ٸ���Ÿ �� ���� ���� ������ �ϰ� ���� �� �� �ٸ���Ÿ���� �ֹ� �Ҵ�
��ũ�� ���� (������ �� �ִ� ������� ����) �ٸ���Ÿ�� ���� ��� �� ���� �ֹ� �Ҵ�
�䱸�Ǵ� �޴��� �յ��ϰ� �ֹ� �Ǿ��� �� or �ٸ���Ÿ�� ó�� ������ �޴��� 
�յ��ϰ� �ֹ� �Ǿ��� �� ȿ�������� �л� ����
*/


// main�� ���� �� �� �� ���Ͽ��� ������ �� �� extern �Լ��� static����
extern vector<menu> men;
extern vector<barista> bari;
extern queue<order> ord;

priority_queue<pair <int, int> > workIndex;

void selectBarista(order ord) {
	
	int numOfDrink = ord.getNumOfDrink();	// �ֹ� ���� ����
	int numOfBarista = bari.size();		// �� �ٸ���Ÿ�� ��
	string drinkName = ord.getDrinkName();
	int menuIndex;

	for (int i = 0; i < men.size(); i++) {
		if (men[i].getDrinkName() == drinkName) {
			menuIndex = i;
			break;
		}
	}

	if (numOfDrink == 1) { // �ֹ� ���� 1���̸�
	// ������������ ���ĵ������Ƿ� ���õ��� ���� barista���� ã��(�ں��� search)
		// 1. �ٸ���Ÿ��ũ�� ���� ���Ḧ����� �ִ���, ���� ���� ������
		int min = 1000;
		int minIndex;
		for (int i = numOfBarista - 1; i >= 0; i--) { // �ٸ���Ÿ index�� 0���� �̹Ƿ� numOfBarista-1
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
		cout << "�ֹ�: " << men[menuIndex].getDrinkName() << endl;
		cout << "�䱸 Rank: " << men[menuIndex].getRank() << endl;
		cout << minIndex << " �� �ٸ���Ÿ" << " �Ϸ�ð�:" << bari[minIndex].getFinishMakingTime() << endl;
		cout << endl;
		workIndex.push(make_pair(minIndex, bari[minIndex].getFinishMakingTime().getTimeSec()));
		bari[minIndex].doWork();
	}
	else {	// �ֹ� ���� ������ �������̸�
		for (int i = 0; i < numOfDrink; i++) {
			int min = 1000;
			int minIndex;
			for (int i = numOfBarista - 1; i >= 0; i--) { // �ٸ���Ÿ index�� 0���� �̹Ƿ� numOfBarista-1
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
			cout << "�ֹ�: " << men[menuIndex].getDrinkName() << endl;
			cout << "�䱸 Rank: " << men[menuIndex].getRank() << endl;
			cout << minIndex << " �� �ٸ���Ÿ" << " �Ϸ�ð�:" << bari[minIndex].getFinishMakingTime() << endl;
			cout << endl;
			workIndex.push(make_pair(minIndex, bari[minIndex].getFinishMakingTime().getTimeSec()));
			bari[minIndex].doWork();
		}
	}
}

void start() {
	int totalMake = 0;	// ��� �ٸ���Ÿ ���� �� �����
	myTime curTime = "08:30:00";	// ���� ���� �ð�(�ð��� �帧�� ���� ����)
	int barinumber;
	
	// ť�� �մ� �ֹ��� �� �� ������
	while (!ord.empty()) {
		order curOrd = ord.front(); // ���� �տ��մ� �ֹ��� ������
		
		if (curOrd.getOrderTime() == curTime) {		// �� ���� �ֹ��� ���� �ð��� �������
			cout << "����ð� :" << curTime << endl;
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
				// prirority_queue���� ���������� �ٸ���Ÿ ã�� loop
				priority_queue< pair<int, int> > tempQ;
				while (true) {
					bariNum = workIndex.top().first;
					barinumber = bariNum;
					bariTime = workIndex.top().second;
					// �ٸ���Ÿ�� �ش� �ֹ��� ���� �������� ���ϸ� tempQ�� ����
					if (bari[bariNum].getRank() < curRank) {
						tempQ.push(make_pair(bariNum, bariTime));
						tempQ.pop();
					}
					// ã���� break
					else
						break;
				}
				// ���� �ξ��� �ٸ���Ÿ�� �ٽ� priority_queue�� �ִ°�
				while (!tempQ.empty()) {
					workIndex.push(make_pair(tempQ.top().first, tempQ.top().second));
					tempQ.pop();
				}

				bariTime = bariTime + curMakeTime;
				workIndex.pop();
				workIndex.push(make_pair(bariNum, bariTime));	
			}
			
			// �ε� �뷱�� �˰����� ���� ���� �ֹ���ȣ�� �´� �ٸ���Ÿ�� ������
			selectBarista(curOrd);	// ���� ������ �Ѱ���
			
			// ��� �ٸ���Ÿ ���� �� ����� update
			totalMake += curOrd.getNumOfDrink();
			//cout << "�� ���� Ŀ�Ǽ� :" << totalMake << endl;			
			// �ֹ� �Ϸ� ť���� ����
			ord.pop();
		}
		else {	// �� ���� �ֹ��� ���� �ð��� �ٸ� ���
			
			// �ֹ� �Ϸ�ð�(pop)
			while(!workIndex.empty() && (bari[workIndex.top().first].getFinishMakingTime() == curTime)){
				cout << "�ٸ���Ÿ ��ȣ : "<< workIndex.top().first << " ����ð� :" << curTime << endl;
				bari[workIndex.top().first].endWork();
				workIndex.pop();
			}
			++curTime;	// �ð��� 1�� �÷���
		}
	}
	cout << endl;
	cout << "<�ε�뷱�� ���>" << endl;
	for (int i = 0; i <= barinumber; i++)
	{
		cout << i << "�� �ٸ���Ÿ(Rank " << bari[i].getRank() << ", " << bari[i].getNumOfCofMade() << "�� ����): " << "[";
		for (int j = 0; j < ((double)bari[i].getNumOfCofMade() / totalMake) * 10.0; j++)
			cout << "*";
		for (int k = 10; k >((double)bari[i].getNumOfCofMade() / totalMake) * 10.0; k--)
			cout << " ";
		cout << "]" << endl;
	}
}
