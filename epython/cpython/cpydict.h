#pragma once
#include <Python.h>
#include "cpyobject.h"

class CPyDict :public CPyObject {
public:
	CPyDict();
	CPyDict(PyObject* p) : CPyObject(p) {}
	CPyDict(const CPyDict& p) :CPyObject(p) {}
	CPyDict(const CPyObject& p) :CPyObject(p) {}
	CPyDict(CPyBorrowedReference& p) : CPyObject(p) {}
	CPyDict(CPyNewReference& p) : CPyObject(p) {}

	void Set(CPyObject& key, CPyObject& value);
	void Set(const char* key, CPyObject& value);
	PyObject* Get(CPyObject& key);
	PyObject* Get(const char* key);
	bool Contains(CPyObject& key);
	bool Contains(const char* key);
};
