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

Object Object::operator()(Object* args, Object* kwargs) {
	PyObject* result = PyObject_Call(pyObject(), args->pyObject(), kwargs ? kwargs->pyObject() : NULL);
	assert(result != NULL);
	return Object(NewReference(result));
}

Object Object::operator()(Object* args) {
	return operator()(args, NULL);
}

Object Object::operator()() {
	Tuple emptyArgs;
	return operator()(&emptyArgs, NULL);
}
