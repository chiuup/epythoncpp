#pragma once
#include <Python.h>
#include "core\type_traits.h"
namespace CPython {
	template<class T> struct IsPyObjectPointer : public Core::FalseType {};
	template<> struct IsPyObjectPointer<PyObject*> :public Core::TrueType {};
	template<> struct IsPyObjectPointer<PyObject* const> :public Core::TrueType {};
	template<> struct IsPyObjectPointer<PyObject* const volatile> :public Core::TrueType {};
	template<> struct IsPyObjectPointer<PyObject* volatile> :public Core::TrueType {};
}