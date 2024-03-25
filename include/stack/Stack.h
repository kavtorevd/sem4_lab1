#ifndef _STACK_ 
#define _STACK_ 

#include <iostream> 

using namespace std;

template <class T>
class TStack {
protected:
	int size;
	int top;
	T* mas;
public:
	TStack(int n) {
		if (n == 0) {
			throw out_of_range("Stack can't be created with zero length");
		}
		size = n;
		top = 0;
		mas = new T[size];
	};
	TStack(TStack<T>& stack) {
		size = stack.size;
		top = stack.top;
		mas = new T[size];
		for (size_t i = 0; i < size; i++) {
			mas[i] = stack.mas[i];
		}
	}

	~TStack() {
		top = 0;
		delete[] mas;
	};

	void Push(T a) {
		if (IsFull()) {
			throw out_of_range("Stack is full");
		}
		mas[top] = a;
		top++;
	}

	void Clear() {
		top = 0;
	}

	T TopView() {
		if (IsEmpty()) {
			throw out_of_range("Stack is empty");
		}
		return mas[top - 1];
	}

	int GetSize() {
		return size;
	}
	T GetTop() {
		if (IsEmpty()) {
			throw out_of_range("Stack is empty");
		}
		top--;
		return mas[top];
	}


	bool IsFull() {
		if (top == size) {
			return true;
		}
		return false;
	}

	bool IsEmpty() {
		if (top == 0) {
			return true;
		}
		return false;
	}

	TStack& operator=(const TStack<T>& stack) {
		size = stack.size;
		top = stack.top;
		for (int i = 0; i < size; i++) {
			mas[i] = mas[i];
		}
		return *this;
	}
};

#endif