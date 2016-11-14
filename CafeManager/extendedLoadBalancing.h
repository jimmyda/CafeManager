#pragma once
#include <iostream>
using namespace std;

class Reader {
public:
	virtual void read() {
		cout << "read something" << endl;
		readData();
		readCondition();
	}
protected:
	void readData() { cout << "read something data" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class Writer {
public:
	virtual void write() {
		cout << "write something" << endl;
		writeData();
		writeResult();
	}
protected:
	void writeData() { cout << "write something Data" << endl; }
	void writeResult() { cout << "write something Result" << endl; }
};

class Computer {
public:
	virtual void compute() { cout << "compute something" << endl; }
private:

};

// Reader 종속해서 원하는데로 구현 실제 로드 밸런싱에선 Reader 받아서 read함
class ReaderSample : public Reader {
public:
	void read() {
		cout << "Reader Sample" << endl;
		readCondition();
		readData();
	}
	void readData() { cout << "Read Data Sample" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class WriterSample : public Writer {
public:
	void write() {
		cout << "Writer Sample" << endl;
		this->writeData(); // 혹은 부모꺼 써버리던지 
		this->writeResult();
	}
private:
};

class ExtendedLoadBalancing {
public:
	Reader* reader;
	Writer* writer;
	Computer* computer;
public:
	ExtendedLoadBalancing() {
		reader = new Reader;
		writer = new Writer;
		computer = new Computer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader) {
		writer = new Writer;
		computer = new Computer;
		this->reader = reader;
		init();
	}
	ExtendedLoadBalancing(Writer* writer) {
		writer = new Writer;
		computer = new Computer;
		this->writer = writer;
		init();
	}
	ExtendedLoadBalancing(Computer* computer) {
		reader = new Reader;
		writer = new Writer;
		this->computer = computer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader, Writer* writer)
	{
		computer = new Computer;
		this->reader = reader;
		this->writer = writer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader, Writer* writer, Computer* computer) {
		this->reader = reader;
		this->writer = writer;
		this->computer = computer;
		init();
	}
	~ExtendedLoadBalancing() {
		delete reader;
		delete writer;
		delete computer;
	}

	void init() {
		reader->read();
		computer->compute();
		writer->write();
	}
};

extern vector<menu> men;
extern vector<barista> bari;
extern queue<order> ord;

extern void load();
extern void test();

// Basic 단계 구현 시간 조건 없을 때 로드밸런싱 
// 이후 시간 및 다른 조건 추가에 따른 로드 밸런싱도 상속을 통해 구현 
// 원한다면 상속을 통해 확장시켜 구현할 수 있게 하기를 목표로 하고있음

class BasicReader : public Reader {
public:
	void read() {
		load();
	}
};

class BasicComputer : public Computer {
private:

public:
	void compute() {
		loadBalancing();
	}

	void loadBalancing() {
		while (!isEmptyOrder()) {
			order curOrd = selectOrder();
			for (int i = 0; i < curOrd.getNumOfDrink(); i++)
				distributeOrder(selectBarista());
		}
	}

	bool isEmptyOrder() {
		return ord.empty();
	}

	order selectOrder() {
		return ord.front();
	}

	void distributeOrder(int selected) {
		bari[selected].incNumOfCofMade();
		ord.pop();
	}

	int selectBarista() {
		int min = 1000;
		barista curBari;
		int bariId;
		for (int i = 0; i < bari.size(); i++)
			if (min > bari[i].getNumOfCofMade())
			{
				min = bari[i].getNumOfCofMade();
				curBari = bari[i];
				bariId = i;
			}
		return bariId;
	}

};

class BasicWriter : public Writer {
public:
	void write() {
		test();
	}
};