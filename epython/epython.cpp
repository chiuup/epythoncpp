#include <stdio.h>
#include <conio.h>
#include "cpython.h"


int main()
{
	CPython cpython;
	char filename[] = "test.py";
	CPyObject p(PyLong_FromLong(50));
	printf_s("Value = %ld\n", PyLong_AsLong(p));
	_getch();
	return 0;
}