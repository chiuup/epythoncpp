#include "object.h"
#include "tuple.h"

using namespace CPython;

Object& Object::pyObject(PyObject* p)
{
	DecRef();
	pyObject_ = p;
	IncRef();
	return *this;
}

Object Object::operator()(void) {
	Tuple emptyArgs;
	return operator()(&emptyArgs, NULL);
}
