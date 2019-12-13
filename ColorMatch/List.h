#pragma once
#include "NodoT.h"
template<class T>
class List
{
public:
	NodoT<T>* first;
	NodoT<T>* last;
	int size;
	List();
	~List();
	void push_back(T val);
	void push_front(T val);
	void insertion();
	NodoT<T>* get_at(int index);
};

//Constructor de la lista
template<class T>
List<T>::List() {
	first = NULL;
	last = NULL;
	size = 0;
}

//Destructor de lista
template<class T>
List<T>::~List() {

}

//Agrega un valor a la lista
//@param valor que se quiere agregar a la lista
template<class T>
void List<T>::push_back(T val) {
	if (first == NULL) {
		first = new NodoT<T>(val);
		last = first;
		first->index = last->index;
		size++;
	}
	else {
		if (first == last) {
			last = new NodoT<T>(val);
			first->next = last;
			first->next->index++;
			size++;
		}
		else {
			last->next = new NodoT<T>(val);
			last->next->index = last->index;
			last = last->next;
			last->index++;
			size++;
		}
	}
}


//Obtiene el elemento de la lista en el índice especificado
// @param index Es el índice del elemento que se desea eliminar
template<class T>
NodoT<T>* List<T>::get_at(int index) {
	bool found;

	if (first == NULL) {
		return NULL;
	}
	else {

		if (first == last) { 
			if (first->index == index) { 

				return first;

			}
			else {
				return NULL;
			}
		}
		else {
			NodoT<T>* it = first;

			while (it != NULL) { 
				if (it->index == index) { 
					return it; 
				}
				else {
					found = false;
				}
				it = it->next;
			}
			if (found == false) { 
				return NULL;
			}
		}
	}
}

//Agrega un elemento al inicio de la lista
//@param val Es el valor a almacenar
template<class T>
void List<T>::push_front(T val) {

	if (first == NULL) {
		first = new NodoT<T>(val);
		last = first;
		last->index = first->index;
		size++;
	}
	else {
		if (first == last) { 
			first = new NodoT<T>(val); 
			first->next = last;
			first->next->index++;
			size++;
		}
		else { 
			NodoT<T>* temporal = first;
			first = new NodoT<T>(val);
			first->next = temporal;
			temporal->index++; 
			while (temporal->next != NULL) { 
				temporal->next->index++;
				temporal = temporal->next; 
			}
			size++;
		}
	}
}

//Insertion sort
template<class T>
void List<T>::insertion() {
	if (first == NULL)
		return;
	NodoT<T>* result = first;
	NodoT<T>* previous = first;
	NodoT<T>* current = first->next;
	NodoT<T>* next = NULL;
	NodoT<T>* it = NULL;

	while (current)
	{
		next = current->next;
		if (previous->value > current->value) {
			previous = current;
		}
		else {
			previous->next = next;
			if (current->value > result->value) {
				NodoT<T>* temp = result;
				result = current;
				result->next = temp;
			}
			if (result->next != NULL) {
				for (it = result; it->next != current; it = it->next) {
					if (it->next != NULL && current->value >= it->next->value) {
						NodoT<T>* temporal = it->next;
						it->next = current;
						current->next = temporal;
						break;
					}
				}
			}
		}
		current = next;
	}
	first = result;
	first->index = 0;
	for (auto it = first; it != NULL; it = it->next) {
		if (it->next != NULL)
			it->next->index = it->index + 1;
	}
}