#pragma once

#include "Lista.h"
#include "Common.h"

class DLLEXPORT IteratorLP
{
	friend class Lista;
private:
	const Lista &lis;
	Lista::Nod* nodLista;
	IteratorLP(const Lista& l, Lista::Nod* e);

public:
	~IteratorLP();
	TElem& element();
	bool valid();
	void urmator();
	void prim();
};

