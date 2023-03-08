#ifndef _FECHA_HPP_
#define _FECHA_HPP_

class Fecha
{
	public:
		explicit Fecha(int d = 0, int m = 0, int a =0);
		Fecha(const Fecha& f) = default;
		Fecha(const char* c);
	private:
		int dia;
		int mes;
		int anno;
		void comprobar_constructor_correcto();
		
}
