#pragma once
#include <Python.h>
#include "preprocessor.h"
#include "cpyconverter.h"

template<typename R>
struct CPyFunctionHelper0 {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		typedef R(*OriginalSignature)();
		OriginalSignature f = (OriginalSignature)F;
		R r = f(a1);
		return CPyConverter<R>::ConvertToPyObject(r);
	}
};

template<>
struct CPyFunctionHelper0<void> {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		typedef void(*OriginalSignature)(void);
		OriginalSignature f = (OriginalSignature)F;
		f();
		Py_RETURN_NONE;
	}
};

template<typename R, typename T1>
struct CPyFunctionHelper1 {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		typedef R(*OriginalSignature)(T1);
		OriginalSignature f = (OriginalSignature)F;
		R r = f(a1);
		return CPyConverter<R>::ConvertToPyObject(r);
	}
};


template<typename T1>
struct CPyFunctionHelper1<void, T1> {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		typedef void(*OriginalSignature)(T1);
		OriginalSignature f = (OriginalSignature)F;
		f(a1);
		Py_RETURN_NONE;
	}
};


template<typename R, typename T1, typename T2>
struct CPyFunctionHelper2 {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		typedef R(*OriginalSignature)(T1, T2);
		OriginalSignature f = (OriginalSignature)F;
		R r = f(a1, a2);
		return CPyConverter<R>::ConvertToPyObject(r);
	}
};

template<typename T1, typename T2>
struct CPyFunctionHelper2<void, T1, T2> {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		typedef R(*OriginalSignature)(T1, T2);
		OriginalSignature f = (OriginalSignature)F;
		f(a1, a2);
		Py_RETURN_NONE;
	}
};

template<typename R, typename T1, typename T2, typename T3>
struct CPyFunctionHelper3 {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		typedef R(*OriginalSignature)(T1, T2, T3);
		OriginalSignature f = (OriginalSignature)F;
		R r = f(a1, a2, a3);
		return CPyConverter<R>::ConvertToPyObject(r);
	}
};

template<typename T1, typename T2, typename T3>
struct CPyFunctionHelper3<void, T1, T2, T3> {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		typedef R(*OriginalSignature)(T1, T2, T3);
		OriginalSignature f = (OriginalSignature)F;
		f(a1, a2, a3);
		Py_RETURN_NONE;
	}
};

template<typename R, typename T1, typename T2, typename T3, typename T4>
struct CPyFunctionHelper4 {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		T4 a4 = tuple.Get<T4>(3);
		typedef R(*OriginalSignature)(T1, T2, T3, T4);
		OriginalSignature f = (OriginalSignature)F;
		R r = f(a1, a2, a3, a4);
		return CPyConverter<R>::ConvertToPyObject(r);
	}
};

template<typename T1, typename T2, typename T3, typename T4>
struct CPyFunctionHelper4<void, T1, T2, T3, T4> {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		T4 a4 = tuple.Get<T4>(3);
		typedef R(*OriginalSignature)(T1, T2, T3, T4);
		OriginalSignature f = (OriginalSignature)F;
		f(a1, a2, a3, a4);
		Py_RETURN_NONE;
	}
};

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
struct CPyFunctionHelper5 {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		T4 a4 = tuple.Get<T4>(3);
		T5 a5 = tuple.Get<T5>(4);
		typedef R(*OriginalSignature)(T1, T2, T3, T4, T5);
		OriginalSignature f = (OriginalSignature)F;
		R r = f(a1, a2, a3, a4, a5);
		return CPyConverter<R>::ConvertToPyObject(r);
	}
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct CPyFunctionHelper5<void, T1, T2, T3, T4, T5> {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		T4 a4 = tuple.Get<T4>(3);
		T5 a5 = tuple.Get<T5>(4);
		typedef R(*OriginalSignature)(T1, T2, T3, T4, T5);
		OriginalSignature f = (OriginalSignature)F;
		f(a1, a2, a3, a4, a5);
		Py_RETURN_NONE;
	}
};

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct CPyFunctionHelper6 {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		T4 a4 = tuple.Get<T4>(3);
		T5 a5 = tuple.Get<T5>(4);
		T6 a6 = tuple.Get<T6>(5);
		typedef R(*OriginalSignature)(T1, T2, T3, T4, T5, T6);
		OriginalSignature f = (OriginalSignature)F;
		R r = f(a1, a2, a3, a4, a5, a6);
		return CPyConverter<R>::ConvertToPyObject(r);
	}
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct CPyFunctionHelper6<void, T1, T2, T3, T4, T5, T6> {
	static PyObject* Call(void* F, PyObject* self, PyObject* args) {
		CPyTuple tuple = CPyBorrowedReference(args);
		T1 a1 = tuple.Get<T1>(0);
		T2 a2 = tuple.Get<T2>(1);
		T3 a3 = tuple.Get<T3>(2);
		T4 a4 = tuple.Get<T4>(3);
		T5 a5 = tuple.Get<T5>(4);
		T6 a6 = tuple.Get<T6>(5);
		typedef R(*OriginalSignature)(T1, T2, T3, T4, T5, T6);
		OriginalSignature f = (OriginalSignature)F;
		f(a1, a2, a3, a4, a5, a6);
		Py_RETURN_NONE;
	}
};


template<void* F, typename R>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	return CPyFunctionHelper0<R>::Call(F, self, args);
}

template<void* F, typename R, typename T1>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	return CPyFunctionHelper1<R, T1>::Call(F, self, args);
}

template<void* F, typename R, typename T1, typename T2>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	return CPyFunctionHelper2<R, T1, T2>::Call(F, self, args);
}

template<void* F, typename R, typename T1, typename T2, typename T3>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	return CPyFunctionHelper3<R, T1, T2, T3>()(F, self, args);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	return CPyFunctionHelper4<R, T1, T2, T3, T4>()(F, self, args);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	return CPyFunctionHelper5<R, T1, T2, T3, T4, T5>()(F, self, args);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	return CPyFunctionHelper6<R, T1, T2, T3, T4, T5, T6>()(F, self, args);
}

