#include <stdio.h>CPython::FunctionDef("plus", plus, 0);
#include <conio.h>
#include "cpython\cpython.h"
#include "core\functor.h"

#include "cpython\function.h"
int plus(int a, int b) {
	// printf("%d\n", a + b);
	return a + b;
}
int minus(int a, int b) {
	printf("%d\n", a - b);
	return a - b;
}
int hello() {
	return 3333;
}
void test()
{
	{
		/*auto f = CPython::Private::PyCFunctionFactory<plus>::Make(plus);
		assert(Py_None == f(NULL, NULL));
	
		auto f2 = CPython::Private::PyCFunctionFactory<minus>::Make(minus);
		assert(Py_None == f2(NULL, NULL));*/
	}
}

CPYTHON_MODULE_INIT(ryan_engine) {
	CPython::FunctionDef("plus", plus);
	CPython::FunctionDef("minus", minus);
}

int main()
{
	CPYTHON_MODULE_IMPORT(ryan_engine);
	CPython::Interpreter interpreter;

	{
		CPython::InterpreterLock lock(&interpreter);
		CPython::Object fooMod = CPython::ImportModule("scripts.stuff.foo");
		if (!fooMod) {
			PyErr_Print();
		}
		else {
			printf("=================================================\n");

			CPython::Object bar = fooMod.GetAttr("bar"), foo = fooMod.GetAttr("Foo");

			assert(bar.pyObject() != NULL);
			assert(bar.IsSubclass(foo));
			assert(bar().IsInstance(foo));
		}
		printf("=================================================\n");
		auto intobj = CPython::Object::From(1);
		printf("%d\n", intobj.To<int>());
		printf("=================================================\n");
		CPython::Tuple tuple(10);
		CPython::Object p(CPython::NewReference(PyLong_FromLong(-50)));
		CPython::Object q(CPython::NewReference(PyUnicode_FromString("my_string")));

		tuple.Set(0, p);
		tuple.Set(1, q);

		printf("%d\n", tuple.Get<int>(0));
		printf("%s\n", tuple.Get<const char*>(1));
		printf("=================================================\n");
	}
	{
		CPython::InterpreterLock lock(&interpreter);
		CPython::Function* func = CPython::MakeFunction(hello);

		CPython::Tuple plus_arg_tuple(2);
		plus_arg_tuple.Set(0, CPython::Object::From<int>(100));
		plus_arg_tuple.Set(1, CPython::Object::From<int>(200));
		PyObject* plus_ret = func->operator()(NULL, CPython::Tuple(), NULL);

		CPython::Object plus_ret_obj = CPython::Object(CPython::NewReference(plus_ret));
		printf("%d\n", plus_ret_obj.To<int>());
		Py_DECREF((PyObject*)func);
		printf("=================================================\n");
	}

	Core::Functor<int(*)(int, int)> functor4 = Core::MakeFunctor(plus);
	printf("%d\n", (functor4)(33, 44));
	test();
	printf("=================================================\n");
	_getch();
	return 0;
}