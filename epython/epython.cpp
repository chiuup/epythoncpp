#include <stdio.h>
#include <conio.h>
#include "cpython/cpython.h"
#include "cpython/cpyobject.h"
#include "cpython/cpytuple.h"
#include "cpython/cpydict.h"
#include "cpython/cpyinterpreter.h"
#include "cpython/cpymodule.h"
#include "cpython/cpyfunction.h"

static PyObject* print1(PyObject* self, PyObject* args) {
	return PyLong_FromLong(1);
}
static PyObject* hello(PyObject* self, PyObject* args) {
	return PyUnicode_FromString("Hello World");
}

static int minus(int a, int b) {
	return a - b;
}
static int plus(int a, int b) {
	return a + b;
}

static int square(int a) {
	return a * a;
}

static const char* echo(const char* msg) {
	return msg;
}

static void no_ret(int k) {
	printf("no_ret: %d\n", k);
}

CPYMODULE_INIT(ryan_engine) {
	CPyModuleDef<hello>("hello");
	CPyModuleDef<print1>("print1", "prints 1", METH_VARARGS);
	CPyModuleDef<plus, int, int, int>("plus");
	CPyModuleDef<minus, int, int, int>("minus");
	CPyModuleDef<square, int, int>("square");
	CPyModuleDef<echo, const char*, const char*>("echo");
	CPyModuleDef<no_ret, void, int>("no_ret");
}

int main()
{
	// printf_s("%d\n", CPyFunction<int, int, int>::Call(plus, 1, 1));

	CPYMODULE_IMPORT(ryan_engine);
	CPython* cpython = CPython::GetInstance();
	CPyInterpreter cpyInterpreter;

	{
		CPyInterpreterLock lock(&cpyInterpreter);
		CPyObject fooMod(PyImport_ImportModule("scripts.stuff.foo"));
		if (!fooMod) {
			PyErr_Print();
		}
		printf("=================================================\n");

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
		printf_s("Value = %s\n", tuple.Get<const char*>(1));

		CPyTuple args(2);
		args.Set(0, CPyObject(PyLong_FromLong(5)));
		args.Set(1, CPyObject(PyLong_FromLong(10)));
		PyObject* oo = CPyFunction<plus, int, int, int>(0, args.pyObject());
		
		printf_s("%d\n", PyLong_AsLong(oo));

	}

	_getch();
	return 0;
}
