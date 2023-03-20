#ifndef _CADENA_HPP_
#define _CADENA_HPP_

#include <iostream>

class Cadena
{
	public:
		explicit Cadena(size_t t = 0, char c = ' ');
		Cadena(const Cadena& cad);
		Cadena(const char* cad);
		Cadena& operator =(const Cadena&);
		operator const char*() const;
		
		size_t length() const noexcept;
		
		Cadena& operator +=(const Cadena& cad);
		
		char& operator[](size_t i);
		const char& operator[](size_t i) const;
		char& at(size_t i);
		const char& at(size_t i) const;
		
		Cadena substr(size_t i, size_t tam) const;
		
		~Cadena();
		
	private:
		char* s;
		size_t tam;
};

bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator !=(const Cadena& cad1, const Cadena& cad2);
bool operator <(const Cadena& cad1, const Cadena& cad2);
bool operator >(const Cadena& cad1, const Cadena& cad2);
bool operator <=(const Cadena& cad1, const Cadena& cad2);
bool operator >=(const Cadena& cad1, const Cadena& cad2);

Cadena operator +(const Cadena& cad1, const Cadena& cad2);

inline size_t Cadena::length() const noexcept{return tam;}
inline char& Cadena::operator[](size_t i){return s[i];}
inline const char& Cadena::operator[](size_t i) const{return s[i];}
inline Cadena::operator const char*() const{return s;}

#endif 
