#pragma once

#include <ctime>
#include "Graph.h"
#include "List.h"
#include "Tile.h"
#include "Text.h"

class Board
{
	Graph<Tile*> board;
	List<Tile*> generator;
	SDL_Renderer* renderer;
	GameObject* objBackground,* objMask,* objArrows;
	Text *textScore;
	SDL_Rect destRect;
	Node<Tile*>* to = NULL;
	Node<Tile*>* from = NULL;
	bool active = false;
	bool finishedMoving = true;
	bool destroy = false;
	bool init = false;
	bool render = false;
	int score = 0, mscore = 4, scount = 0;
	
public:
	//Constructor de la clase Board
	Board(SDL_Renderer* ren) {
		renderer = ren;
		objBackground = new GameObject("./Assets/Background.png", 0, 0, 600, 700, renderer);
		objMask = new GameObject("./Assets/Mask.png", 0, 0, 600, 147, renderer);
		textScore = new Text(250, 30, 100, 64, renderer, { 0, 0, 0 });
		CreateBoard();
		for (int i = 0; i < 8; i++) {
			Tile* gen = new Tile(renderer, 44 + (i * 64), 83, rand() % 7);
			generator.push_back(gen);
		}
	}
	//Destructor de la clase Board
	~Board();

	//Regresa si se tiene una casilla activada
	bool GetActive() { return active; }

	//Genra un numero random
	int TileRandomizer() {
		if ((rand() % 100) < 99)
			return rand() % 7;
		else
			return rand() % (2) + 8;
	}

