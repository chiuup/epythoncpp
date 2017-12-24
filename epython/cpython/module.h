#pragma once
#include <assert.h>
#include <Python.h>
#include "core\preprocessor.h"
#include "scope.h"
#include "function.h"
#include "dict.h"

namespace CPython {
	PyObject* InitModule(PyModuleDef* moduleDef, void(*initFunc)());
	
	Object ImportModule(const char* name);

	template<typename F>
	void AddFunction(const char* name, F func, const char* doc) {
		Function* funcObj = MakeFunction(func);
		Private::Scope current;
		funcObj->AddToModule(current, name, doc);
		Py_DECREF((PyObject*)funcObj);
	}

	template<typename F>
	void AddFunction(const char* name, F func) {
		AddFunction(name, func, 0);
	}

	template<typename T>
	void AddConstant(const char* name, T value) {
		Private::Scope current;
		Dict moduleDict = current.GetAttr("__dict__");
		Object pyObj = Object(NewReference(Converter<T>::ToPyObject(value)));
		moduleDict.Set(name, pyObj);
	}
}

#define _CPYTHON_MODULE_INIT(name) \
PyMODINIT_FUNC \
CORE_PP_CAT(PyInit_, name)() { \
	static PyMethodDef initMethodDef[] = { {0, 0, 0, 0} }; \
	static struct PyModuleDef moduleDef = { \
		PyModuleDef_HEAD_INIT, \
		CORE_PP_STRINGIZE(name), \
		0, \
		-1, \
		initMethodDef, \
		0, \
		0, \
		0, \
		0 \
	}; \
\
	return CPython::InitModule(&moduleDef, CORE_PP_CAT(CPyInitModule_, name)); \
} \
void CORE_PP_CAT(CPyInitModule_, name)()

#define CPYTHON_MODULE_INIT(name) \
void CORE_PP_CAT(CPyInitModule_, name)(); \
_CPYTHON_MODULE_INIT(name)

#define CPYTHON_MODULE_IMPORT(name) \
{ \
	int rc = PyImport_AppendInittab(CORE_PP_STRINGIZE(name), CORE_PP_CAT(PyInit_, name)); \
	assert(rc != -1); \
}
