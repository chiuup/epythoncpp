#pragma once
#include <Python.h>
#include "cpyobject.h"

class CPyTuple :public CPyObject {
public:
	CPyTuple(int n);
	CPyTuple() : CPyTuple(0) {}
	CPyTuple(PyObject* p) : CPyObject(p) {}
	CPyTuple(const CPyTuple& p) :CPyObject(p) {}
	CPyTuple(const CPyObject& p) :CPyObject(p) {}
	CPyTuple(CPyBorrowedReference& p) : CPyObject(p) {}
	CPyTuple(CPyNewReference& p) : CPyObject(p) {}

	void Set(unsigned int n, CPyObject& item);

	template<typename T>
	T Get(unsigned int n) {
		return CPyObject(CPyBorrowedReference(Get<PyObject*>(n))).To<T>();
	}

	template<>
	PyObject * CPyTuple::Get<PyObject*>(unsigned int n)
	{
		assert(n < PyTuple_GET_SIZE(pyObject_));
		PyObject* item = PyTuple_GetItem(pyObject(), n);
		return item;
	}
};
