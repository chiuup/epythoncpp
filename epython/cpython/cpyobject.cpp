#include <assert.h>
#include "cpyobject.h"
#include "cpytuple.h"

PyObject * CPyObject::operator()(CPyObject * args, CPyObject * kwargs) {
	PyObject* result = PyObject_Call(pyObject(), args->pyObject(), kwargs ? kwargs->pyObject() : NULL);
	assert(result != NULL);
	return result;
}

PyObject * CPyObject::operator()(CPyObject * args) {
	return operator()(args, NULL);
}

PyObject * CPyObject::operator()() {
	CPyTuple emptyArgs;
	return operator()(&emptyArgs, NULL);
}
