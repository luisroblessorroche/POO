#include "articulo.hpp"


Articulo::Articulo(Cadena r, Cadena t, Fecha f, double p, size_t e): 
referencia_{r}, titulo_{t}, f_publi_{f}, precio_{p}, stock_{e}{}


std::ostream& operator <<(std::ostream& os, const Articulo& art) noexcept
{
	std::locale::global(std::locale(""));
	os << "[" <<art.referencia() << "] " << "\"" << art.titulo() << "\", " <<
	art.f_publi().anno() << ". " << std::fixed << std::setprecision(2) <<
	art.precio() << " \u20AC" << std::endl;
	return os;
}
