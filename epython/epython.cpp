#include <stdio.h>
#include <conio.h>
#include "cpython/cpython.h"
#include "cpython/cpyobject.h"
#include "cpython/cpytuple.h"
#include "cpython/cpydict.h"
#include "cpython/cpyinterpreter.h"
#include "cpython/cpymodule.h"

static PyObject* print1(PyObject* self, PyObject* args) {
	return PyLong_FromLong(1);
}
static PyObject* hello(PyObject* self, PyObject* args) {
	return PyUnicode_FromString("Hello World");
}

CPYMODULE_INIT(ryan_engine) {
	CPyModuleDef<hello>("hello");
	CPyModuleDef<print1>("print1", METH_VARARGS, "prints 1");;
}

int main()
{
	CPYMODULE_IMPORT(ryan_engine);
	CPython* cpython = CPython::GetInstance();
	CPyInterpreter cpyInterpreter;

	{
		CPyInterpreterLock lock(&cpyInterpreter);
		CPyObject fooMod(PyImport_ImportModule("scripts.stuff.foo"));
		if (!fooMod) {
			PyErr_Print();
		}
		CPyObject bar = fooMod.GetAttr("bar"), foo = fooMod.GetAttr("Foo");
		
		assert(bar.pyObject() != NULL);
		assert(bar.IsSubclass(&foo));
		assert(CPyObject(bar()).IsInstance(&foo));
		CPyObject p(PyLong_FromLong(50));
		CPyTuple tuple(10);
		printf_s("Value = %ld\n", PyLong_AsLong(p));
	}

	_getch();
	return 0;
}
