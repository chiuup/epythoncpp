#pragma once
#include <Python.h>
#include "cpyconverter.h"

class CPyObject
{
private:
	CPyObject(const CPyObject&);
protected:
	const bool decRef_;
	PyObject* pyObject_;
public:
	CPyObject(PyObject* p, bool decRef);
	CPyObject() :CPyObject(NULL, true) {}
	CPyObject(PyObject* p) :CPyObject(p, true) {}
	virtual ~CPyObject();

	PyObject* pyObject() const;
	CPyObject* pyObject(PyObject* p);

	void IncRef();
	void DecRef();
	void Release();
	int Print(FILE* fp, int flags);
	int Print(int flags);
	int Print();

	bool IsSubclass(CPyObject* cls);
	bool IsInstance(CPyObject* cls);
	PyObject* GetAttr(CPyObject* name);
	PyObject* GetAttr(const char* name);

	CPyObject* operator=(CPyObject* p);
	CPyObject* operator=(PyObject* p);
	PyObject* operator->();

	PyObject* operator()(CPyObject* args, CPyObject* kwargs);
	PyObject* operator()(CPyObject* args);
	PyObject* operator()();

	operator PyObject*();
	operator bool();

	template<typename T>
	T To() {
		return CPyConverter<T>::Convert(pyObject());
	}
};

class CPyBorrowedReference : public CPyObject
{
public:
	CPyBorrowedReference() : CPyObject(NULL, false) {}
	CPyBorrowedReference(PyObject* p) :CPyObject(p, false) {}
	virtual ~CPyBorrowedReference() {}

	void Release() { pyObject_ = NULL; }
	CPyObject* pyObject(PyObject* p) { pyObject_ = p; return this; }
};

class CPyNewReference : public CPyObject
{
public:
	CPyNewReference() : CPyObject(NULL, false) {}
	CPyNewReference(PyObject* p) :CPyObject(p, false) {}
	virtual ~CPyNewReference() { Release(); } // Have to call Release because base class won't do it

	CPyObject* pyObject(PyObject* p) { pyObject_ = p; return this; }
};