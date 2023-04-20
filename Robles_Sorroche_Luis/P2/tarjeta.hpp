#ifndef _TARJETA_HPP_
#define _TARJETA_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

#include <set>
#include <iostream>
#include <cctype>
#include <iomanip>

class Usuario;

//-------------------------clase Numero--------------------------

class Numero
{
	public:
		Numero(const Cadena& cad);
		
		operator const char*()const noexcept{return numero_.c_str();}
		
		enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
		
		class Incorrecto
		{
			public:
				Incorrecto(Numero::Razon r): razon_{r}{}
				Numero::Razon razon() const noexcept{return razon_;}
				
			private:
				Numero::Razon razon_;
		};
	private:
		Cadena numero_;
};

inline bool operator <(const Numero& n1, const Numero& n2)
{
	return static_cast<Cadena>(n1) < static_cast<Cadena>(n2);
}


//------------------------------------clase Tarjeta---------------------------

class Tarjeta
{
	public:
		Tarjeta(const Numero& n, Usuario& u, const Fecha& f);
		Tarjeta(const Tarjeta& t) = delete;
		Tarjeta& operator =(const Tarjeta& t) = delete;
		
		~Tarjeta();
		
		enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
		
		const Numero& numero() const noexcept{return numero_;}
		Usuario* titular() const noexcept{return titular_;}
		const Fecha& caducidad() const noexcept{return caducidad_;}
		Tipo tipo() const noexcept;
		bool activa() const noexcept{return activa_;}
		
		bool activa(bool b = true) noexcept;
		
		class Caducada
		{
			public:
				Caducada(const Fecha& f):caducada_{f}{}
				const Fecha& cuando() const noexcept{return caducada_;}
			private:
				Fecha caducada_;
		};
		
		class Num_duplicado
		{
			public:
				Num_duplicado(const Numero& n):numero_{n}{}
				const Numero& que() const noexcept{return numero_;}
			private:
				Numero numero_;
		};
		class Desactivada{};
	private:
		const Numero numero_;
		Usuario* const titular_;
		const Fecha caducidad_;
		bool activa_;
		
		friend class Usuario;
		void anula_titular();
		
		static std::set<Numero> tarjetas_;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tip);
std::ostream& operator <<(std::ostream& os, const Tarjeta& t) noexcept;

inline bool operator <(const Tarjeta& t1, const Tarjeta& t2) noexcept
{
	return t1.numero() < t2.numero();
}

inline bool Tarjeta::activa(bool b) noexcept
{
	activa_ = b;
	return activa_;
}

#endif





















