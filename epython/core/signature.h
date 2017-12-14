#pragma once
// Hurts my brain to read this code
#include "typetuple.h"
#include "typetraits.h"
namespace Core {
	template<
		typename T
	>
		struct Signature {};

	template<
		typename R
	>
		struct Signature<R(*)()>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<VoidArgType> Args;
	};

	template<
		typename R, typename A0
	>
		struct Signature<R(*)(A0)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0> Args;
	};


	template<
		typename R, typename A0
	>
		struct Signature<R(A0)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0> Args;
	};


	template<
		typename R, typename A0, typename A1
	>
		struct Signature<R(*)(A0, A1)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1> Args;
	};

	template<
		typename R, typename A0, typename A1, typename A2
	>
		struct Signature<R(*)(A0, A1, A2)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2> Args;
	};

	template<
		typename R, typename A0, typename A1, typename A2, typename A3
	>
		struct Signature<R(*)(A0, A1, A2, A3)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3> Args;
	};

	template<
		typename R, typename A0, typename A1, typename A2, typename A3, typename A4
	>
		struct Signature<R(*)(A0, A1, A2, A3, A4)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4> Args;
	};

	template<
		typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5
	>
		struct Signature<R(*)(A0, A1, A2, A3, A4, A5)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5> Args;
	};

	template<
		typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
		typename A6
	>
		struct Signature<R(*)(A0, A1, A2, A3, A4, A5, A6)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5, A6> Args;
	};

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
		typename A6, typename A7
	>
		struct Signature<R(*)(A0, A1, A2, A3, A4, A5, A6, A7)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5, A6, A7> Args;
	};

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
		typename A6, typename A7, typename A8
	>
		struct Signature<R(*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
	{
		typedef NullTupleElement* ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5, A6, A7, A8> Args;
	};

	template<
		class C, typename R
	>
		struct Signature<R(C::*)()>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<NullTupleElement> Args;
	};


	template<
		class C, typename R, typename A0
	>
		struct Signature<R(C::*)(A0)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0> Args;
	};


	template<
		class C, typename R, typename A0, typename A1
	>
		struct Signature<R(C::*)(A0, A1)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1> Args;
	};

	template<
		class C, typename R, typename A0, typename A1, typename A2
	>
		struct Signature<R(C::*)(A0, A1, A2)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2> Args;
	};

	template<
		class C, typename R, typename A0, typename A1, typename A2, typename A3
	>
		struct Signature<R(C::*)(A0, A1, A2, A3)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3> Args;
	};

	template<
		class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4
	>
		struct Signature<R(C::*)(A0, A1, A2, A3, A4)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4> Args;
	};

	template<
		class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4,
		typename A5
	>
		struct Signature<R(C::*)(A0, A1, A2, A3, A4, A5)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5> Args;
	};

	template<
		class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4,
		typename A5, typename A6
	>
		struct Signature<R(C::*)(A0, A1, A2, A3, A4, A5, A6)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5, A6> Args;
	};

	template<
		class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4,
		typename A5, typename A6, typename A7
	>
		struct Signature<R(C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5, A6, A7> Args;
	};

	template<
		class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4,
		typename A5, typename A6, typename A7, typename A8
	>
		struct Signature<R(C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
	{
		typedef C ObjectType;
		typedef typename EnableIfIsArgType<R>::Type ResultType;
		typedef typename TypeTuple<A0, A1, A2, A3, A4, A5, A6, A7, A8> Args;
	};
}