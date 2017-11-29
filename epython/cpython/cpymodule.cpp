#include "cpyscope.h"
#include "cpymodule.h"

PyObject* CPyInitModule(PyModuleDef * moduleDef, void(*initFunc)()) {
	PyObject* m = PyModule_Create(moduleDef);
	if (m == NULL) return NULL;
	CPyScope currentModule(m);
	initFunc();
	return m;
}

void CPyModuleDef(const char* name, PyCFunction func) {
	// Warning: This will cause memory leak if we ever unload modules.
	PyMethodDef* methodDef = new PyMethodDef[2]();
	methodDef[0].ml_name = name;
	methodDef[0].ml_meth = func;
	methodDef[0].ml_flags = METH_VARARGS;

	CPyScope current;
	int rc = PyModule_AddFunctions(current.pyObject(), methodDef);
	assert(rc == 0);
}