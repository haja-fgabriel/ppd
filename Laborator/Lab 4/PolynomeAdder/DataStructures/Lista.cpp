#include "Lista.h"
#include "IteratorLP.h"

#include <iostream>

Lista::Lista() { this->primNod = NULL; this->ultimNod = NULL; Marime = 0; }

int Lista::dim() const
{
	return this->Marime;
}

bool Lista::vida() const
{
	if (Marime == 0)
	{
		return true;
	}
	return false;
}

IteratorLP Lista::prim() const
{
	return IteratorLP(*this, primNod);
}

TElem Lista::element(IteratorLP poz) const
{
	if (!poz.valid())
	{
		throw std::exception();
	}
	return poz.nodLista->element;
}

TElem Lista::modifica(IteratorLP poz, TElem e)
{
	if (poz.valid() == 0)
	{
		throw std::exception();
	}
	TElem valVeche = poz.nodLista->element;
	poz.nodLista->element = e;
	return valVeche;
}

void Lista::adaugaSfarsit(TElem e)
{
	Lista::Nod* nou = new Nod(e);
	if (this->primNod == NULL)
	{
		this->primNod = nou;
		this->ultimNod = nou;
	}
	else
	{
		this->ultimNod->urmator = nou;
		this->ultimNod = nou;
	}
	this->Marime++;
}

void Lista::adauga(IteratorLP poz, TElem e)
{
	if (poz.valid() == 0)
	{
		throw std::exception();
	}
	Nod* inc = primNod;
	Nod* urmator = poz.nodLista->urmator;

	Nod* newNod = new Nod(poz.nodLista->element);
	newNod->urmator = urmator;

	poz.nodLista->element = e;
	poz.nodLista->urmator = newNod;
	if (ultimNod == poz.nodLista)
	{
		ultimNod = newNod;
	}
	Marime++;
}

void Lista::adaugaInOrdine(TElem e)
{
    if (Marime == 0)
    {
        adaugaSfarsit(e);
    }
    else
    {
        for (IteratorLP it = prim(); it.valid(); it.urmator())
        {
            if (it.element().Degree > e.Degree)
            {
                adauga(it, e);
                break;
            }
            else if (it.element().Degree == e.Degree)
            {
                it.element().Coefficient += e.Coefficient;
                break;
            }
        }
    }
}

TElem Lista::sterge(IteratorLP poz)
{
	if (poz.valid() == 0)
	{
		throw std::exception();
	}
	Lista::Nod* inc = this->primNod;
	if (poz.nodLista != inc)
	{
		while (inc != NULL && inc->urmator != poz.nodLista)
		{
			inc = inc->urmator;
		}
	}
	inc->urmator = poz.nodLista->urmator;

	if (poz.nodLista == ultimNod) 
	{
		if (ultimNod != primNod)
		{
			ultimNod = inc;
		}
		else
		{
			primNod = ultimNod = NULL;
		}
	}

	TElem retVal = poz.nodLista->element;
	this->Marime--;

	delete poz.nodLista;
	return retVal;
}

IteratorLP Lista::cauta(TElem e) const
{
	IteratorLP inc(*this, primNod);
	while (inc.valid())
	{
		if (inc.element() == e)
		{
			return inc;
		}
		inc.urmator();
	}
	return IteratorLP(*this, NULL);
}

void Lista::stergeToate()
{
	while (Marime > 0)
	{
		Nod* acestNod = primNod;
		primNod = acestNod->urmator;
		delete acestNod;
		Marime--;
	}
	primNod = ultimNod = NULL; 
}

Lista::~Lista()
{
	while (Marime > 0)
	{
		Nod* acestNod = primNod;
		primNod = acestNod->urmator;
		delete acestNod;
		Marime--;
	}

}