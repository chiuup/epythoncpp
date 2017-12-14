#pragma once
#include <Python.h>
#include "object.h"

namespace CPython {
	namespace Private {
		class Scope : public Object {
		public:
			Scope(PyObject* newScope) : Object(BorrowedReference(newScope)), previousScope_(currentScope_) {
				currentScope_ = newScope;
			}
			Scope() : Object(BorrowedReference(currentScope_ ? currentScope_ : Py_None)), previousScope_(currentScope_) {
			}

			virtual ~Scope() {
				currentScope_ = previousScope_;
			}
		private:
			PyObject * previousScope_;
			static PyObject* currentScope_;

			Scope(const Scope&);
			void operator=(const Scope&);
		};
	}
}