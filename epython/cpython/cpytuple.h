#pragma once
#include <Python.h>
#include "cpyobject.h"

class CPyTuple:public CPyObject {
public:
	CPyTuple(int n);
	CPyTuple() : CPyTuple(0) {}
	CPyTuple(PyObject* p) : CPyObject(p) {}

	void Set(unsigned int n, CPyObject* item);
	PyObject* Get(unsigned int n);
};
