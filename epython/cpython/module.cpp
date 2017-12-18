#include "module.h"

namespace CPython {
	PyObject* InitModule(PyModuleDef * moduleDef, void(*initFunc)()) {
		PyObject* m = PyModule_Create(moduleDef);
		if (m == NULL) return NULL;
		Private::Scope currentModule(m);
		initFunc();
		return m;
	}

	Object ImportModule(const char * name)
	{
		return Object(PyImport_ImportModule(name));
	}
}