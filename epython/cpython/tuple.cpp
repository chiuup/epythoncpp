#include <assert.h>
#include "tuple.h"
using namespace CPython;

Tuple::Tuple(int n) :Object()
{
	PyObject* tuple = PyTuple_New(n);
	assert(tuple != NULL);

	pyObject_ = tuple;
}

void Tuple::Set(unsigned int n, Object& item)
{
	assert(n < PyTuple_GET_SIZE(pyObject_));
	// PyTuple_SetItem steals reference.
	item.IncRef();
	PyTuple_SetItem(pyObject(), n, item.pyObject());
}
