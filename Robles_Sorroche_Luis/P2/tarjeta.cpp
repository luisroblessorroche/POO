#include "tarjeta.hpp"

std::set<Numero> Tarjeta::tarjetas_;
bool luhn(const Cadena&);





//------------------------Metodos de la clase Numero----------------------------

Numero::Numero(const Cadena& cad)
{
	Cadena n;
	for(auto x:cad)
	{
		if(!isspace(x))
		{
			if(!isdigit(x))
			{
				throw Numero::Incorrecto(Razon::DIGITOS);
			}
			else
			{
				n +=Cadena(1,x);
			}
		}
	}
	
	if(n.length() < 13 || n.length() >19)
	{
		throw Numero::Incorrecto(Razon::NO_VALIDO);
	}
	else
	{
		if(!luhn(n))
		{
			throw Numero::Incorrecto(Razon::NO_VALIDO);
		}
		else
		{
			numero_ = n;
		}
	}
}


//----------------Metodos de la clase tarjeta---------------------

Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f):numero_{n}, titular_{&u},
caducidad_{f}, activa_{true}
{
	Fecha hoy;
	if(hoy > f)
	{
		throw Tarjeta::Caducada(f);
	}
	else
	{
		if(!tarjetas_.insert(n).second)
		{
			throw Tarjeta::Num_duplicado(n);
			
		}
		else
		{
			titular_->es_titular_de(*this);
		}
	}
}


Tarjeta::~Tarjeta()
{
	if(titular_)
	{
		titular_->no_es_titular_de(*this);
	}
	tarjetas_.erase(numero_);
}


Tarjeta::Tipo Tarjeta::tipo() const noexcept
{
	Cadena primeros(2);
	primeros[0] = numero_[0];
	primeros[1] = numero_[1];
	
	if(primeros == "34" || primeros == "37")
	{
		return Tarjeta::AmericanExpress;
	}
	else
	{
		switch(primeros[0])
		{
			case '3':
				return Tarjeta::JCB;
				break;
			case '4':
				return Tarjeta::VISA;
				break;
			case '5':
				return Tarjeta::Mastercard;
				break;
			case '6':
				return Tarjeta::Maestro;
				break;
			default:
				return Tarjeta::Otro;
		}
	}
}


void Tarjeta::anula_titular()
{
	activa_  = false;
	const_cast<Usuario*&>(titular_) = nullptr;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tip)
{
	switch(tip)
	{
		case Tarjeta::Otro:
			os << "Otro";
			break;
		case Tarjeta::VISA:
			os << "VISA";
			break;
		case Tarjeta::Mastercard:
			os << "Mastercard";
			break;
		case Tarjeta::Maestro:
			os << "Maestro";
			break;
		case Tarjeta::JCB:
			os << "JCB";
			break;
		case Tarjeta::AmericanExpress:
			os << "AmericanExpress";
			break;
		default:
			os << "Error Tipo Tarjeta";
	}
	return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t) noexcept
{
	os << " " << std::setfill('-') << std::setw(30) << " " << std::endl;
	os << "/			      \\" << std::endl;
	os << "| " << std::left << std::setfill(' ') << std::setw(28) << t.tipo() << "|" << std::endl;
	os << "| " << std::setfill(' ') << std::setw(28) << t.numero() << "|" << std::endl;
	Cadena cad_mostrar = t.titular()->nombre() + " " + t.titular()->apellidos();
	
	for(auto& x:cad_mostrar)
	{
		if(islower(x))
		{
			x = toupper(x);
		}
	}
	os << "| " << std::setfill(' ') << std::setw(28) << cad_mostrar << "|" << std::endl;
	os << std::right << "| Caduca: " << std::setfill('0') << std::setw(2)
	<< (t.caducidad().mes()) << "/" << std::setw(2) << (t.caducidad().anno()%100)
	<< std::setfill(' ') << std::setw(16) << "|" << std::endl;
	
	os << "\\			      /" << std::endl;
	os << " -----------------------------" << std::endl;
	return os;
}














