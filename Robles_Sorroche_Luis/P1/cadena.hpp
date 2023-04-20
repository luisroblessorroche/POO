#ifndef _CADENA_HPP_
#define _CADENA_HPP_

#include <iostream>

class Cadena
{
	public:
		//constructores
		explicit Cadena(size_t t = 0, char c = ' ');
		Cadena(const Cadena& cad);
		Cadena(const char* cad);
		Cadena(Cadena&& cad);
		
		//operadores de asignacion
		Cadena& operator =(const Cadena& cad);
		Cadena& operator =(Cadena&& cad);
		
		//operador de conversion a cadena de bajo nivel
		operator const char*() const;//
		
		//conversor a cadena de bajo nivel
		const char* c_str() const noexcept;
		
		//metodo observador de longitud
		size_t length() const noexcept;
		
		//operador de concatenacion de cadena
		Cadena& operator +=(const Cadena& cad);
		
		//indices
		char& operator[](size_t i);
		const char& operator[](size_t i) const;
		char& at(size_t i);
		const char& at(size_t i) const;
		
		//subcadena
		Cadena substr(size_t i, size_t tam) const;
		
		//iteradores
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
		//manejo de iteradores
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_iterator cbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_iterator cend() const noexcept;
		const_reverse_iterator crend() const noexcept;

		
		//destructor
		~Cadena();
		
	private:
		char* s_;
		size_t tam_;
};


bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator ==(const Cadena& cad1, const char* cad2);
bool operator ==(const char* cad1, const Cadena& cad2);

bool operator !=(const Cadena& cad1, const Cadena& cad2);
bool operator !=(const Cadena& cad1, const char* cad2);
bool operator !=(const char* cad1, const Cadena& cad2);

bool operator <(const Cadena& cad1, const Cadena& cad2);
bool operator <(const Cadena& cad1, const char* cad2);
bool operator <(const char* cad1, const Cadena& cad2);

bool operator >(const Cadena& cad1, const Cadena& cad2);
bool operator >(const Cadena& cad1, const char* cad2);
bool operator >(const char* cad1, const Cadena& cad2);

bool operator <=(const Cadena& cad1, const Cadena& cad2);
bool operator <=(const Cadena& cad1, const char* cad2);
bool operator <=(const char* cad1, const Cadena& cad2);

bool operator >=(const Cadena& cad1, const Cadena& cad2);
bool operator >=(const Cadena& cad1, const char* cad2);
bool operator >=(const char* cad1, const Cadena& cad2);


//operador de concatenacion de cadena
Cadena operator +(const Cadena& cad1, const Cadena& cad2);


//funciones inline
inline size_t Cadena::length() const noexcept{return tam_;}
inline char& Cadena::operator[](size_t i){return s_[i];}
inline const char& Cadena::operator[](size_t i) const{return s_[i];}
inline const char* Cadena::c_str() const noexcept{return s_;}
inline Cadena::operator const char*() const{return s_;}

//------------------ENTRADA/SALIDA--------------------------
std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept;
std::istream& operator >>(std::istream& is, Cadena& cad);

//---------------ITERADORES----------------------

inline Cadena::iterator Cadena::begin() noexcept{return s_;}
inline Cadena::iterator Cadena::end() noexcept{return s_+tam_;}

inline Cadena::const_iterator Cadena::begin() const noexcept{return const_iterator(s_);}
inline Cadena::const_iterator Cadena::end() const noexcept{return const_iterator(s_+tam_);}

inline Cadena::reverse_iterator Cadena::rbegin() noexcept{return reverse_iterator(end());}
inline Cadena::reverse_iterator Cadena::rend() noexcept{return reverse_iterator(begin());}

inline Cadena::const_reverse_iterator Cadena::rbegin() const noexcept{return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::rend() const noexcept{return const_reverse_iterator(begin());}

inline Cadena::const_iterator Cadena::cbegin() const noexcept{return const_iterator(s_);}
inline Cadena::const_iterator Cadena::cend() const noexcept{return const_iterator(s_+tam_);}

inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept{return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::crend() const noexcept{return const_reverse_iterator(begin());}

namespace std
{
	template <>
	struct hash<Cadena>
	{
		size_t operator()(const Cadena& cad) const
		{
			hash<string> hs;
			const char* p = cad.c_str();
			string s(p);
			size_t res = hs(s);
			return res;
		}
	};
}

#endif
