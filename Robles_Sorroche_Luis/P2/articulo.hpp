#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <locale>
#include <iomanip>


//---------------------------------Clase Articulo--------------------------------

class Articulo
{
	public:
		Articulo(Cadena r, Cadena t, Fecha f, double p, size_t e = 0);
		
		const Cadena& referencia() const noexcept{return referencia_;}
		const Cadena& titulo() const noexcept{return titulo_;}
		const Fecha& f_publi() const noexcept{return f_publi_;}
		
		double precio() const noexcept{return precio_;}
		double& precio() noexcept{return precio_;}
		size_t stock() const noexcept{return stock_;}
		size_t& stock() noexcept{return stock_;}
		
	private:
		const Cadena referencia_;
		const Cadena titulo_;
		const Fecha f_publi_;
		double precio_;
		size_t stock_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& art) noexcept;

#endif
