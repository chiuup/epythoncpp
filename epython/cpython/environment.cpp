#include "environment.h"
using namespace CPython;

Environment* Environment::instance_ = NULL;

Environment::Environment() {
	if (Py_IsInitialized()) return;
	Py_SetPath(_PY_PATH);
	Py_Initialize();

	PyEval_InitThreads(); // Acquired GIL
	mainPyThreadState_ = PyEval_SaveThread(); // Releasing GIL
	assert(mainPyThreadState_ != NULL);
}
Environment* Environment::GetInstance() {
	if (instance_ != NULL) return instance_;
	instance_ = new Environment();
	return instance_;
}
bool Environment::initialized()
{
	return Py_IsInitialized();
}

void Environment::Acquire()
{
	PyEval_AcquireThread(mainPyThreadState_);
}

void Environment::Release()
{
	PyEval_ReleaseThread(mainPyThreadState_);
}

PyThreadState* Environment::mainPyThreadState()
{
	return mainPyThreadState_;
}

Environment::~Environment() {
	if (mainPyThreadState_ != NULL) {
		PyEval_RestoreThread(mainPyThreadState_);
	}
	Py_Finalize();
	instance_ = NULL;
}
