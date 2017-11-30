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
		CPyObject item;
		item = Get<PyObject*>(n);
		return item.To<T>();
	}

	template<>
	PyObject * CPyTuple::Get<PyObject*>(unsigned int n)
	{
		PyObject* item = PyTuple_GetItem(pyObject(), n);
		return item;
	}
};
