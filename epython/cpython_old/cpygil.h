#pragma once
#include <Python.h>

class CPyGIL {
private:
	PyGILState_STATE pyGILState_;
public:
	CPyGIL() {
		pyGILState_ = PyGILState_Ensure();
	}
	~CPyGIL() {
		PyGILState_Release(pyGILState_);
	}
};
