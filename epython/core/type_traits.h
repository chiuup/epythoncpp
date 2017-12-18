#pragma once
namespace Core {
	template<bool, class T0, class T1>
	struct If;

	template<class T, T val>
	struct ConstantType
	{
		typedef T ValueType;
		typedef ConstantType<T, val> Type;
		static const T value = val;
	};

	typedef ConstantType<bool, true> TrueType;
	typedef ConstantType<bool, false> FalseType;

	template <class T0, class T1> struct IsSame :public FalseType {};
	template <class T> struct IsSame<T, T> :public TrueType {};

	template<class T = void> struct IsSigned : public FalseType {};
	template<> struct IsSigned<signed char> : public TrueType {};
	template<> struct IsSigned<short> : public TrueType {};
	template<> struct IsSigned<int> : public TrueType {};
	template<> struct IsSigned<long> : public TrueType {};
	template<> struct IsSigned<long long> : public TrueType {};
	template<class T> struct IsSigned<const T> :public IsSigned<T> {};
	template<class T> struct IsSigned<volatile T> :public IsSigned<T> {};
	template<class T> struct IsSigned<const volatile T> :public IsSigned<T> {};

	template<class T = void> struct IsUnsigned : public FalseType {};
	template<> struct IsUnsigned<unsigned char> : public TrueType {};
	template<> struct IsUnsigned<unsigned short> : public TrueType {};
	template<> struct IsUnsigned<unsigned int> : public TrueType {};
	template<> struct IsUnsigned<unsigned long> : public TrueType {};
	template<> struct IsUnsigned<unsigned long long> : public TrueType {};
	template<class T> struct IsUnsigned<const T> :public IsUnsigned<T> {};
	template<class T> struct IsUnsigned<volatile T> :public IsUnsigned<T> {};
	template<class T> struct IsUnsigned<const volatile T> :public IsUnsigned<T> {};

	template<class T = void> struct IsChar :public FalseType {};
	template<> struct IsChar<char> : public TrueType {};
	template<> struct IsChar<unsigned char> : public TrueType {};
	template<> struct IsChar<signed char> : public TrueType {};
	template<class T> struct IsChar<const T> :public IsChar<T> {};
	template<class T> struct IsChar<volatile T> :public IsChar<T> {};
	template<class T> struct IsChar<const volatile T> :public IsChar<T> {};


	template<class T = void> struct IsInteger :
		public If<IsSigned<T>::value || IsUnsigned<T>::value || IsChar<T>::value, TrueType, FalseType>::Type {};

	template<class T = void> struct IsFloat :public FalseType {};
	template<> struct IsFloat<float> :public TrueType {};
	template<> struct IsFloat<double> :public TrueType {};
	template<> struct IsFloat<long double> :public TrueType {};
	template<class T> struct IsFloat<const T> :public IsFloat<T> {};
	template<class T> struct IsFloat<volatile T> :public IsFloat<T> {};
	template<class T> struct IsFloat<const volatile T> :public IsFloat<T> {};

	template<class T = void> struct IsArithmetic :
		public If<IsInteger<T>::value || IsFloat<T>::value, TrueType, FalseType>::Type {};

	template<class T> struct IsPointer : public FalseType {};
	template<class T> struct IsPointer<T*> : public TrueType {};
	template<class T> struct IsPointer<T* const> : public TrueType {};
	template<class T> struct IsPointer<T* const volatile> : public TrueType {};
	template<class T> struct IsPointer<T* volatile> : public TrueType {};

	template<class T> struct IsReference : public FalseType {};
	template<class T> struct IsReference<T&> : public TrueType {};

	template<class T> struct IsVoid : public FalseType {};
	template<> struct IsVoid<void> :public TrueType {};

	template<class T> struct IsString : public FalseType {};
	template<> struct IsString<char*> : public TrueType {};
	template<> struct IsString<const char*> : public TrueType {};
	template<> struct IsString<char* const> : public TrueType {};
	template<> struct IsString<char* const volatile> : public TrueType {};
	template<> struct IsString<char* volatile> : public TrueType {};
	template<> struct IsString<const unsigned char*> : public TrueType {};
	template<> struct IsString<unsigned char*> : public TrueType {};
	template<> struct IsString<unsigned char* const> : public TrueType {};
	template<> struct IsString<unsigned char* const volatile> : public TrueType {};
	template<> struct IsString<unsigned char* volatile> : public TrueType {};

	template<class T> struct IsBool : public FalseType {};
	template<> struct IsBool<bool> :public TrueType {};

	struct VoidArgType {};

	template<class T> struct IsArgType :
		public If<IsArithmetic<T>::value || IsPointer<T>::value || IsReference<T>::value || IsVoid<T>::value || IsSame<VoidArgType, T>::value, TrueType, FalseType>::Type {};

	template<class T> struct IsMemberFunctionPointer : public FalseType {};
	template<class T0, class T1> struct IsMemberFunctionPointer<T0 T1::*> : public TrueType {};

	template<class T>
	struct IsFunctionPointer : public FalseType {};
	template<class R>
	struct IsFunctionPointer<R(*)()> : public TrueType {};
	template<class R, class A0>
	struct IsFunctionPointer < R(*)(A0) > : public TrueType {};
	template<class R, class A0, class A1>
	struct IsFunctionPointer < R(*)(A0, A1) > : public TrueType {};
	template<class R, class A0, class A1, class A2>
	struct IsFunctionPointer < R(*)(A0, A1, A2) > : public TrueType {};
	template<class R, class A0, class A1, class A2, class A3>
	struct IsFunctionPointer<R(*)(A0, A1, A2, A3)> : public TrueType {};
	template<class R, class A0, class A1, class A2, class A3, class A4>
	struct IsFunctionPointer<R(*)(A0, A1, A2, A3, A4)> : public TrueType {};
	template<class R, class A0, class A1, class A2, class A3, class A4, class A5>
	struct IsFunctionPointer<R(*)(A0, A1, A2, A3, A4, A5)> : public TrueType {};
	template<class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6>
	struct IsFunctionPointer<R(*)(A0, A1, A2, A3, A4, A5, A6)> : public TrueType {};
	template<class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	struct IsFunctionPointer<R(*)(A0, A1, A2, A3, A4, A5, A6, A7)> : public TrueType {};
	template<class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	struct IsFunctionPointer<R(*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)> : public TrueType {};

	template<bool, class T = void> struct EnableIf {};
	template<class T> struct EnableIf<true, T> { typedef T Type; };
	template<class T> struct EnableIfIsArgType : public EnableIf<IsArgType<T>::value, T> {};

	template<bool, class T0, class T1> struct If { typedef T0 Type; };
	template<class T0, class T1> struct If<false, T0, T1> { typedef T1 Type; };
}