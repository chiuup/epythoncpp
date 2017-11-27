#pragma once
#include "Python.h"

#ifdef _WIN64
#define _PY_PATH L"epython/x64/python36.zip;epython/x64/DLLs;"
#elif _WIN32
#define _PY_PATH L"epython/x86/python36.zip;epython/x86/DLLs;"
#else
// #define _PY_PATH // Not supported
#endif

class CPython
{
public:
	CPython() {
		Py_SetPath(_PY_PATH);
		Py_Initialize();
	}

	~CPython() {
		Py_Finalize();
	}
};

class CPyObject
{
private:
	PyObject* p_;
public:
	CPyObject() :p_(NULL) {}
	CPyObject(PyObject* p) : p_(p) {}

	~CPyObject() {
		this->Release();
	}

	PyObject* pyObject() const {
		return this->p_;
	}

	void pyObject(PyObject* p) {	
		this->Release();
		this->p_ = p;
		this->IncRef();
	}

	void IncRef() {
		if (this->p_) {
			Py_INCREF(this->p_);
		}
	}

	void DecRef() {
		if (this->p_) {
			Py_DECREF(this->p_);
		}
	}

	void Release() {
		this->DecRef();
		this->p_ = NULL;
	}

	CPyObject* operator=(CPyObject* p) {
		this->Release();
		this->pyObject(p->pyObject());
		return this;
	}

	CPyObject* operator=(PyObject* p) {
		this->pyObject(p);
		return this;
	}

	operator PyObject*() {
		return this->p_;
	}

	operator bool() {
		return this->p_ ? true : false;
	}

	PyObject* operator ->() {
		return this->p_;
	}
};