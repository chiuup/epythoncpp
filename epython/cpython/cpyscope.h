#pragma once
#include <Python.h>
#include "cpyobject.h"

class CPyScope: public CPyObject {
public:
	CPyScope(PyObject* newScope) : CPyObject(newScope), previousScope_(currentScope_) {
		IncRef();
		currentScope_ = newScope;
	}
	CPyScope() : CPyObject(currentScope_ ? currentScope_ : Py_None), previousScope_(currentScope_) {
		IncRef();
	}

	virtual ~CPyScope() {
		currentScope_ = previousScope_;
	}
private:
	PyObject* previousScope_;
	static PyObject* currentScope_;

	CPyScope(const CPyScope&);
	void operator=(const CPyScope&);
};
