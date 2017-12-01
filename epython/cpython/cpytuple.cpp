#include <assert.h>
#include "cpytuple.h"

CPyTuple::CPyTuple(int n) :CPyObject()
{
	PyObject* tuple = PyTuple_New(n);
	assert(tuple != NULL);

	pyObject_ = tuple;
}

void CPyTuple::Set(unsigned int n, CPyObject& item)
{
	assert(n < PyTuple_GET_SIZE(pyObject_));
	// PyTuple_SetItem steals reference.
	item.IncRef();
	PyTuple_SetItem(pyObject(), n, item.pyObject());
}
