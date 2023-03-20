#include "cadena.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>

//--------------------------CONSTRUCTORES---------------------------------

Cadena::Cadena(size_t t, char c): s{new char[t+1]},tam{t}
{
	for(size_t i = 0; i < tam; i++)
	{
		s[i] = c;
	}
	s[tam] = '\0';
}

Cadena::Cadena(const Cadena& cad): s{new char[cad.tam + 1]}, tam{cad.tam}{strcpy(s,cad.s);}

Cadena::Cadena(const char* cad): s{new char[strlen(cad)+1]}, tam{strlen(cad)}{strcpy(s,cad);}

Cadena& Cadena::operator =(const Cadena& cad)
{
	if(this != &cad)
	{
		delete[] s;
		s = new char[cad.tam + 1];
		tam = cad.tam;
		strcpy(s,cad.s);
	}
	return *this;
}


Cadena& Cadena::operator +=(const Cadena& cad)
{
	char* aux = new char[tam +1];
	strcpy(aux,s);
	tam += cad.tam;
	delete[] s;
	s = new char[tam + 1];
	strcpy(s,aux);
	strcat(s,cad.s);
	delete[] aux;
	return *this;
}

Cadena operator +(const Cadena& cad1, const Cadena& cad2)
{
	Cadena aux(cad1);
	return aux += cad2;
}

//-----------------------------OPERADORES LOGICOS------------------------------

bool operator ==(const Cadena& cad1, const Cadena& cad2){return !strcmp(cad1,cad2);}
bool operator !=(const Cadena& cad1, const Cadena& cad2){return strcmp(cad1,cad2);}
bool operator <(const Cadena& cad1, const Cadena& cad2){return (strcmp(cad1,cad2) < 0);}
bool operator >(const Cadena& cad1, const Cadena& cad2){return cad2 < cad1;}
bool operator <=(const Cadena& cad1, const Cadena& cad2){return ((cad1 < cad2) || (cad1 == cad2));}
bool operator >=(const Cadena& cad1, const Cadena& cad2){return ((cad1 > cad2) || (cad1 == cad2));}


//----------------------------FUNCIONES AT--------------------------------

char& Cadena::at(size_t i)
{
	if(i<tam){return s[i];}
	else{throw std::out_of_range("Funcion at(): fuera del rango permitido");}
}

const char& Cadena::at(size_t i) const
{
	if(i < tam){return s[i];}
	else{throw std::out_of_range("Funcion at(): fuera del rango permitido");}
}

Cadena Cadena::substr(size_t i, size_t t) const
{
	if(i+t> tam || t > tam || i > tam){throw std::out_of_range("Funcion substr(): fuera del rango permitido");}
	else
	{
		Cadena aux(t);
		strncpy(aux.s,s+i,t);
		aux.s[t] = '\0';
		return aux;
	}
}

//---------------------------------DESTRUCTOR-------------------------------


Cadena::~Cadena()
{
	delete[] s;
	tam = 0;
}
