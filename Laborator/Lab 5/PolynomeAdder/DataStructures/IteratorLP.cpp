#include "IteratorLP.h"

IteratorLP::IteratorLP(const Lista& l, Lista::Nod* e) : lis{l}, nodLista{e}{}

IteratorLP::~IteratorLP() {}

TElem& IteratorLP::element()
{
	if (valid() == 0)
	{
		throw std::exception();
	}
	return this->nodLista->element;
}

bool IteratorLP::valid()
{
	if (nodLista == NULL)
	{
		return false;
	}
	return true;
}

void IteratorLP::urmator()
{
	if (valid())
	{
        nodPrev = nodLista;
		nodLista = nodLista->urmator;
	}
	else
	{
		throw std::exception();
	}
}

void IteratorLP::prim()
{
	nodLista = lis.primNod;
}
