#pragma once
#include "preprocessor.h"

struct NullType {};

template<class T, class U>
struct Typelist
{
	typedef T head;
	typedef U tail;
};

#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T2, TYPELIST_1(T1)  >
#define TYPELIST_3(T1, T2, T3) Typelist<T3, TYPELIST_2(T1, T2)  >
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T4, TYPELIST_3(T1, T2, T3)  >
#define TYPELIST_5(T1, T2, T3, T4, T5) Typelist<T5, TYPELIST_4(T1, T2, T3, T4)  >
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) Typelist<T6, TYPELIST_5(T1, T2, T3, T4, T5)  >

#define TYPELIST(...) VA_SELECT(TYPELIST, __VA_ARGS__)

typedef TYPELIST(signed char, short, int, long) SignedIntegers;