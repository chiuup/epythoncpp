#pragma once
#include <Python.h>
#include "typelist.h"

enum CPyConverterSelector { SignedInt, UnsignedInt, Float, Bool, String, CPyObjectCast };
template<typename R>
struct CPyConverter
{
	template<typename R, int v>
	struct ConverterFromPyObjectImpl {
		R operator()(PyObject* from) {
			CPyObject obj(CPyBorrowedReference(from));
			return (R)obj;
		}
	};

	template<typename R>
	struct ConverterFromPyObjectImpl<R, SignedInt> {
		R operator()(PyObject* from) {
			return (R)PyLong_AsLongLong(from);
		}
	};

	template<typename R>
	struct ConverterFromPyObjectImpl<R, UnsignedInt> {
		R operator()(PyObject* from) {
			R ret = (R)PyLong_AsUnsignedLongLong(from);
			return ret;
		}
	};

	template<typename R>
	struct ConverterFromPyObjectImpl<R, Float> {
		R operator()(PyObject* from) {
			return (R)PyFloat_AsDouble(from);
		}
	};

	template<typename R>
	struct ConverterFromPyObjectImpl<R, Bool> {
		R operator()(PyObject* from) {
			return (R)PyBool_Check(from);
		}
	};

	template<typename R>
	struct ConverterFromPyObjectImpl<R, String> {
		R operator()(PyObject* from) {
			return (R)PyUnicode_AsUTF8(from);
		}
	};

	static R ConvertFromPyObject(PyObject* from) {
		enum {
			converterImpl = IndexOf<SignedIntTypelist, R>::value >= 0 ? SignedInt :
			IndexOf<UnsignedIntTypelist, R>::value >= 0 ? UnsignedInt :
			IndexOf<FloatTypelist, R>::value >= 0 ? Float :
			IndexOf<BoolTypeList, R>::value >= 0 ? Bool :
			IndexOf<StringTypeList, R>::value >= 0 ? String : CPyObjectCast
		};

		return ConverterFromPyObjectImpl<R, converterImpl>()(from);
	}

	template<typename R, int v>
	struct ConvertToPyObjectImpl {
		PyObject* operator()(R from) {
			return (R)obj;
		}
	};

	template<typename R>
	struct ConvertToPyObjectImpl<R, CPyObjectCast> {
		PyObject* operator()(R from) {
			return static_cast<CPyObject*>(from)->pyObject();
		}
	};

	template<typename R>
	struct ConvertToPyObjectImpl<R, SignedInt> {
		PyObject* operator()(R from) {
			return PyLong_FromLongLong((long long)from);
		}
	};

	template<typename R>
	struct ConvertToPyObjectImpl<R, UnsignedInt> {
		PyObject* operator()(R from) {
			return PyLong_FromUnsignedLongLong((unsigned long long)from);
		}
	};

	template<typename R>
	struct ConvertToPyObjectImpl<R, Float> {
		PyObject* operator()(R from) {
			return PyFloat_FromDouble((double)from);
		}
	};

	template<typename R>
	struct ConvertToPyObjectImpl<R, Bool> {
		PyObject* operator()(R from) {
			PyObject* ret = from ? Py_True : Py_False;
			Py_INCREF(ret);
			return ret;
		}
	};

	template<typename R>
	struct ConvertToPyObjectImpl<R, String> {
		PyObject* operator()(R from) {
			return PyUnicode_FromString((const char*)from);
		}
	};
	enum { HasReturnValue = IndexOf<VoidTypeList, R>::value >= 0 ? false : true };
	static PyObject* ConvertToPyObject(R from) {
		enum {
			converterImpl = IndexOf<SignedIntTypelist, R>::value >= 0 ? SignedInt :
			IndexOf<UnsignedIntTypelist, R>::value >= 0 ? UnsignedInt :
			IndexOf<FloatTypelist, R>::value >= 0 ? Float :
			IndexOf<BoolTypeList, R>::value >= 0 ? Bool :
			IndexOf<StringTypeList, R>::value >= 0 ? String : CPyObjectCast
		};

		return ConvertToPyObjectImpl<R, converterImpl>()(from);
	}
};

