#pragma once
#include <Python.h>
#include "cpyobject.h"

class CPyTuple:public CPyObject {
public:
	CPyTuple(int n);
	CPyTuple() : CPyTuple(0) {}
	CPyTuple(PyObject* p) : CPyObject(p) {}

	void Set(unsigned int n, CPyObject* item);

	template<typename T>
	T Get(unsigned int n) {
		return CPyObject(Get<PyObject*>(n)).To<T>();
	}

	template<>
	PyObject * CPyTuple::Get<PyObject*>(unsigned int n)
	{
		// Getting PyObject* will always be a new reference 
		// instead of a borrowed reference in Python C API
		PyObject* item = PyTuple_GetItem(pyObject(), n);
		Py_INCREF(item);
		return item;
	}
};
