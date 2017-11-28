#pragma once
#include <Python.h>
#include "cpyobject.h"

class CPyDict :public CPyObject {
public:
	CPyDict();
	CPyDict(PyObject* p) : CPyObject(p) {}

	void Set(CPyObject* key, CPyObject* value);
	void Set(const char* key, CPyObject* value);
	PyObject* Get(CPyObject* key);
	PyObject* Get(const char* key);
	bool Contains(CPyObject* key);
	bool Contains(const char* key);
};
