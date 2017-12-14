#pragma once
#include <Python.h>
#include "object.h"
namespace CPython {
	class Dict :public Object {
	public:
		Dict();
		Dict(PyObject* p) : Object(p) {}
		Dict(const Dict& p) :Object(p) {}
		Dict(const Object& p) :Object(p) {}
		Dict(BorrowedReference& p) : Object(p) {}
		Dict(NewReference& p) : Object(p) {}

		void Set(Object& key, Object& value);
		void Set(const char* key, Object& value);
		inline Object Get(const Object& key);
		inline Object Get(const char* key);
		bool Contains(const Object& key);
		bool Contains(const char* key);
	};
}