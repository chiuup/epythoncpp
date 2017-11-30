#pragma once
#include <Python.h>
#include "typelist.h"
using namespace TL;

enum CPyConverterSelector { SignedInt, UnsignedInt, Float, Bool, String, CPyObjectCast };
template<typename R>
struct CPyConverter
{
	template<typename R, int v>
	struct CPyConverterImpl {
		R operator()(PyObject* from) {
			CPyBorrowedReference obj(from);
			return (R)obj;
		}
	};

	template<typename R>
	struct CPyConverterImpl<R, SignedInt> {
		R operator()(PyObject* from) {
			return (R)PyLong_AsLongLong(from);
		}
	};

	template<typename R>
	struct CPyConverterImpl<R, UnsignedInt> {
		R operator()(PyObject* from) {
			R ret = (R)PyLong_AsUnsignedLongLong(from);
			return ret;
		}
	};

	template<typename R>
	struct CPyConverterImpl<R, Float> {
		R operator()(PyObject* from) {
			return (R)PyFloat_AsDouble(from);
		}
	};

	template<typename R>
	struct CPyConverterImpl<R, Bool> {
		R operator()(PyObject* from) {
			return (R)PyBool_Check(from);
		}
	};

	template<typename R>
	struct CPyConverterImpl<R, String> {
		R operator()(PyObject* from) {
			return (R)PyUnicode_AsUTF8(from);
		}
	};

	static R Convert(PyObject* from) {
		enum {
			converterImpl = IndexOf<SignedIntTypelist, R>::value >= 0 ? SignedInt :
			IndexOf<UnsignedIntTypelist, R>::value >= 0 ? UnsignedInt :
			IndexOf<FloatTypelist, R>::value >= 0 ? Float :
			IndexOf<BoolTypeList, R>::value >= 0 ? Bool :
			IndexOf<StringTypeList, R>::value >= 0 ? String : CPyObjectCast
		};


		return CPyConverterImpl<R, converterImpl>()(from);
	}
};

