#include "cpython.h"

CPython* CPython::instance_ = NULL;

CPython::CPython() {
	if (Py_IsInitialized()) return;	
	Py_SetPath(_PY_PATH);
	Py_Initialize();

	PyEval_InitThreads(); // Acquired GIL
	mainPyThreadState_ = PyEval_SaveThread(); // Releasing GIL
	assert(mainPyThreadState_ != NULL);
}
CPython* CPython::GetInstance() {
	if (instance_ != NULL) return instance_;
	instance_ = new CPython();
	return instance_;
}
bool CPython::initialized()
{
	return Py_IsInitialized();
}

void CPython::Acquire()
{
	PyEval_AcquireThread(mainPyThreadState_);
}

void CPython::Release()
{
	PyEval_ReleaseThread(mainPyThreadState_);
}

PyThreadState* CPython::mainPyThreadState()
{
	return mainPyThreadState_;
}

CPython::~CPython() {
	if (mainPyThreadState_ != NULL) {
		PyEval_RestoreThread(mainPyThreadState_);
	}
	Py_Finalize();
	instance_ = NULL;
}
