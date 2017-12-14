#include <assert.h>
#include "environment.h"
#include "interpreter.h"
using namespace CPython;

Interpreter::Interpreter() {
	// Set current thread state to main thread state
	// Also acquire GIL
	Environment::GetInstance()->Acquire();

	// Current thread state changed to new interpreter state
	pyThreadState_ = Py_NewInterpreter();
	assert(pyThreadState_ != NULL);

	// Reset current thread state to NULL
	Release();
}

Interpreter::~Interpreter() {
	// Set current thread state to this interpreter
	Acquire();
	// End interpreter and reste current thread state to NULL
	Py_EndInterpreter(pyThreadState_);
}

void Interpreter::Acquire()
{
	PyEval_AcquireThread(pyThreadState_);
}

void Interpreter::Release()
{
	PyEval_ReleaseThread(pyThreadState_);
}

int Interpreter::RunSimpleString(const char * code)
{
	InterpreterLock lock(this);
	int rc = PyRun_SimpleString(code);
	return rc;
}

int Interpreter::RunSimpleFile(const char * filename)
{
	InterpreterLock lock(this);
	FILE* fp = NULL;
	errno_t rc = fopen_s(&fp, filename, "r");
	assert(rc == 0 && fp != NULL);

	int rc2 = PyRun_SimpleFile(fp, filename);
	return rc2;
}
