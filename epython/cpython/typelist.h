#pragma once
#include "preprocessor.h"
namespace TL {
	struct NullType {};

	template<class T, class U>
	struct Typelist
	{
		typedef T Head;
		typedef U Tail;
	};
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) \
 Typelist<T1, TYPELIST_3(T2, T3, T4) > 
#define TYPELIST_5(T1, T2, T3, T4, T5) \
 Typelist<T1, TYPELIST_4(T2, T3, T4, T5) > 
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) \
 Typelist<T1, TYPELIST_5(T2, T3, T4, T5, T6) > 

#define TYPELIST(...) VA_SELECT(TYPELIST, __VA_ARGS__)

	template<class TList, class T> struct IndexOf;
	template<class T>
	struct IndexOf<NullType, T> {
		enum { value = -1 };
	};

	template<class T, class Tail>
	struct IndexOf<Typelist<T, Tail>, T> {
		enum { value = 0 };
	};

	template<class Head, class Tail, class T>
	struct IndexOf<Typelist<Head, Tail>, T> {
	private:
		enum { temp = IndexOf<Tail, T>::value };
	public:
		enum { value = temp == -1 ? -1 : 1 + temp };
	};


	typedef TYPELIST(signed char, short, int, long, long long) SignedIntTypelist;
	typedef TYPELIST(unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long) UnsignedIntTypelist;
	typedef TYPELIST(float, double, long double) FloatTypelist;
	typedef TYPELIST(bool) BoolTypeList;
	typedef TYPELIST(const char*, char*) StringTypeList;
	typedef TYPELIST(void) VoidTypeList;
}