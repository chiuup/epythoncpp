#include "module.h"
#include "scope.h"

PyObject* CPython::InitModule(PyModuleDef * moduleDef, void(*initFunc)()) {
	PyObject* m = PyModule_Create(moduleDef);
	if (m == NULL) return NULL;
	Private::Scope currentModule(m);
	initFunc();
	return m;
}
