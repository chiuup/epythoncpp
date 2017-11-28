#pragma once
#include <Python.h>

class CPyInterpreter {
private:
	PyThreadState* pyThreadState_;
public:
	CPyInterpreter();
	~CPyInterpreter();

	void Acquire();
	void Release();
	int RunSimpleString(const char* code);
	int RunSimpleFile(const char* filename);
};

class CPyInterpreterLock {
private:
	CPyInterpreter* interpreter_;
public:
	CPyInterpreterLock(CPyInterpreter* interpreter) :interpreter_(interpreter) {
		interpreter_->Acquire();
	}

	~CPyInterpreterLock() {
		interpreter_->Release();
	}
};