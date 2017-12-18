#pragma once
#include <Python.h>
#include "core\signature.h"
#include "dict.h"

namespace CPython {
	namespace Private {
		struct FunctionInvokerBase {
			virtual ~FunctionInvokerBase() {}
			virtual PyObject* operator()(PyObject* self, PyObject* args, PyObject* kwargs) = 0;
		};

		template<typename F>
		struct VoidFunctionInvokerImpl {
			VoidFunctionInvokerImpl(F f) :func_(f) {}
			virtual ~VoidFunctionInvokerImpl() {}

			template<unsigned int arity>
			inline PyObject* Invoke(PyObject* self, PyObject* args, PyObject* kwargs);

			template<>
			inline PyObject* Invoke<0>(PyObject* self, PyObject* args, PyObject* kwargs) {
				func_();
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<1>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				func_(a0);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<2>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				func_(a0, a1);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<3>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				func_(a0, a1, a2);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<4>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				func_(a0, a1, a2, a3);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<5>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				func_(a0, a1, a2, a3, a4);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<6>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				func_(a0, a1, a2, a3, a4, a5);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<7>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				ArgType6 a6 = argTuple.Get<ArgType6>(6);
				func_(a0, a1, a2, a3, a4, a5, a6);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<8>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				ArgType6 a6 = argTuple.Get<ArgType6>(6);
				ArgType7 a7 = argTuple.Get<ArgType7>(7);
				func_(a0, a1, a2, a3, a4, a5, a6, a7);
				Py_RETURN_NONE;
			}

			template<>
			inline PyObject* Invoke<9>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				ArgType6 a6 = argTuple.Get<ArgType6>(6);
				ArgType7 a7 = argTuple.Get<ArgType7>(7);
				ArgType8 a8 = argTuple.Get<ArgType8>(8);
				func_(a0, a1, a2, a3, a4, a5, a6, a7, a8);
				Py_RETURN_NONE;
			}
		private:
			F func_;

			typedef typename Core::Signature<F>::ObjectType ObjectType;
			typedef typename Core::Signature<F>::ResultType ResultType;
			typedef typename Core::Signature<F>::Args Args;
			typedef typename Args::template ArgTypeAtNonStrict<0>::Type ArgType0;
			typedef typename Args::template ArgTypeAtNonStrict<1>::Type ArgType1;
			typedef typename Args::template ArgTypeAtNonStrict<2>::Type ArgType2;
			typedef typename Args::template ArgTypeAtNonStrict<3>::Type ArgType3;
			typedef typename Args::template ArgTypeAtNonStrict<4>::Type ArgType4;
			typedef typename Args::template ArgTypeAtNonStrict<5>::Type ArgType5;
			typedef typename Args::template ArgTypeAtNonStrict<6>::Type ArgType6;
			typedef typename Args::template ArgTypeAtNonStrict<7>::Type ArgType7;
			typedef typename Args::template ArgTypeAtNonStrict<8>::Type ArgType8;

		};

		template<typename F>
		struct FunctionInvokerImpl {
			FunctionInvokerImpl(F f) :func_(f) {}
			virtual ~FunctionInvokerImpl() {}

			template<unsigned int arity>
			inline PyObject* Invoke(PyObject* self, PyObject* args, PyObject* kwargs);

			template<>
			inline PyObject* Invoke<0>(PyObject* self, PyObject* args, PyObject* kwargs) {
				return Converter<ResultType>::ToPyObject(func_());
			}

			template<>
			inline PyObject* Invoke<1>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				return Converter<ResultType>::ToPyObject(func_(a0));
			}

