#include "cpyscope.h"
#include "cpymodule.h"

PyObject* CPyInitModule(PyModuleDef * moduleDef, void(*initFunc)()) {
	PyObject* m = PyModule_Create(moduleDef);
	if (m == NULL) return NULL;
	CPyScope currentModule(m);
	initFunc();
	return m;
}

void _CPyModuleDef(const char* name, PyMethodDef* methodDef) {
	CPyScope current;
	int rc = PyModule_AddFunctions(current.pyObject(), methodDef);
	assert(rc == 0);
}

