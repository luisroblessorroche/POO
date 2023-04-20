#include "articulo.hpp"

std::ostream& operator <<(std::ostream& os, const Articulo& art) noexcept
{
	std::locale::global(std::locale(""));
	os << "[" <<art.referencia() << "] " << "\"" << art.titulo() << "\", " <<
	art.f_publi().anno() << ". " << std::fixed << std::setprecision(2) <<
	art.precio() << " \u20AC" << std::endl;
	return os;
}
