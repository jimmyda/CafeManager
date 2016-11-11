#pragma once
#include <iostream>
using namespace std;

class Reader {
public:
	virtual void read() { cout << "read something" << endl;
		readData();
		readCondition();
	}
protected:
	void readData() { cout << "read something data" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class Writer {
public:
	void write() { cout << "write something" << endl;
		writeData();
		writeResult();
	}
protected:
	void writeData() { cout << "write something Data" << endl; }
	void writeResult() { cout << "write something Result" << endl; }
};

class Computer {
public:
	void compute() { cout << "compute something" << endl; }
private:

};

// Reader 종속해서 원하는데로 구현 실제 로드 밸런싱에선 Reader 받아서 read함
class ReaderSample : virtual public Reader {
public:
	void read() { cout << "실제 read할꺼 넣으셔서 오버라이드" << endl; 
	readCondition();
	readData();
	}
	void readData() { cout << "가능하면 이런식으로 받을 수 있으면 또는 vector를 받던지" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class WriterSample : public Writer {
public:
	void write() {
		cout << "LoadBalancing에선 그냥 이거 쓸꺼" << endl;
		this->writeData(); // 혹은 부모꺼 써버리던지 
		this->writeResult();
	}
private:
};

class LoadBalancing {
public:
	Reader* reader;
	Writer* writer;
	Computer* computer;
public:
	LoadBalancing() {
		reader = new Reader;
		writer = new Writer;
		computer = new Computer;
		init();
	}
	LoadBalancing(Reader* reader) {
		this->reader = reader;
		init();
	}
	LoadBalancing(Writer* writer) {
		this->writer = writer;
		init();
	}
	LoadBalancing(Computer* computer) {
		this->computer = computer;
		init();
	}
	LoadBalancing(Reader* reader, Writer* writer)
	{
		this->reader = reader;
		this->writer = writer;
		init();
	}
	LoadBalancing(Reader* reader, Writer* writer, Computer* computer) {
		this->reader = reader;
		this->writer = writer;
		this->computer = computer;
		init();
	}

	void init() {
		reader->read();
		computer->compute();
		writer->write();
	}
};
