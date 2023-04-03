#include "cadena.hpp"
#include <iostream>
#include <cstring>
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

Cadena::Cadena(Cadena&& cad): s_{cad.s_}, tam_{cad.tam_}
{
	cad.tam_ = 0;
	cad.s_ = nullptr;
}

Cadena& Cadena::operator =(const Cadena& cad)
{
	if(this != &cad)
	{
		tam_ = cad.tam_;
		delete[] s_;
		s_ = new char[tam_+1];
		strcpy(s_,cad.s_);
	}
	return *this;
} 


Cadena& Cadena::operator =(Cadena&& cad)
{
	if(this != &cad)
	{
		tam_ = cad.tam_;
		delete[] s_;
		s_ = cad.s_;
		cad.s_ = nullptr;
		cad.tam_ = 0;
	}
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

/*
bool operator ==(const Cadena& cad1, const Cadena& cad2)
{
	return (strcmp(cad1.c_str(),cad2.c_str()) == 0);
}

bool operator !=(const Cadena& cad1, const Cadena& cad2)
{
	return !(cad1 == cad2);
}

bool operator <(const Cadena& cad1, const Cadena& cad2)
{
	return (strcmp(cad1.c_str(),cad2.c_str()) < 0);
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


//---------------------ENTRADA/SALIDA--------------------------

std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept
{
	os << cad.c_str();
	return os;
}

std::istream& operator >>(std::istream& is, Cadena& cad)
{
	char linea[33]="";//¿cómo que 33? = limite de 32 caracteres + el caracter terminador
	is.width(33);
	is >> linea;
	cad = linea;
	return is;
}
//---------------------------------DESTRUCTOR-------------------------------


Cadena::~Cadena()
{
	delete[] s_;
}
