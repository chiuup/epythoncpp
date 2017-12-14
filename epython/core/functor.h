#pragma once
#include "signature.h"
#include "typetraits.h"
namespace Core {
	namespace Private {
		template<typename F>
		class MemberFunctionInvoker
		{
		public:
			typedef typename Signature<F>::ObjectType ObjectType;
			typedef typename Signature<F>::ResultType ResultType;
			typedef typename Signature<F>::Args Args;
			typedef typename Args::template ArgTypeAtNonStrict<0>::Type ArgType0;
			typedef typename Args::template ArgTypeAtNonStrict<1>::Type ArgType1;
			typedef typename Args::template ArgTypeAtNonStrict<2>::Type ArgType2;
			typedef typename Args::template ArgTypeAtNonStrict<3>::Type ArgType3;
			typedef typename Args::template ArgTypeAtNonStrict<4>::Type ArgType4;
			typedef typename Args::template ArgTypeAtNonStrict<5>::Type ArgType5;
			typedef typename Args::template ArgTypeAtNonStrict<6>::Type ArgType6;
			typedef typename Args::template ArgTypeAtNonStrict<7>::Type ArgType7;
			typedef typename Args::template ArgTypeAtNonStrict<8>::Type ArgType8;

			MemberFunctionInvoker(ObjectType* obj, F func) :obj_(obj), func_(func) {};

			ResultType operator()() {
				return (obj_->*func_)();
			}
			ResultType operator()(ArgType0 a0) {
				return (obj_->*func_)(a0);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1) {
				return (obj_->*func_)(a0, a1);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2) {
				return (obj_->*func_)(a0, a1, a2);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3) {
				return (obj_->*func_)(a0, a1, a2, a3);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4) {
				return (obj_->*func_)(a0, a1, a2, a3, a4);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5) {
				return (obj_->*func_)(a0, a1, a2, a3, a4, a5);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5, ArgType6 a6) {
				return (obj_->*func_)(a0, a1, a2, a3, a4, a5, a6);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5, ArgType6 a6, ArgType7 a7) {
				return (obj_->*func_)(a0, a1, a2, a3, a4, a5, a6, a7);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5, ArgType6 a6, ArgType7 a7, ArgType8 a8) {
				return (obj_->*func_)(a0, a1, a2, a3, a4, a5, a6, a7, a8);
			}
		private:
			ObjectType * obj_;
			F func_;
		};

		template<typename F>
		class FunctionInvoker
		{
		public:
			typedef typename Signature<F>::ObjectType ObjectType;
			typedef typename Signature<F>::ResultType ResultType;
			typedef typename Signature<F>::Args Args;
			typedef typename Args::template ArgTypeAtNonStrict<0>::Type ArgType0;
			typedef typename Args::template ArgTypeAtNonStrict<1>::Type ArgType1;
			typedef typename Args::template ArgTypeAtNonStrict<2>::Type ArgType2;
			typedef typename Args::template ArgTypeAtNonStrict<3>::Type ArgType3;
			typedef typename Args::template ArgTypeAtNonStrict<4>::Type ArgType4;
			typedef typename Args::template ArgTypeAtNonStrict<5>::Type ArgType5;
			typedef typename Args::template ArgTypeAtNonStrict<6>::Type ArgType6;
			typedef typename Args::template ArgTypeAtNonStrict<7>::Type ArgType7;
			typedef typename Args::template ArgTypeAtNonStrict<8>::Type ArgType8;

			FunctionInvoker(F func) : func_(func) {};

			ResultType operator()() {
				return func_();
			}
			ResultType operator()(ArgType0 a0) {
				return func_(a0);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1) {
				return func_(a0, a1);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2) {
				return func_(a0, a1, a2);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3) {
				return func_(a0, a1, a2, a3);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4) {
				return func_(a0, a1, a2, a3, a4);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5) {
				return func_(a0, a1, a2, a3, a4, a5);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5, ArgType6 a6) {
				return func_(a0, a1, a2, a3, a4, a5, a6);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5, ArgType6 a6, ArgType7 a7) {
				return func_(a0, a1, a2, a3, a4, a5, a6, a7);
			}
			ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
				ArgType5 a5, ArgType6 a6, ArgType7 a7, ArgType8 a8) {
				return func_(a0, a1, a2, a3, a4, a5, a6, a7, a8);
			}
		private:
			F func_;
		};

		template<typename F>
		struct FunctorInvokerSelect
		{
			typedef typename If<IsMemberFunctionPointer<F>::Value,
				MemberFunctionInvoker<F>,
				FunctionInvoker<F>
			>::Type InvokerType;
		};
	}

	template<typename F>
	class Functor
	{
	private:
		typedef typename Private::FunctorInvokerSelect<F>::InvokerType InvokerType;
		typedef typename InvokerType::ObjectType ObjectType;
		typedef typename InvokerType::ResultType ResultType;
		typedef typename InvokerType::Args Args;
		typedef typename InvokerType::ArgType0 ArgType0;
		typedef typename InvokerType::ArgType1 ArgType1;
		typedef typename InvokerType::ArgType2 ArgType2;
		typedef typename InvokerType::ArgType3 ArgType3;
		typedef typename InvokerType::ArgType4 ArgType4;
		typedef typename InvokerType::ArgType5 ArgType5;
		typedef typename InvokerType::ArgType6 ArgType6;
		typedef typename InvokerType::ArgType7 ArgType7;
		typedef typename InvokerType::ArgType8 ArgType8;
	public:
		Functor(ObjectType* obj, F func) :invoker_(obj, func) {};
		Functor(F func) :invoker_(func) {};
		virtual ~Functor() { printf("deleted\n"); };
		ResultType operator()() {
			return invoker_();
		}
		ResultType operator()(ArgType0 a0) {
			return invoker_(a0);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1) {
			return invoker_(a0, a1);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2) {
			return invoker_(a0, a1, a2);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3) {
			return invoker_(a0, a1, a2, a3);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4) {
			return invoker_(a0, a1, a2, a3, a4);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
			ArgType5 a5) {
			return invoker_(a0, a1, a2, a3, a4, a5);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
			ArgType5 a5, ArgType6 a6) {
			return invoker_(a0, a1, a2, a3, a4, a5, a6);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
			ArgType5 a5, ArgType6 a6, ArgType7 a7) {
			return invoker_(a0, a1, a2, a3, a4, a5, a6, a7);
		}
		ResultType operator()(ArgType0 a0, ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4,
			ArgType5 a5, ArgType6 a6, ArgType7 a7, ArgType8 a8) {
			return invoker_(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		}
	private:
		InvokerType invoker_;
	};

	template<typename F>
	inline Functor<F> MakeFunctor(F f) {
		return Functor<F>(f);
	}

	template<typename F>
	inline Functor<F> MakeFunctor(typename Signature<F>::ObjectType* obj, F f) {
		return Functor<F>(obj, f);
	}

	class LazyFunctor
	{
	public:
		LazyFunctor(void *func) :func_(func) {};

		template<typename F>
		typename Signature<F>::ResultType Invoke(typename Signature<F>::Args::template ArgTypeAtNonStrict<0>::Type a0) {
			F f = (F)func_;
			return f(a0);
		}
	private:
		void* func_;
	};
}