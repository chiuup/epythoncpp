#include <stdio.h>
#include <conio.h>
#include "cpython\cpython.h"
#include "core\functor.h"

#include "cpython\function.h"
int plus(int a, int b) {
	printf("%d\n", a + b);
	return a + b;
}
int minus(int a, int b) {
	printf("%d\n", a - b);
	return a - b;
}
void test()
{
	{
		auto f = CPython::PyCFunctionFactory<plus>::Make(plus);
		assert(Py_None == f(NULL, NULL));
	
		auto f2 = CPython::PyCFunctionFactory<minus>::Make(minus);
		assert(Py_None == f2(NULL, NULL));
	}
}
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
		printf("=================================================\n");
	}

	Core::Functor<int(*)(int, int)> functor4 = Core::MakeFunctor(plus);
	printf("%d\n", (functor4)(33, 44));
	test();


	_getch();
	return 0;
}