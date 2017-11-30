#pragma once
#include <Python.h>

class CPyObject
{
protected:
	PyObject* pyObject_;
public:
	CPyObject();
	CPyObject(PyObject* p);
	virtual ~CPyObject();

	PyObject* pyObject() const;
	CPyObject* pyObject(PyObject* p);

	void IncRef();
	void DecRef();
	void Release();

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
	T To();
};