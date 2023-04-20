#include "cadena.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>

//--------------------------CONSTRUCTORES---------------------------------

Cadena::Cadena(size_t t, char c): s_{new char[t+1]},tam_{t}
{
	for(size_t i = 0; i < tam_; i++)
	{
		s_[i] = c;
	}
	s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cad): s_{new char[cad.tam_ + 1]}, tam_{cad.tam_}
{
	strcpy(s_,cad.s_);
}


Cadena::Cadena(const char* cad): s_{new char[strlen(cad)+1]}, tam_{strlen(cad)}
{
	strcpy(s_,cad);
}

Cadena& Cadena::operator =(const Cadena& cad)
{
	delete[] s_;
	s_ = new char[cad.tam_ + 1];
	tam_ = cad.tam_;
	strcpy(s_,cad.s_);
	return *this;
}


Cadena& Cadena::operator +=(const Cadena& cad)
{
	char* aux = new char[tam_ +1];
	strcpy(aux,s_);
	tam_ += cad.tam_;
	delete[] s_;
	s_ = new char[tam_ + 1];
	strcpy(s_,aux);
	strcat(s_,cad.s_);
	delete[] aux;
	return *this;
}

Cadena operator +(const Cadena& cad1, const Cadena& cad2)
{
	Cadena aux(cad1);
	return aux += cad2;
}

//-----------------------------OPERADORES LOGICOS------------------------------


bool operator ==(const Cadena& cad1, const Cadena& cad2)
{
	return ((const char*)cad1 == (const char*)cad2);
	//return (strcmp((const char*)cad1,(const char*)cad2) == 0);
}

bool operator ==(const char* cad1, const char* cad2)
{
	return (strcmp(cad1,cad2) == 0);
}
/*
bool operator !=(const Cadena& cad1, const Cadena& cad2)
{
	return !(cad1 == cad2);
}

bool operator <(const Cadena& cad1, const Cadena& cad2)
{
	return (strcmp(cad1.char*(),cad2.char*()) < 0);
}

bool operator >(const Cadena& cad1, const Cadena& cad2)
{
	return cad2 < cad1;
}

bool operator <=(const Cadena& cad1, const Cadena& cad2)
{
	return ((cad1 < cad2) || (cad1 == cad2));
}

bool operator >=(const Cadena& cad1, const Cadena& cad2)
{
	return ((cad1 > cad2) || (cad1 == cad2));
}

*/
//----------------------------FUNCIONES AT--------------------------------

char& Cadena::at(size_t i)
{
	if(i<tam_)
	{
		return s_[i];
	}
	else
	{
		throw std::out_of_range("Funcion at(): fuera del rango permitido");
	}
}

const char& Cadena::at(size_t i) const
{
	if(i < tam_)
	{
		return s_[i];
	}
	else
	{
		throw std::out_of_range("Funcion at(): fuera del rango permitido");
	}
}

Cadena Cadena::substr(size_t i, size_t t) const
{
	if(i+t> tam_ || t > tam_ || i > tam_)
	{
		throw std::out_of_range("Funcion substr(): fuera del rango permitido");
	}
	else
	{
		Cadena aux(t);
		strncpy(aux.s_,s_+i,t);
		aux.s_[t] = '\0';
		return aux;
	}
}

//---------------------------------DESTRUCTOR-------------------------------


Cadena::~Cadena()
{
	delete[] s_;
	tam_ = 0;
}
