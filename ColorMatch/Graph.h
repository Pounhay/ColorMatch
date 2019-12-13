#pragma once
#include "Node.h"
#include <stdio.h>

template<class T>
class Graph
{
public:
	Node<T>* first;
	Graph();
	~Graph();
	void insert(Node<T>* val);
	void insert(Node<T>* val, Node<T>* padre, Node<T>* hijo, std::string pos);
};

//Constructor del grafo
template<class T>
Graph<T>::Graph() {
	first = NULL;
}

//Deconstructor del grafo
template<class T>
Graph<T>::~Graph() {

}

//Agrega un nodo al grafo
//@param Nodo que se quiere agregar
template<class T>
void Graph<T>::insert(Node<T>* val) {
	if (first == NULL) {
		first = val;
	}
}

//Agrega un nodo al grafo
//@param Nodo que se quiere agregar
//@param Nodo al que se quiere agregar
//@param Nodo hijo que se esta checando
//@param posicion del nodo donde se quiere agregar
template<class T>
void Graph<T>::insert(Node<T>* val, Node<T>* padre, Node<T>* hijo, std::string pos) {
	if (hijo != NULL) {
		if (hijo == padre && pos == "Arriba") {
			hijo->Arr = val;
			return;
		}
		else if (hijo == padre && pos == "Abajo") {
			hijo->Aba = val;
			return;
		}
		else if (hijo == padre && pos == "Derecha") {
			hijo->Der = val;
			return;
		}
		else if (hijo == padre && pos == "Izquierda") {
			hijo->Izq = val;
			return;
		}
		else {
			insert(val, padre, hijo->Aba, pos);
			insert(val, padre, hijo->Der, pos);
		}
	}
}