#include <assert.h>
#include "cpyobject.h"
#include "cpytuple.h"

CPyObject::CPyObject(PyObject* p, bool decRef) :pyObject_(p), decRef_(decRef) {
	if (decRef_)
		IncRef();
}

CPyObject::~CPyObject() {
	if (decRef_)
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

int CPyObject::Print(FILE * fp, int flags)
{
	return PyObject_Print(pyObject(), fp, flags);
}

int CPyObject::Print(int flags)
{
	return Print(stdout, flags);
}

int CPyObject::Print()
{
	return Print(stdout, 0);
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
