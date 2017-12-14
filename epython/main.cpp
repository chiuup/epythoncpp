#include <stdio.h>
#include <conio.h>
#include "cpython\cpython.h"

CPYTHON_MODULE_INIT(ryan_engine) {
}

int main() 
{
	CPYTHON_MODULE_IMPORT(ryan_engine);
	CPython::Interpreter interpreter;

	{
		CPython::InterpreterLock lock(&interpreter);
		CPython::Object fooMod(PyImport_ImportModule("scripts.stuff.foo"));
		if (!fooMod) {
			PyErr_Print();
		}
		printf("=================================================\n");

		CPython::Object bar = fooMod.GetAttr("bar"), foo = fooMod.GetAttr("Foo");

		assert(bar.pyObject() != NULL);
		assert(bar.IsSubclass(foo));
		assert(bar().IsInstance(foo));
	}

	_getch();
	return 0;
}