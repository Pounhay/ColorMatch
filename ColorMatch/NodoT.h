#pragma once
#include <iostream>
template<class T>
class NodoT
{
public:
	T value;
	NodoT* next;
	int index;
	NodoT(T v) : value(v) {
		next = NULL;
		index = 0;
	}
};