#include <assert.h>
#include "cpython.h"
#include "cpyinterpreter.h"

CPyInterpreter::CPyInterpreter() {
	// Set current thread state to main thread state
	// Also acquire GIL
	CPython::GetInstance()->Acquire();

	// Current thread state changed to new interpreter state
	pyThreadState_ = Py_NewInterpreter();
	assert(pyThreadState_ != NULL);

	// Reset current thread state to NULL
	Release();
}

CPyInterpreter::~CPyInterpreter() {
	// Set current thread state to this interpreter
	Acquire();
	// End interpreter and reste current thread state to NULL
	Py_EndInterpreter(pyThreadState_);
}

void CPyInterpreter::Acquire()
{
	PyEval_AcquireThread(pyThreadState_);
}

void CPyInterpreter::Release()
{
	PyEval_ReleaseThread(pyThreadState_);
}

int CPyInterpreter::RunSimpleString(const char * code)
{
	CPyInterpreterLock lock(this);
	int rc = PyRun_SimpleString(code);
	return rc;
}

int CPyInterpreter::RunSimpleFile(const char * filename)
{
	CPyInterpreterLock lock(this);
	FILE* fp = NULL;
	errno_t rc = fopen_s(&fp, filename, "r");
	assert(rc == 0 && fp != NULL);

	int rc2 = PyRun_SimpleFile(fp, filename);
	return rc2;
}
