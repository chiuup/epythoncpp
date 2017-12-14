#pragma once
#include <Python.h>

namespace CPython {
	class Interpreter {
	private:
		PyThreadState * pyThreadState_;
	public:
		Interpreter();
		~Interpreter();

		void Acquire();
		void Release();
		int RunSimpleString(const char* code);
		int RunSimpleFile(const char* filename);
	};

	class InterpreterLock {
	private:
		Interpreter * interpreter_;
	public:
		InterpreterLock(Interpreter* interpreter) :interpreter_(interpreter) {
			interpreter_->Acquire();
		}

		~InterpreterLock() {
			interpreter_->Release();
		}
	};
}