#include "usuario.hpp"

std::unordered_set<Cadena> Usuario::usuarios_;

//-------------------Metedos clase Clave----------------------------
Clave::Clave(const char* c)
{
	char* cad;
	if(strlen(c) < 5)
	{
		throw Clave::Incorrecta(Clave::CORTA);
	}
	else
	{
		const char* cjto_caracteres = "./abcdefghijlmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		char salt[2];
		salt[0] = cjto_caracteres[rand() % strlen(cjto_caracteres)];
		salt[1] = cjto_caracteres[rand() % strlen(cjto_caracteres)];
		
		if((cad = (crypt(c,salt))) == NULL)
		{
			throw Clave::Incorrecta(Clave::ERROR_CRYPT);
		}
		else
		{
			clave_ = cad;
		}
	}
}

bool Clave::verifica(const char* c) const 
{
	return !strcmp(crypt(c,clave_.c_str()),clave_.c_str());
}

//------------------------------metodos clase Usuario----------------------------

Usuario::Usuario(const Cadena& i, const Cadena& n, const Cadena& a, const Cadena& d, const Clave& c):
id_{i}, nombre_{n}, apellidos_{a}, direccion_{d}, clave_{c}
{
	if(!usuarios_.insert(i).second)
	{
		throw Usuario::Id_duplicado(i);
	}
}

Usuario::~Usuario()
{
	for(auto& kv:tarjetas_)
	{
		kv.second->anula_titular();
	}
	usuarios_.erase(id_);
}

void Usuario::es_titular_de(const Tarjeta& t)
{
	if(t.titular() == this)
	{
		tarjetas_[t.numero()] = const_cast<Tarjeta*>(&t);
	}
}

void Usuario::no_es_titular_de(const Tarjeta& t)
{
	tarjetas_.erase(t.numero());
}



void Usuario::compra(const Articulo& art, size_t cant)
{
	auto en_cesta = articulos_.find(const_cast<Articulo*>(&art));
	if(en_cesta == articulos_.end())
	{
		if(cant > 0)
		{
			articulos_[const_cast<Articulo*>(&art)] = cant;
		}
	}
	else
	{
		if(cant > 0)
		{
			en_cesta->second = cant;
		}
		else
		{
			articulos_.erase(en_cesta);
		}
	}
}

void Usuario::vaciar_carro()
{
	auto i  = articulos_.begin();
	while(i != articulos_.end())
	{
		articulos_.erase(i);
	}
}

std::ostream& operator <<(std::ostream& os, const Usuario& u) noexcept
{
	os << u.id_ << " [" << u.clave_.clave() << "} " << u.nombre_<< " " << u.apellidos_<< std::endl;
	os << u.direccion_<< std::endl;
	os << "Tarjetas: " << std::endl;
	for(auto& i:u.tarjetas_)
	{
		os << *i.second << std::endl;
	}
	return os;
}

void mostrar_carro(std::ostream& os, const Usuario& u) noexcept
{
	os << "Carrito de la compra de " << u.id() << " [Articulos: " << u.n_articulos() << "]" << std::endl;
	os << "Cant.\tArt." << std::endl;
	os << "========================================================================================" << std::endl;
	for(auto& i:u.compra())
	{
		os << i.second << "\t" << *i.first << std::endl;
	}
	
	os << std::endl;
}




































































