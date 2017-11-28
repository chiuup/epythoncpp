#include <assert.h>
#include "cpyobject.h"
#include "cpytuple.h"

CPyObject::CPyObject() :pyObject_(NULL) {
}

CPyObject::CPyObject(PyObject* p) :pyObject_(p) {
}

CPyObject::~CPyObject() {
	Release();
}

void CPyObject::IncRef() {
	if (pyObject_) {
		Py_INCREF(pyObject_);
	}
}


void CPyObject::DecRef() {
	if (pyObject_) {
		Py_DECREF(pyObject_);
	}
}

void CPyObject::Release() {
	DecRef();
	pyObject_ = NULL;
}

bool CPyObject::IsSubclass(CPyObject * cls) {
	return PyObject_IsSubclass(pyObject(), cls->pyObject());
}

bool CPyObject::IsInstance(CPyObject * cls) {
	return PyObject_IsInstance(pyObject(), cls->pyObject());
}


PyObject* CPyObject::pyObject() const {
	return pyObject_;
}

CPyObject* CPyObject::pyObject(PyObject* p) {
	Release();
	pyObject_ = p;
	IncRef();
	return this;
}

CPyObject* CPyObject::operator=(CPyObject* p) {
	return pyObject(p->pyObject());
}

CPyObject* CPyObject::operator=(PyObject* p) {
	return pyObject(p);
}

PyObject* CPyObject::operator ->() {
	return pyObject_;
}

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

CPyObject::operator PyObject*() {
	return pyObject_;
}

CPyObject::operator bool() {
	return pyObject_ ? true : false;
}

PyObject* CPyObject::GetAttr(CPyObject* name) {
	return PyObject_GetAttr(pyObject(), name->pyObject());
}

PyObject* CPyObject::GetAttr(const char* name) {
	return PyObject_GetAttrString(pyObject(), name);
}