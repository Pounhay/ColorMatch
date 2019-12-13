#pragma once
#include <iostream>
#include "List.h"

template<class T>
class Node
{
public:
	T value;
	Node<T>* Der;
	Node<T>* Aba;
	Node<T>* Izq;
	Node<T>* Arr;
	bool visited = false;
	bool toDestroy = false;
	Node(T v) : value(v) {
		Der = NULL;
		Izq = NULL;
		Aba = NULL;
		Arr = NULL;
	};
};
