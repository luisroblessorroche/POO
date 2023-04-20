#ifndef _FECHA_HPP_
#define _FECHA_HPP_

#include <iostream>

class Fecha
{
	public:
		explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
		Fecha(const Fecha& f) = default;
		Fecha(const char* c);
		
		Fecha& operator = (const Fecha& f) = default;
		
		const char* cadena() const;
		
		static const int AnnoMinimo = 1902;
		static const int AnnoMaximo = 2037;
		
		class Invalida
		{
			public:
				Invalida(const char* inf): motivo{inf}{}
				const char* por_que() const {return motivo;}
			private:
				const char* motivo;
		};
		
		int dia() const noexcept;
		int mes() const noexcept;
		int anno() const noexcept;
		
		Fecha& operator ++();
		Fecha operator ++(int);
		Fecha& operator --();
		Fecha operator --(int);
		Fecha& operator +=(int i);
		Fecha& operator -=(int i);
		
		Fecha operator +(int i) const;
		Fecha operator -(int i) const;
		
		~Fecha() = default;
		
	private:
		int d;
		int m;
		int a;
		void comprobar_validez();
		int ultimo_dia() const;
};

bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);


inline int Fecha::dia() const noexcept{return d;}
inline int Fecha::mes() const noexcept{return m;}
inline int Fecha::anno() const noexcept{return a;}

std:: ostream& operator <<(std::ostream& os, const Fecha& f) noexcept;
std::istream& operator >>(std::istream& is, Fecha& f);

#endif
