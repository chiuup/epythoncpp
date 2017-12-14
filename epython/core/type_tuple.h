#pragma once
namespace Core {
	struct NullTupleElement {};
	struct EmptyType {};

	namespace Private {
		template<class TTuple, class T> struct IndexOfHelper;
		template <class TTuple, unsigned int index> struct TypeAtHelper;
		template <class TTuple, unsigned int index, typename DefaultType> struct TypeAtNonStrictHelper;
	}

	template<class T, class U>
	struct TypeTupleElement
	{
		typedef T Head;
		typedef U Tail;
	};

	namespace Private {
		template<class T>
		struct IndexOfHelper<NullTupleElement, T> {
			static const int value = -1;
		};

		template<class T, class Tail>
		struct IndexOfHelper<TypeTupleElement<T, Tail>, T> {
			static const int value = 0;
		};

		template<class Head, class Tail, class T>
		struct IndexOfHelper<TypeTupleElement<Head, Tail>, T> {
		private:
			static const int temp = IndexOfHelper<Tail, T>::value;
		public:
			static const int value = temp == -1 ? -1 : 1 + temp;
		};


		template <class Head, class Tail>
		struct TypeAtHelper<TypeTupleElement<Head, Tail>, 0>
		{
			typedef Head Type;
		};

		template <class Head, class Tail, unsigned int i>
		struct TypeAtHelper<TypeTupleElement<Head, Tail>, i>
		{
			typedef typename TypeAtHelper<Tail, i - 1>::Type Type;
		};

		template <class TTuple, unsigned int index, typename DefaultType = NullTupleElement>
		struct TypeAtNonStrictHelper
		{
			typedef DefaultType Type;
		};

		template <class Head, class Tail, typename DefaultType>
		struct TypeAtNonStrictHelper<TypeTupleElement<Head, Tail>, 0, DefaultType>
		{
			typedef Head Type;
		};

		template <class Head, class Tail, unsigned int i, typename DefaultType>
		struct TypeAtNonStrictHelper<TypeTupleElement<Head, Tail>, i, DefaultType>
		{
			typedef typename
				TypeAtNonStrictHelper<Tail, i - 1, DefaultType>::Type Type;
		};
	}

	template<
		typename T0 = NullTupleElement, typename T1 = NullTupleElement, typename T2 = NullTupleElement,
		typename T3 = NullTupleElement, typename T4 = NullTupleElement, typename T5 = NullTupleElement,
		typename T6 = NullTupleElement, typename T7 = NullTupleElement, typename T8 = NullTupleElement
	>
		struct TypeTuple
	{
	private:
		typedef typename TypeTuple<T1, T2, T3, T4, T5, T6, T7, T8>::Result TailResult;
	public:
		typedef TypeTupleElement<T0, TailResult> Result;

		template<class T>
		struct IndexOf {
			static const int value = Private::IndexOfHelper<Result, T>::value;
		};

		template<unsigned int i>
		struct TypeAt {
			typedef typename Private::TypeAtHelper<Result, i>::Type Type;
		};

		template<unsigned int i>
		struct TypeAtNonStrict {
			typedef typename Private::TypeAtNonStrictHelper<Result, i, EmptyType>::Type Type;
		};

		template<unsigned int i>
		struct ArgTypeAt {
		private:
			typedef typename Private::TypeAtHelper<Result, i>::Type TempType;
		public:
			typedef typename EnableIfIsArgType<TempType>::Type Type;
		};

		template<unsigned int i>
		struct ArgTypeAtNonStrict {
		private:
			typedef typename Private::TypeAtNonStrictHelper<Result, i, EmptyType*>::Type TempType;
		public:
			typedef typename EnableIfIsArgType<TempType>::Type Type;
		};
	};

	template<>
	struct TypeTuple<>
	{
		typedef NullTupleElement Result;
	};
}