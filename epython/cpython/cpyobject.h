#pragma once
#include <Python.h>
#include "cpyconverter.h"

struct CPyReferenceHolder {
	PyObject* pyObject;
	CPyReferenceHolder(PyObject* p) :pyObject(p) {}
};
struct CPyBorrowedReference :CPyReferenceHolder {
	CPyBorrowedReference(PyObject* p) :CPyReferenceHolder(p) {}
};
struct CPyNewReference :CPyReferenceHolder {
	CPyNewReference(PyObject* p) :CPyReferenceHolder(p) {}
};

class CPyObject
{
protected:
	const bool decRef_;
	PyObject* pyObject_;
public:
	CPyObject() :decRef_(true), pyObject_(NULL) {}
	CPyObject(const CPyObject& p) :decRef_(true), pyObject_(p.pyObject()) { IncRef(); }
	CPyObject(PyObject* p) :decRef_(true), pyObject_(p) {}
	CPyObject(CPyBorrowedReference& p) :decRef_(true), pyObject_(p.pyObject) { IncRef(); }
	CPyObject(CPyNewReference& p) :decRef_(true), pyObject_(p.pyObject) {}

	virtual ~CPyObject() {
		if (decRef_)
			Release();
	}

	void IncRef() { Py_XINCREF(pyObject_); }
	void DecRef() { Py_XDECREF(pyObject_); }

	void Release() { DecRef(); pyObject_ = NULL; }
	int Print(FILE* fp, int flags) { return PyObject_Print(pyObject(), fp, flags); }
	int Print(int flags) { return Print(stdout, flags); }
	int Print() { return Print(stdout, 0); }

	bool IsSubclass(CPyObject& cls) { return PyObject_IsSubclass(pyObject(), cls.pyObject()); }
	bool IsInstance(CPyObject& cls) { return PyObject_IsInstance(pyObject(), cls.pyObject()); }
	PyObject* GetAttr(CPyObject& name) { return PyObject_GetAttr(pyObject(), name.pyObject()); }
	PyObject* GetAttr(const char* name) { return PyObject_GetAttrString(pyObject(), name); }

	PyObject* pyObject() const { return pyObject_; }
	CPyObject& pyObject(PyObject* p) {
		Release();
		pyObject_ = p;
		IncRef();
		return *this;
	}

	CPyObject& operator=(CPyObject& p) { return pyObject(p.pyObject()); }
	CPyObject& operator=(PyObject* p) { return pyObject(p); }
	PyObject* operator->() { return pyObject_; }

	PyObject* operator()(CPyObject* args, CPyObject* kwargs);
	PyObject* operator()(CPyObject* args);
	PyObject* operator()();

	operator PyObject*() { return pyObject_; }
	operator bool() { return pyObject_ ? true : false; }

	template<typename T>
	T To() {
		return CPyConverter<T>::ConvertFromPyObject(pyObject());
	}
};
