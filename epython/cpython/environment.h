#pragma once
#include <Python.h>

#ifdef _WIN64
#define _PY_PATH L"epython/x64/python36.zip;epython/x64/DLLs;"
#elif _WIN32
#define _PY_PATH L"epython/x86/python36.zip;epython/x86/DLLs;"
#else
// #define _PY_PATH // Not supported
#endif

namespace CPython {
	class Environment
	{
	private:
		Environment();
		PyThreadState* mainPyThreadState_;
		static Environment* instance_;
	public:
		static Environment* GetInstance();
		~Environment();

		PyThreadState* mainPyThreadState();
		bool initialized();
		void Acquire();
		void Release();
	};
}