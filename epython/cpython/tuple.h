#pragma once
#include <Python.h>
#include "object.h"
#include "converter.h"

namespace CPython {
	class Tuple :public Object {
	public:
		Tuple(int n);
		Tuple() : Tuple(0) {}
		Tuple(PyObject* p) : Object(p) {}
		Tuple(const Tuple& p) :Object(p) {}
		Tuple(const Object& p) :Object(p) {}
		Tuple(BorrowedReference& p) : Object(p) {}
		Tuple(NewReference& p) : Object(p) {}

		void Set(unsigned int n, Object& item);

		template<typename T>
		inline T Get(unsigned int n) {
			return Converter<T>::FromPyObject(Get<PyObject*>(n));
		}

		template<>
		inline PyObject* Tuple::Get<PyObject*>(unsigned int n)
		{
			assert(n < PyTuple_GET_SIZE(pyObject_));
			PyObject* item = PyTuple_GetItem(pyObject(), n);
			return item;
		}

		template<>
		inline Object Tuple::Get<Object>(unsigned int n)
		{
			assert(n < PyTuple_GET_SIZE(pyObject_));
			return Object(BorrowedReference(Get<PyObject*>(n)));
		}
	};

}