
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "defs.h"

using namespace std;

template<class T>
class Array {
	template<class V>
	friend ostream& operator<<(ostream&, const Array<V>&);

	public:
		//constructor
		Array();
				
		//destructor
		~Array();
		
		//others
		Array<T>& operator+=(const T&);
		Array<T>& operator-=(const T&);
		T& operator[](int index);
		const T& operator[](int index) const;
		int getSize() const;
		bool isFull() const;
		void clear();
	
	private:
		int size;
		T* elements;
	
};

//constructor
template<class T>
Array<T>::Array(){
	elements = new T[MAX_ARRAY];
	size = 0;
}

//destructor
template<class T>
Array<T>::~Array(){
	delete [] elements;
}

//Overload the += operator to add an element to Array, add to the back of the array
template<class T>
Array<T>& Array<T>::operator+=(const T& t) {
	if (isFull()) {
		return *this;
	}  
	elements[size++] = t;
	return *this;
}

//Overload the += operator to remove an element to Array
template<class T>
Array<T>& Array<T>::operator-=(const T& t) {
	for (int i = 0; i < size; ++i) {
		if (elements[i] == t) {
			for (int j = i; j < size-1; ++j) {
				elements[j] = elements[j+1];
			}
			elements[size-1] = NULL;
			size--;
		}
	}
	return *this;
}

template<class T>
int Array<T>::getSize() const {
	return size;
}

template<class T>
bool Array<T>::isFull() const {
	return size >= MAX_ARRAY;
}

template<class T>
T& Array<T>::operator[](int index) {
	if (index < 0 || index >= size) {
		cerr<<"Array index out of bounds"<<endl;
		exit(1);
	}
	return elements[index];
}

template<class T>
const T& Array<T>::operator[](int index) const{
	if (index < 0 || index >= size) {
		cerr<<"Array index out of bounds"<<endl;
		exit(1);
	}
	return elements[index];
}

//clear the array
template<class T>
void Array<T>::clear() {
	while (size > 0) {
		*this-=elements[size - 1];
	}
}

//writes to ostream all of the contained elements
template <class T>
ostream& operator<<(ostream& out, const Array<T>& arr) {
	for (int i = 0; i < arr.getSize(); ++i) {
		out << arr.elements[i] << endl;
	}
	return out;
}

#endif