			template<>
			inline PyObject* Invoke<2>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				return Converter<ResultType>::ToPyObject(func_(a0, a1));
			}

			template<>
			inline PyObject* Invoke<3>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				return Converter<ResultType>::ToPyObject(func_(a0, a1, a2));
			}

			template<>
			inline PyObject* Invoke<4>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				return Converter<ResultType>::ToPyObject(func_(a0, a1, a2, a3));
			}

			template<>
			inline PyObject* Invoke<5>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				return Converter<ResultType>::ToPyObject(func_(a0, a1, a2, a3, a4));
			}

			template<>
			inline PyObject* Invoke<6>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				return Converter<ResultType>::ToPyObject(func_(a0, a1, a2, a3, a4, a5));
			}

			template<>
			inline PyObject* Invoke<7>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				ArgType6 a6 = argTuple.Get<ArgType6>(6);
				return Converter<ResultType>::ToPyObject(func_(a0, a1, a2, a3, a4, a5, a6));
			}

			template<>
			inline PyObject* Invoke<8>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				ArgType6 a6 = argTuple.Get<ArgType6>(6);
				ArgType7 a7 = argTuple.Get<ArgType7>(7);
				return Converter<ResultType>::ToPyObject(func_(a0, a1, a2, a3, a4, a5, a6, a7));
			}

			template<>
			inline PyObject* Invoke<9>(PyObject* self, PyObject* args, PyObject* kwargs) {
				Tuple argTuple = Tuple(BorrowedReference(args));
				ArgType0 a0 = argTuple.Get<ArgType0>(0);
				ArgType1 a1 = argTuple.Get<ArgType1>(1);
				ArgType2 a2 = argTuple.Get<ArgType2>(2);
				ArgType3 a3 = argTuple.Get<ArgType3>(3);
				ArgType4 a4 = argTuple.Get<ArgType4>(4);
				ArgType5 a5 = argTuple.Get<ArgType5>(5);
				ArgType6 a6 = argTuple.Get<ArgType6>(6);
				ArgType7 a7 = argTuple.Get<ArgType7>(7);
				ArgType8 a8 = argTuple.Get<ArgType8>(8);
				return Converter<ResultType>::ToPyObject(func_(a0, a1, a2, a3, a4, a5, a6, a7, a8));
			}
		private:
			F func_;

			typedef typename Core::Signature<F>::ObjectType ObjectType;
			typedef typename Core::Signature<F>::ResultType ResultType;
			typedef typename Core::Signature<F>::Args Args;
			typedef typename Args::template ArgTypeAtNonStrict<0>::Type ArgType0;
			typedef typename Args::template ArgTypeAtNonStrict<1>::Type ArgType1;
			typedef typename Args::template ArgTypeAtNonStrict<2>::Type ArgType2;
			typedef typename Args::template ArgTypeAtNonStrict<3>::Type ArgType3;
			typedef typename Args::template ArgTypeAtNonStrict<4>::Type ArgType4;
			typedef typename Args::template ArgTypeAtNonStrict<5>::Type ArgType5;
			typedef typename Args::template ArgTypeAtNonStrict<6>::Type ArgType6;
			typedef typename Args::template ArgTypeAtNonStrict<7>::Type ArgType7;
			typedef typename Args::template ArgTypeAtNonStrict<8>::Type ArgType8;

		};

		template<typename F>
		struct FunctionInvoker : FunctionInvokerBase {
			FunctionInvoker(F f) : impl_(InvokerImpl(f)) {}
			virtual ~FunctionInvoker() {}

			virtual PyObject* operator()(PyObject* self, PyObject* args, PyObject* kwargs) {
				return impl_.Invoke<Core::Signature<F>::arity>(self, args, kwargs);
			}
		private:
			typedef typename Core::If< Core::IsVoid<typename Core::Signature<F>::ResultType>::value,
				VoidFunctionInvokerImpl<F>, FunctionInvokerImpl<F>>::Type InvokerImpl;
			InvokerImpl impl_;
		};
	}

	struct Function : PyObject {
		Function(Private::FunctionInvokerBase* invoker);
		~Function() {
			delete invoker_; 
		}

		inline PyObject* operator()(PyObject* self, PyObject* args, PyObject* kwargs) {
			return invoker_->operator()(self, args, kwargs);
		}

		inline void AddToModule(const Object& module, const char* name, const char* doc) {
			assert(name != NULL);
			name_ = Object::From<const char*>(name);
			if (doc) doc_ = Object::From<const char*>(doc);
			else doc_ = Object::From<const char*>("");
			module_ = Object(module);

			Dict moduleDict = module_.GetAttr("__dict__");
			moduleDict.Set(name_, Object(BorrowedReference(this)));
		}

		inline const Object& doc() const {
			return doc_;
		}

		inline const Object& name() const {
			return name_;
		}

		inline const Object& module() const {
			return module_;
		}
	private:
		Private::FunctionInvokerBase* invoker_;
		Object name_;
		Object module_;
		Object doc_;
	};

	template<typename F>
	inline Function* MakeFunction(F func) {
		return new Function(new Private::FunctionInvoker<F>(func));
	}

}