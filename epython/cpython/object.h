#pragma once
#include <Python.h>
#include "core\type_traits.h"

namespace CPython {
	namespace Private {
		struct ReferenceHolder {
			PyObject* pyObject;
			inline ReferenceHolder(PyObject* p) :pyObject(p) {}

			inline operator PyObject*() { return pyObject; }
		};
	}
	struct BorrowedReference :Private::ReferenceHolder {
		inline BorrowedReference(PyObject* p) :Private::ReferenceHolder(p) {}
	};
	struct NewReference :Private::ReferenceHolder {
		inline NewReference(PyObject* p) :Private::ReferenceHolder(p) {}
	};

	class Object {
	protected:
		const bool decRef_;
		PyObject* pyObject_;
	public:
		inline Object() :decRef_(true), pyObject_(NULL) {}
		inline Object(const Object& p) : decRef_(true), pyObject_(p.pyObject()) { IncRef(); }
		inline Object(PyObject* p) : decRef_(true), pyObject_(p) {}
		inline Object(BorrowedReference& p) : decRef_(true), pyObject_(p) { IncRef(); }
		inline Object(NewReference& p) : decRef_(true), pyObject_(p) {}

		virtual ~Object() { if (decRef_) DecRef(); }

		inline PyObject* pyObject() const { return pyObject_; }
		Object& pyObject(PyObject* p);

		inline void IncRef() { Py_XINCREF(pyObject_); }
		inline void DecRef() { Py_XDECREF(pyObject_); }

		inline void Release() { DecRef(); pyObject_ = NULL; }
		inline int Print(FILE* fp, int flags) { return PyObject_Print(pyObject(), fp, flags); }
		inline int Print(int flags) { return Print(stdout, flags); }
		inline int Print() { return Print(stdout, 0); }

		inline bool IsSubclass(Object& cls) { return PyObject_IsSubclass(pyObject(), cls.pyObject()); }
		inline bool IsInstance(Object& cls) { return PyObject_IsInstance(pyObject(), cls.pyObject()); }
		inline Object GetAttr(Object& name) { return Object(NewReference(PyObject_GetAttr(pyObject(), name.pyObject()))); }
		inline Object GetAttr(const char* name) { return Object(NewReference(PyObject_GetAttrString(pyObject(), name))); }

		inline Object& operator=(Object& p) { return pyObject(p.pyObject()); }
		inline Object& operator=(PyObject* p) { return pyObject(p); }
		inline PyObject* operator->() { return pyObject_; }

		Object operator()();
		inline Object operator()(Object* args) { return operator()(args, NULL); }
		inline Object operator()(Object* args, Object* kwargs) {
			PyObject* result = PyObject_Call(pyObject(), args->pyObject(), kwargs ? kwargs->pyObject() : NULL);
			assert(result != NULL);
			return Object(NewReference(result));
		}


		inline operator PyObject*() const { return pyObject_; }
		inline operator bool() const { return pyObject_ ? true : false; }
	};
}