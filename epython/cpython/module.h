#pragma once
#include <assert.h>
#include <Python.h>
#include "core\preprocessor.h"

namespace CPython {
	PyObject* InitModule(PyModuleDef* moduleDef, void(*initFunc)());
}

#define _CPYTHON_MODULE_INIT(name) \
PyMODINIT_FUNC \
CORE_CAT(PyInit_, name)() { \
	static PyMethodDef initMethodDef[] = { {0, 0, 0, 0} }; \
	static struct PyModuleDef moduleDef = { \
		PyModuleDef_HEAD_INIT, \
		CORE_STRINGIZE(name), \
		0, \
		-1, \
		initMethodDef, \
		0, \
		0, \
		0, \
		0 \
	}; \
\
	return CPython::InitModule(&moduleDef, CORE_CAT(CPyInitModule_, name)); \
} \
void CORE_CAT(CPyInitModule_, name)()

#define CPYTHON_MODULE_INIT(name) \
void CORE_CAT(CPyInitModule_, name)(); \
_CPYTHON_MODULE_INIT(name)

#define CPYTHON_MODULE_IMPORT(name) \
{ \
	int rc = PyImport_AppendInittab(CORE_STRINGIZE(name), CORE_CAT(PyInit_, name)); \
	assert(rc != -1); \
}
