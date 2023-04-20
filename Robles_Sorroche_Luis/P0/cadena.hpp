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
		char* s_;
		size_t tam_;
};

bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator ==(const char* cad1, const char* cad2);
//bool operator !=(const Cadena& cad1, const Cadena& cad2);
//bool operator <(const Cadena& cad1, const Cadena& cad2);
//bool operator >(const Cadena& cad1, const Cadena& cad2);
//bool operator <=(const Cadena& cad1, const Cadena& cad2);
//bool operator >=(const Cadena& cad1, const Cadena& cad2);

Cadena operator +(const Cadena& cad1, const Cadena& cad2);

inline size_t Cadena::length() const noexcept
{
	return tam_;
}

inline char& Cadena::operator[](size_t i)
{
	return s_[i];
}

inline const char& Cadena::operator[](size_t i) const
{
	return s_[i];
}

inline Cadena::operator const char*() const
{
	return s_;
}

#endif 
