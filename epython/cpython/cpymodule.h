#pragma once
#include <assert.h>
#include <Python.h>
#include "preprocessor.h"
#include "cpyfunction.h"

PyObject* CPyInitModule(PyModuleDef* moduleDef, void(*initFunc)());

#define _CPYMODULE_INIT(name) \
PyMODINIT_FUNC \
CAT(PyInit_, name)() { \
	static PyMethodDef initMethodDef[] = { {0, 0, 0, 0} }; \
	static struct PyModuleDef moduleDef = { \
		PyModuleDef_HEAD_INIT, \
		STRINGIZE(name), \
		0, \
		-1, \
		initMethodDef, \
		0, \
		0, \
		0, \
		0 \
	}; \
\
	return CPyInitModule(&moduleDef, CAT(CPyInitModule_, name)); \
} \
void CAT(CPyInitModule_, name)()

#define CPYMODULE_INIT(name) \
void CAT(CPyInitModule_, name)(); \
_CPYMODULE_INIT(name)

#define CPYMODULE_IMPORT(name) \
{ \
	int rc = PyImport_AppendInittab(STRINGIZE(name), CAT(PyInit_, name)); \
	assert(rc != -1); \
}

void CPyModuleDef(const char* name, PyCFunction func);