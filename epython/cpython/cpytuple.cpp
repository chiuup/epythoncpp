#include <assert.h>
#include "cpytuple.h"

CPyTuple::CPyTuple(int n)
{
	PyObject* tuple = PyTuple_New(n);
	assert(tuple != NULL);

	Release();
	pyObject_ = tuple;
}

void CPyTuple::Set(unsigned int n, CPyObject * item)
{
	PyTuple_SetItem(pyObject(), n, item->pyObject());
}

PyObject * CPyTuple::Get(unsigned int n)
{
	PyObject* item = PyTuple_GetItem(pyObject(), n);
	return item;
}