	//Crea e inicializa el board
	void CreateBoard() {
		List<Node<Tile*>*> list;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Tile* temp = new Tile(renderer, 44+(j*64), 147+(i*64), TileRandomizer());
				Node<Tile*>* tmp = new Node<Tile*>(temp);
				list.push_back(tmp);
			}
		}
		board.insert(list.get_at(0)->value);
		for (int i = 0; i < 64; i++) {
			if (i + 1 < 64 && i % 8 != 7)
				board.insert(list.get_at(i + 1)->value, list.get_at(i)->value, board.first, "Derecha");
			if (i - 8 >= 0)
				board.insert(list.get_at(i - 8)->value, list.get_at(i)->value, board.first, "Arriba");
			if (i + 8 < 64)
				board.insert(list.get_at(i + 8)->value, list.get_at(i)->value, board.first, "Abajo");
			if (i - 1 >= 0 && i % 8 != 0)
				board.insert(list.get_at(i - 1)->value, list.get_at(i)->value, board.first, "Izquierda");
		}
	}

	//Destruye una fila
	//@param Tile donde se elimina
	void DestroyRow(Node<Tile*>* init) {
		for (Node<Tile*>* temp = init; temp != NULL; temp = temp->Izq)
			temp->toDestroy = true;
		for (Node<Tile*>* temp = init; temp != NULL; temp = temp->Der) 
			temp->toDestroy = true;
		init->toDestroy = true;
		score += 8;
	}

	//Devuelve el score
	int GetScore() { return score; }

	//Destruye una columna
	//@param Tile donde se elimina
	void DestroyColumn(Node<Tile*>* init) {
		for (Node<Tile*>* temp = init; temp != NULL; temp = temp->Arr)
			temp->toDestroy = true;
		for (Node<Tile*>* temp = init; temp != NULL; temp = temp->Aba)
			temp->toDestroy = true;
		init->toDestroy = true;
		score += 8;
	}

	//Selecciona una Tile dependiendo de coordenadas x y y
	//@param posicion en x
	//@param posicion en y
	void TileSelect(int mx1, int my1) {
		for (Node<Tile*>* temp = board.first; temp != NULL; temp = temp->Aba) {
			for (Node<Tile*>* tmp = temp; tmp != NULL; tmp = tmp->Der) {
				if ((mx1 > tmp->value->GetX()) && (mx1 < tmp->value->GetX() + tmp->value->GetW()) && (my1 > tmp->value->GetY()) && (my1 < tmp->value->GetY() + tmp->value->GetH()))
					from = tmp;
			}
		}
		if (from != NULL && from->value->GetChoosen()==false) {
			if (from->value->GetType() == 8) {
				DestroyColumn(from);
				destroy = true;
				from->value->UnChoose();
			}
			if (from->value->GetType() == 9) {
				DestroyRow(from);
				destroy = true;
				from->value->UnChoose();
			}
			else {
				from->value->Choose();
				active = true;
			}
		}
	}

	//Mueve una Tile seleccionada dependiendo de coordenadas x y y
	//@param posicion en x
	//@param posicion en y
	void TileMove(int mx1, int my1) {
		if (from != NULL) {
			Node<Tile*>* tmp = from;
			if ((tmp->Aba != NULL) && (mx1 > tmp->Aba->value->GetX()) && (mx1 < tmp->Aba->value->GetX() + tmp->Aba->value->GetW()) && (my1 > tmp->Aba->value->GetY()) && (my1 < tmp->Aba->value->GetY() + tmp->Aba->value->GetH()))
				to = tmp->Aba;
			else if ((tmp->Der != NULL) && (mx1 > tmp->Der->value->GetX()) && (mx1 < tmp->Der->value->GetX() + tmp->Der->value->GetW()) && (my1 > tmp->Der->value->GetY()) && (my1 < tmp->Der->value->GetY() + tmp->Der->value->GetH()))
				to = tmp->Der;
			else if ((tmp->Izq != NULL) && (mx1 > tmp->Izq->value->GetX()) && (mx1 < tmp->Izq->value->GetX() + tmp->Izq->value->GetW()) && (my1 > tmp->Izq->value->GetY()) && (my1 < tmp->Izq->value->GetY() + tmp->Izq->value->GetH()))
				to = tmp->Izq;
			else if ((tmp->Arr != NULL) && (mx1 > tmp->Arr->value->GetX()) && (mx1 < tmp->Arr->value->GetX() + tmp->Arr->value->GetW()) && (my1 > tmp->Arr->value->GetY()) && (my1 < tmp->Arr->value->GetY() + tmp->Arr->value->GetH()))
				to = tmp->Arr;
			else {
				from->value->UnChoose();
				TileSelect(mx1, my1);
				return;
			}
			SwapTiles(to->value, from->value, 16);
			from->value->UnChoose();
			active = false;
		}
	}

	//Checa si hay 4 Tiles del mismo tipo juntas y las destruye n caso de que asi sea
	void CheckIf4() {
		List<Node<Tile*>*>* talVez = new List<Node<Tile*>*>;
		if (finishedMoving == true) {
			for (Node<Tile*>* temp = board.first; temp != NULL; temp = temp->Aba) {
				for (Node<Tile*>* tmp = temp; tmp != NULL; tmp = tmp->Der) {
					if (!tmp->visited) {
						talVez->push_back(tmp);
						CheckIf4(tmp, talVez);
						if (talVez->size > 3) {
							int it = 0;
							for (NodoT<Node<Tile*>*>* dest = talVez->first; dest != NULL; dest = dest->next) {
								dest->value->toDestroy = true;
								dest->value->value->SetType(7);
								destroy = true;
								init = true;
								it++;
								if (scount == 0) {
									if (it > 3) {
										mscore += scount;
										scount += 2;
									}
								}
								else {
									mscore += scount;
									scount += 2;
								}
							}
						}
					}
					talVez = new List<Node<Tile*>*>;
				}
			}
			for (Node<Tile*>* temp = board.first; temp != NULL; temp = temp->Aba) {
				for (Node<Tile*>* tmp = temp; tmp != NULL; tmp = tmp->Der) {
					tmp->visited = false;
				}
			}
		}if (destroy) {
			int i = 0;
			finishedMoving = false;
			for (Node<Tile*>* tmp = board.first; tmp != NULL; tmp = tmp->Der) {
				if (tmp->toDestroy) {
					FallTiles(generator.get_at(i)->value, tmp->value, 32);
					generator.get_at(i)->value->SetType(TileRandomizer());
					tmp->toDestroy = false;
					return;
				}
				for (Node<Tile*>* temp = tmp; temp != NULL; temp = temp->Aba) {
					if (temp->toDestroy && temp->Arr != NULL) {
						for (Node<Tile*>* arriba = temp; arriba->Arr != NULL; arriba = arriba->Arr) {
							FallTiles(arriba->Arr->value, arriba->value, 32);
							arriba->toDestroy = false;
							arriba->Arr->toDestroy = true;
							return;
						}
					}
				}
				i++;
			}
			finishedMoving = true;
			destroy = false;	
			for (Node<Tile*>* temp = board.first; temp != NULL; temp = temp->Aba) {
				for (Node<Tile*>* tmp = temp; tmp != NULL; tmp = tmp->Der) {
					if (!tmp->visited) {
						talVez->push_back(tmp);
						CheckIf4(tmp, talVez);
						if (talVez->size > 3) {
							init = false;
						}
						talVez = new List<Node<Tile*>*>;
					}
				}
			}
		}if (init) {
			score += mscore;
			scount = 0;
			mscore = 4;
			init = false;
		}
	}	

	//Sobrecarga recursiva del metodo anterior
	//@param nodo en el que se busca
	//@param lista a donde se agrega
	void CheckIf4(Node<Tile*>* current, List<Node<Tile*>*>* list) {
		if (current != NULL) {
			int c = current->value->GetType();
			current->visited = true;
			if (current->Der != NULL) {
				if (c == current->Der->value->GetType() && !current->Der->visited) {
					list->push_back(current->Der);
					CheckIf4(current->Der, list);
				}
			}
			if (current->Arr != NULL) {
				if (c == current->Arr->value->GetType() && !current->Arr->visited) {
					list->push_back(current->Arr);
					CheckIf4(current->Arr, list);
				}
			}
			if (current->Izq != NULL) {
				if (c == current->Izq->value->GetType() && !current->Izq->visited) {
					list->push_back(current->Izq);
					CheckIf4(current->Izq, list);
				}
			}
			if (current->Aba != NULL) {
				if (c == current->Aba->value->GetType() && !current->Aba->visited) {
					list->push_back(current->Aba);
					CheckIf4(current->Aba, list);
				}
			}
		}
	}

	//Regresa el valor de si hay Tiles cayendo
	bool CheckIfFalling() {
		for (Node<Tile*>* temp = board.first; temp != NULL; temp = temp->Aba) {
			for (Node<Tile*>* tmp = temp; tmp != NULL; tmp = tmp->Der) {
				if (tmp->value->GetFalling())
					return true;
			}
		}
	}

	//Cambia dos tiles de lugar manteniendo el grafo
	//@param primera Tile a cambiar
	//@param segunda Tile a cambiar
	//@param velocidad de cambio
	void SwapTiles(Tile* a, Tile* b, int s) {
		int data = a->GetType();
		a->Swap(b->GetX(), b->GetY(), b->GetType(), s);
		b->Swap(a->GetX(), a->GetY(), data, s);
	}	

	//Cambia dos tiles de lugar manteniendo el grafo
	//@param primera Tile a cambiar
	//@param segunda Tile a cambiar
	//@param velocidad de cambio
	void FallTiles(Tile* a, Tile* b, int s) {
		int data = a->GetType();
		a->Fall(b->GetY(), b->GetType(), s);
		b->Fall(a->GetY(), data, s);
	}

	//Metodo que Actualiza el tablero y sus componentes
	void Update() {
		objBackground->Update();
		if (!CheckIfFalling()) {
			CheckIf4();
		}
		for (Node<Tile*>* temp = board.first; temp != NULL; temp = temp->Aba) {
			for (Node<Tile*>* tmp = temp; tmp != NULL; tmp = tmp->Der) {
				tmp->value->Update();
			}
		}
		for(int i = 0;i<8;i++)
			generator.get_at(i)->value->Update();
		objMask->Update(); 
		textScore->Update(std::to_string(score).c_str());
	}

	//Metodo que Renderiza el tablero y sus componentes
	void Render() {
		objBackground->Render();
		for (Node<Tile*>* temp = board.first; temp != NULL; temp = temp->Aba) {
			for (Node<Tile*>* tmp = temp; tmp != NULL; tmp = tmp->Der) {
				tmp->value->Render();
			}
		}
		for (int i = 0; i < 8; i++)
			generator.get_at(i)->value->Render();
		objMask->Render();
		if(render)
			textScore->Render();
	}

	void Init() {
		score = 0;
		mscore = 4; 
		scount = 0;
		render = true;
	}
};

