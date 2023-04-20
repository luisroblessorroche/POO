#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include "articulo.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

class Numero;
class Tarjeta;


//------------------------clase Clave-----------------------------

class Clave
{
	public:
		Clave(const char* c);
		Cadena clave() const noexcept{return clave_;}
		bool verifica(const char* c) const;
		
		enum Razon{CORTA, ERROR_CRYPT};
		
		class Incorrecta
		{
			public:
				Incorrecta(const Clave::Razon r):razon_{r}{}
				Clave::Razon razon() const noexcept{return razon_;}
			private:
				Clave::Razon razon_;	
		};	
	private:
		Cadena clave_;
};

class Usuario
{
	public:
		typedef std::map<Numero, Tarjeta*> Tarjetas;
		typedef std::unordered_map<Articulo*, unsigned int> Articulos;
		
		Usuario(const Cadena& i, const Cadena& n, const Cadena& a, const Cadena& d, const Clave& c);
		Usuario(const Usuario& u) = delete;
		Usuario& operator =(const Usuario& u) = delete;
		
		~Usuario();
		
		const Cadena& id() const noexcept{return id_;}
		const Cadena& nombre() const noexcept{return nombre_;}
		const Cadena& apellidos() const noexcept{return apellidos_;}
		const Cadena& direccion() const noexcept{return direccion_;}
		const Tarjetas& tarjetas() const noexcept{return tarjetas_;}
		const Articulos& compra() const noexcept{return articulos_;}
		size_t n_articulos() const noexcept{return articulos_.size();}
		
		void es_titular_de(const Tarjeta& t);
		void no_es_titular_de(const Tarjeta& t);
		void compra(const Articulo& art, size_t cant = 1);
		void vaciar_carro();
		
		class Id_duplicado
		{
			public:
				Id_duplicado(const Cadena& i):idd_{i}{}
				const Cadena& idd() const noexcept{return idd_;}
			private:
				Cadena idd_;	
		};
		
		friend std::ostream& operator <<(std::ostream& os, const Usuario& u) noexcept;
	private:
	
		const Cadena id_;
		const Cadena nombre_;
		const Cadena apellidos_;
		const Cadena direccion_;
		Clave clave_;
		Tarjetas tarjetas_;
		Articulos articulos_;
		
		static std::unordered_set<Cadena> usuarios_;
};

void mostrar_carro(std::ostream& os, const Usuario& u) noexcept;

#endif

