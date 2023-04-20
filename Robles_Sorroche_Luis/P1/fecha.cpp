#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <locale>


//-----------------------------FUNCIONES PRIVADAS--------------------------

//comprueba que la fecha es valida
void Fecha::comprobar_validez()
{
	//el rango del dia esta entre 1 y el ultimo dia dependiendo del mes, que puede ser 31,30,29,28 y 0 si esta mal
	if(d > ultimo_dia() || d < 1)
	{
		throw Invalida("Dia Invalido");
	}
	//el rango del mes esta entre 1 y 12
	if(m < 1 || m > 12)
	{
		throw Invalida("Mes Invalido");
	}
	//el rango del anno esta entre 1902 y 2037
	if(a < Fecha::AnnoMinimo || a > Fecha::AnnoMaximo)
	{
		throw Invalida("Anno Invalido");
	}
}

int Fecha::ultimo_dia() const
{
	//si es enero, marzo, mayo, julio, agosto, octubre o diciembre devolvera 31
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		return 31;
	}
	//si es abril, junio, septiembre o noviembre devolvera 30
	if(m == 4 || m == 6 || m == 9 || m == 11)
	{
		return 30;
	}
	if(m == 2)
	{
		// si es febrero y cae en anno bisiesto devolvera 29
		if(a % 4 == 0 && (a % 400 == 0 || a % 100 != 0))
		{
			return 29;
		}
		else
		{
			//si no es bisiesto devolvera 28
			return 28;
		}
	}
	
	//el mes no es valido entonces
	throw Invalida("Mes Invalido");
}

//-------------------METODOS PUBLICOS----------------------


//-----------CONSTRUCTORES-------------

Fecha::Fecha(int dia, int mes, int anno): d{dia},m{mes},a{anno}
{
	//coger la fecha actual si algun valor se inicializa por defecto
	std::time_t tiempo = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo);
	//asignar valor del sistema si anno esta por defecto
	if(a == 0)
	{
		a = tiempo_descompuesto->tm_year + 1900;
	}
	//asignar valor del sistema si mes esta por defecto
	if(m == 0)
	{
		m = tiempo_descompuesto->tm_mon + 1;
	}
	//asignar valor del sistema si dia esta por defecto
	if(d == 0)
	{
		d = tiempo_descompuesto->tm_mday;
	}
	//comprobamos que es correcto
	comprobar_validez();
}

Fecha::Fecha(const char* c)
{
	if(sscanf(c,"%d/%d/%d",&d,&m,&a)!=3)
	{
		throw Invalida("Formato Invalido");
	}
	std::time_t tiempo = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo);
	
	if(a == 0)
	{
		a = tiempo_descompuesto->tm_year + 1900;
	}
	if(m == 0)
	{
		m = tiempo_descompuesto->tm_mon + 1;
	}
	if(d == 0)
	{
		d = tiempo_descompuesto->tm_mday;
	}
	comprobar_validez();
}

//-------------------CONVERSOR DE FECHA A CADENA----------------------------
const char* Fecha::cadena() const
{
	std::locale::global(std::locale("es_ES.utf8"));
	char *aux = new char[36];
	std::tm f{};
	
	f.tm_mday = d;
	f.tm_mon = m - 1;
	f.tm_year = a - 1900;
	mktime(&f);
	
	strftime(aux,36,"%A %e de %B de %Y",&f);
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

Fecha Fecha::operator ++(int)
{
	std::unique_ptr<Fecha> f(new Fecha(*this));
    *this += 1;
    return *f;
}

Fecha& Fecha::operator --()
{
	*this += -1;
	return *this;	
}

Fecha Fecha::operator --(int)
{
	std::unique_ptr<Fecha> f(new Fecha(*this));
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

bool operator ==(const Fecha& f1, const Fecha& f2)
{
	return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno());
}

bool operator !=(const Fecha& f1, const Fecha& f2)
{
	return !(f1 == f2);
}

bool operator <(const Fecha& f1, const Fecha& f2)
{
	return ((f1.anno() < f2.anno()) || (f1.anno() == f2.anno() && f1.mes() < f2.mes()) ||
			(f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() < f2.dia()));
}

bool operator >(const Fecha& f1, const Fecha& f2)
{
	return f2 < f1;
}

bool operator <=(const Fecha& f1, const Fecha& f2)
{
	return ((f1 < f2) || (f1 == f2));
}

bool operator >=(const Fecha& f1, const Fecha& f2)
{
	return ((f1 > f2) || (f1 == f2));
}

//--------------------ENTRADA/SALIDA-------------------------

std::ostream& operator <<(std::ostream& os, const Fecha& f) noexcept
{
	os << f.cadena();
	return os;
}

std::istream& operator >>(std::istream& is, Fecha& f)
{
	
	//dd/mm/aaaa son 10 caracteres mas el caracter terminador
	char linea[11];
	is.getline(linea,11);
	try
	{
		f = linea;
	}
	catch(Fecha::Invalida e)
	{
		is.setstate(std::ios::failbit);
		throw e;
	}

	return is;
}






