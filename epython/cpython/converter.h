#pragma once
#include <Python.h>
#include "core\type_traits.h"

namespace CPython {
	namespace Private {
		template<typename T>
		struct SignedConverter {
			inline static T FromPyObject(PyObject* obj) {
				return (T)PyLong_AsLongLong(obj);
			}

			inline static PyObject* ToPyObject(T val) {
				return PyLong_FromLongLong((long long)val);
			}
		};
		
		template<typename T>
		struct UnsignedConverter {
			inline static T FromPyObject(PyObject* obj) {
				return (T)PyLong_AsUnsignedLongLong(obj);
			}

			inline static PyObject* ToPyObject(T val) {
				return PyLong_FromUnsignedLongLong((unsigned long long)val);
			}
		};

		template<typename T>
		struct FloatConverter {
			inline static T FromPyObject(PyObject* obj) {
				return (T)PyFloat_AsDouble(obj);
			}

			inline static PyObject* ToPyObject(T val) {
				return PyFloat_FromDouble((double)val);
			}
		};

		template<typename T>
		struct StringConverter {
			inline static T FromPyObject(PyObject* obj) {
				return (T)PyUnicode_AsUTF8(obj);
			}

			inline static PyObject* ToPyObject(T val) {
				return PyUnicode_FromString((const char*)val);
			}
		};

		template<typename T>
		struct BoolConverter {
			inline static T FromPyObject(PyObject* obj) {
				return (T)PyBool_Check(obj);
			}

			inline static PyObject* ToPyObject(T val) {
				PyObject* ret = from ? Py_True : Py_False;
				Py_INCREF(ret);
				return ret;
			}
		};

		struct ObjectConverter {
			inline static PyObject* FromPyObject(PyObject* obj) {
				return obj;
			}

			inline static PyObject* ToPyObject(PyObject* val) {
				return val;
			}
		};
	}
	template<typename T>
	struct Converter {
	private:
		typedef typename 
		Core::If < Core::IsSigned<T>::value, Private::SignedConverter<T>,
			typename Core::If < Core::IsUnsigned<T>::value, Private::UnsignedConverter<T>,
				typename Core::If < Core::IsFloat<T>::value, Private::FloatConverter<T>,
					typename Core::If < Core::IsString<T>::value, Private::StringConverter<T>,
						typename Core::If < Core::IsBool<T>::value, Private::BoolConverter<T>, Private::ObjectConverter>::Type
					>::Type
				>::Type
			>::Type
		>::Type ConverterImpl;
	public:
		static inline T FromPyObject(PyObject* obj) {
			return ConverterImpl::FromPyObject(obj);
		}
		static inline PyObject* ToPyObject(T t) {
			return ConverterImpl::ToPyObject(t);
		}
	};
}