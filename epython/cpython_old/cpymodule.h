#pragma once
#include <assert.h>
#include <Python.h>
#include "preprocessor.h"
#include "cpyfunction.h"
#include "cpyscope.h"

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

void _CPyModuleDef(const char* name, PyMethodDef* methodDef);

#define CPYMODULE_DEF_4(name, func, flags, doc) \
do { \
	static PyMethodDef CAT(methodDef_, func)[] = { \
		{ name, func, flags, doc }, \
		{ 0, 0, 0, 0 } \
	}; \
	_CPyModuleDef(name, CAT(methodDef_, func)); \
} while(0)
#define CPYMODULE_DEF_3(name, func, flags) CPYMODULE_DEF_4(name, func, METH_VARARGS, 0)
#define CPYMODULE_DEF_2(name, func) CPYMODULE_DEF_3(name, func, METH_VARARGS)
#define CPYMODULE_DEF(...) VA_SELECT(CPYMODULE_DEF, __VA_ARGS__)

template<PyCFunction func>
void CPyModuleDef(const char* name, const char* doc, int flags) {
	static PyMethodDef methodDef[] = {
		{ name, func, flags, doc },
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<PyCFunction func>
void CPyModuleDef(const char* name, const char* doc) {
	return CPyModuleDef<func>(name, doc, METH_VARARGS);
}

template<PyCFunction func>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<func>(name, 0, METH_VARARGS);
}

template<void* F, typename R>
void CPyModuleDef(const char* name, const char* doc) {
	static PyMethodDef methodDef[] = {
		{ name, CPyFunction<F, R>, METH_VARARGS, doc },
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<void* F, typename R>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<F, R>(name, 0);
}

template<void* F, typename R, typename T1>
void CPyModuleDef(const char* name, const char* doc) {
	static PyMethodDef methodDef[] = {
		{ name, CPyFunction<F, R, T1>, METH_VARARGS, doc },
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<void* F, typename R, typename T1>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<F, R, T1>(name, 0);
}

template<void* F, typename R, typename T1, typename T2>
void CPyModuleDef(const char* name, const char* doc) {
	static PyMethodDef methodDef[] = {
		{ name, CPyFunction<F, R, T1, T2>, METH_VARARGS, doc},
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<void* F, typename R, typename T1, typename T2>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<F, R, T1, T2>(name, 0);
}

template<void* F, typename R, typename T1, typename T2, typename T3>
void CPyModuleDef(const char* name, const char* doc) {
	static PyMethodDef methodDef[] = {
		{ name, CPyFunction<F, R, T1, T2, T3>, METH_VARARGS, doc },
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<void* F, typename R, typename T1, typename T2, typename T3>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<F, R, T1, T2, T3>(name, 0);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4>
void CPyModuleDef(const char* name, const char* doc) {
	static PyMethodDef methodDef[] = {
		{ name, CPyFunction<F, R, T1, T2, T3, T4>, METH_VARARGS, doc },
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<F, R, T1, T2, T3, T4>(name, 0);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
void CPyModuleDef(const char* name, const char* doc) {
	static PyMethodDef methodDef[] = {
		{ name, CPyFunction<F, R, T1, T2, T3, T4, T5>, METH_VARARGS, doc },
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<F, R, T1, T2, T3, T4, T5>(name, 0);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void CPyModuleDef(const char* name, const char* doc) {
	static PyMethodDef methodDef[] = {
		{ name, CPyFunction<F, R, T1, T2, T3, T4, T5, T6>, METH_VARARGS, doc },
		{ 0, 0, 0, 0 }
	};
	_CPyModuleDef(name, methodDef);
}

template<void* F, typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void CPyModuleDef(const char* name) {
	return CPyModuleDef<F, R, T1, T2, T3, T4, T5, T6>(name, 0);
}

