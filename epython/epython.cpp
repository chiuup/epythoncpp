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

static int plus(int a, int b) {
	return a + b;
}

CPYMODULE_INIT(ryan_engine) {
	CPyModuleDef<hello>("hello");
	CPyModuleDef<print1>("print1", METH_VARARGS, "prints 1");
	// CPyModuleDef<plus>("plus");
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
		assert(bar.IsSubclass(foo));
		assert(CPyObject(bar()).IsInstance(foo));

		CPyTuple tuple(10);
		CPyObject p(CPyNewReference(PyLong_FromLong(-50)));
		CPyObject q(CPyNewReference(PyUnicode_FromString("my_string")));

		tuple.Set(0, p);
		tuple.Set(1, q);
		CPyObject peek = CPyBorrowedReference(tuple.Get<PyObject*>(0));
		peek.Print();
		
		printf_s("\nValue = %ld\n", PyLong_AsLong(p));
		printf_s("Value = %d\n", tuple.Get<int>(0));
		printf_s("Value = %u\n", tuple.Get<unsigned int>(0));
		printf_s("Value = %s\n", tuple.Get<const char*>(3));
	}

	_getch();
	return 0;
}
