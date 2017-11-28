#include <stdio.h>
#include <conio.h>
#include "cpython/cpython.h"
#include "cpython/cpyobject.h"
#include "cpython/cpytuple.h"
#include "cpython/cpydict.h"
#include "cpython/cpyinterpreter.h"

int main()
{
	CPython* cpython = CPython::GetInstance();

	CPyInterpreter cpyInterpreter;

	{
		CPyInterpreterLock lock(&cpyInterpreter);
		CPyObject fooMod(PyImport_ImportModule("scripts.stuff.foo"));
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