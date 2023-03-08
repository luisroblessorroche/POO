#include "Fecha.hpp"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <locale>

//-----------CONSTRUCTORES-------------

Fecha::Fecha(int d, int m, int a): dia{d},mes{m},anno{a}
{
	std::time_t tiempo = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo);
	
	if(anno == 0)
	{
		anno = tiempo_descompuesto->tm_year+1900;
	}
	
	if(mes == 0)
	{
		mes = tiempo_descompuesto->tm_mon + 1;
	}
	
	if(dia == 0)
	{
		dia = tiempo_descompuesto->tm_mday;
	}
	
	comprobar_constructor_correcto();
}

Fecha::Fecha(const char* c)
{
	if(sscanf(c,"%d/%d/%d",&dia,&mes,&anno)!=3)
	{
		Fecha::Invalida format("formato incorrecto");
		throw format;
	}
	std::time_t tiempo = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo);
	
	if(anno == 0)
	{
		anno = tiempo_descompuesto->tm_year+1900;
	}
	
	if(mes == 0)
	{
		mes = tiempo_descompuesto->tm_mon + 1;
	}
	
	if(dia == 0)
	{
		dia = tiempo_descompuesto->tm_mday;
	}
	
	comprobar_constructor_correcto();
}
