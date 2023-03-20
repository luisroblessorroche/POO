#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <locale>


//-----------------------------FUNCIONES PRIVADAS--------------------------

void Fecha::comprobar_validez()
{
	if(d > ultimo_dia() || d < 0)
	{
		Fecha::Invalida dia_invalido("Dia Invalido");
		throw dia_invalido;
	}
	if(a < Fecha::AnnoMinimo || a > Fecha::AnnoMaximo)
	{
		Fecha::Invalida anno_invalido("Anno Invalido");
		throw anno_invalido;
	}
}

int Fecha::ultimo_dia() const
{
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12){return 31;}
	if(m == 4 || m == 6 || m == 9 || m == 11){return 30;}
	if(m == 2)
	{
		if(a % 4 == 0 && (a % 400 == 0 || a % 100 != 0)){return 29;}
		else{return 28;}
	}
	
	if(m != 1 && m != 2 && m != 3 && m != 4 && m != 5 && m != 6 && m != 7 && m != 8 && m != 9 && m != 10 && m != 11 && m != 12)
	{
		Fecha::Invalida mes_invalido("Mes Invalido");
		throw mes_invalido;
		return 0;
	}
}

//-------------------METODOS PUBLICOS----------------------


//-----------CONSTRUCTORES-------------

Fecha::Fecha(int dia, int mes, int anno): d{dia},m{mes},a{anno}
{
	std::time_t tiempo = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo);
	if(a == 0){a = tiempo_descompuesto->tm_year + 1900;}
	if(m == 0){m = tiempo_descompuesto->tm_mon + 1;}
	if(d == 0){d = tiempo_descompuesto->tm_mday;}
	comprobar_validez();
}

Fecha::Fecha(const char* c)
{
	if(sscanf(c,"%d/%d/%d",&d,&m,&a)!=3)
	{
		Fecha::Invalida formato_invalido("formato incorrecto");
		throw formato_invalido;
	}
	std::time_t tiempo = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo);
	
	if(a == 0){a = tiempo_descompuesto->tm_year + 1900;}
	if(m == 0){m = tiempo_descompuesto->tm_mon + 1;}
	if(d == 0){d = tiempo_descompuesto->tm_mday;}
	comprobar_validez();
}

//-------------------CONVERSOR DE FECHA A CADENA----------------------------
Fecha::operator const char*() const
{
	std::locale::global(std::locale("es_ES.utf8"));
	char *aux = new char[100];
	
	std::time_t tiempo = std::time(nullptr);
	std::tm* f = std::localtime(&tiempo);
	
	f->tm_mday = d;
	f->tm_mon = m - 1;
	f->tm_year = a - 1900;
	mktime(f);
	strftime(aux,100,"%A %e de %B de %Y",f);
	return aux;
}

//-------------------------OPERADORES---------------------------------

Fecha& Fecha::operator +=(int i)
{
	std::tm f{};
	f.tm_mday = d + i;
	f.tm_mon = m - 1;
	f.tm_year = a - 1900;
	std::mktime(&f);
	
	d = f.tm_mday;
	m = f.tm_mon + 1;
	a = f.tm_year + 1900;
	
	comprobar_validez();
	return *this;
} 

Fecha& Fecha::operator -=(int i)
{
	*this += -i;
	return *this;	
} 

Fecha& Fecha::operator ++()
{
	*this += 1;
	return *this;
} 

Fecha& Fecha::operator ++(int)
{
	Fecha *f = new Fecha(*this);
	*this += 1;
	return *f;
}

Fecha& Fecha::operator --()
{
	*this += -1;
	return *this;	
}

Fecha& Fecha::operator --(int)
{
	Fecha *f = new Fecha(*this);
	*this += -1;
	return *f;	
}

//---------------------OPERADORES ARITMETICOS------------------------

Fecha Fecha::operator +(int i) const
{
	Fecha f(*this);
	return f += i;
}

Fecha Fecha::operator -(int i) const
{
	Fecha f(*this);
	return f += -i;	
}


//--------------------------OPERADORES LOGICOS--------------------------

bool operator ==(const Fecha& f1, const Fecha& f2){return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno());}
bool operator !=(const Fecha& f1, const Fecha& f2){return !(f1 == f2);}
bool operator <(const Fecha& f1, const Fecha& f2){return ((f1.anno() < f2.anno()) || (f1.anno() == f2.anno() && f1.mes() < f2.mes())||(f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() < f2.dia()));}
bool operator >(const Fecha& f1, const Fecha& f2){return f2 < f1;}
bool operator <=(const Fecha& f1, const Fecha& f2){return ((f1 < f2) || (f1 == f2));}
bool operator >=(const Fecha& f1, const Fecha& f2){return ((f1 > f2) || (f1 == f2));}

//--------------------------CONSTRUCTOR INVALIDA-------------------------

Fecha::Invalida::Invalida(const char* mot): motivo(mot){}








