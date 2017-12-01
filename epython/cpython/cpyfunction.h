#pragma once
#include <Python.h>
#include "preprocessor.h"
#include "cpyconverter.h"

template<void* F, typename R, typename T1, typename T2>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	CPyTuple tuple = CPyBorrowedReference(args);
	T1 a1 = tuple.Get<T1>(0);
	T2 a2 = tuple.Get<T2>(1);
	typedef R(*OriginalSignature)(T1, T2);
	OriginalSignature f = (OriginalSignature)F;
	R r = f(a1, a2);
	return CPyConverter<R>::ConvertToPyObject(r);
}


template<void* F, typename R, typename T1>
static PyObject* CPyFunction(PyObject* self, PyObject* args) {
	CPyTuple tuple = CPyBorrowedReference(args);
	T1 a1 = tuple.Get<T1>(0);
	typedef R(*OriginalSignature)(T1);
	OriginalSignature f = (OriginalSignature)F;
	R r = f(a1);
	return CPyConverter<R>::ConvertToPyObject(r);
}

//template<void* F, typename T1>
//static PyObject* CPyFunction<F, void, T1>(PyObject* self, PyObject* args) {
//	CPyTuple tuple = CPyBorrowedReference(args);
//	T1 a1 = tuple.Get<T1>(0);
//	typedef R(*OriginalSignature)(T1);
//	OriginalSignature f = (OriginalSignature)F;
//	f(a1);
//	Py_INCREF(Py_None);
//	return Py_None;
//}