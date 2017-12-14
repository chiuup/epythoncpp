#pragma once
#include <Python.h>
#include "core\functor.h"

namespace CPython {
	namespace Private {
		template<typename F>
		struct PyCFunctionConverter{};
	}

	template<void* factoryFunctionPointer>
	struct PyCFunctionFactory
	{
		template<typename FunctionType>
		static PyCFunction Make(FunctionType typeFunctionPointer) {
			assert(factoryFunctionPointer == typeFunctionPointer);
			struct lambdaHelper {
				static PyObject* lambdaFunction(PyObject* self, PyObject* args) {
					(FunctionType)factoryFunctionPointer(3, 3);
					Py_RETURN_NONE;
				}
			};
			return &lambdaHelper::lambdaFunction;
		}
	};
}