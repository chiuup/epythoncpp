#pragma once
#include <Python.h>
#include "scope.h"

namespace CPython {

	template<class T>
	struct Class {
		Class(const char* name, const char* doc) :classObj_(new ClassObject()) {
			ClassType.tp_name = name;
			ClassType.tp_doc = doc;
			if (Py_TYPE(&ClassType) == 0)
			{
				Py_TYPE(&ClassType) = &PyType_Type;
				PyType_Ready(&ClassType);
				printf("ready\n");
			}
			PyObject* p = (PyObject*)&ClassType;

			Private::Scope current;
			Dict moduleDict = current.GetAttr("__dict__");
			moduleDict.Set(name, Object(BorrowedReference(p)));
		}
		Class(const char* name) : Class(name, 0) {}

		virtual ~Class() {}

		struct ClassObject : PyObject {
			ClassObject() { printf("class obj created\n"); }
			~ClassObject() { printf("class obj deleted\n"); }
		};

		static PyObject* ClassObjectNew(PyTypeObject *subtype, PyObject*args, PyObject* kwargs) {

		}

		static void ClassObjectDealloc(PyObject* p) {
			delete static_cast<ClassObject*>(p);
		}

		static PyTypeObject ClassType;
	private:
		Class();
		ClassObject* classObj_;
	};

	template<class T>
	PyTypeObject Class<T>::ClassType = {
		PyVarObject_HEAD_INIT(NULL, 0)
		0, // tp_name
		sizeof(ClassObject),
		0,
		(destructor)ClassObjectDealloc,               /* tp_dealloc */
		0,                                  /* tp_print */
		0,                                  /* tp_getattr */
		0,                                  /* tp_setattr */
		0,                                  /* tp_compare */
		0, //(reprfunc)func_repr,                   /* tp_repr */
		0,                                  /* tp_as_number */
		0,                                  /* tp_as_sequence */
		0,                                  /* tp_as_mapping */
		0,                                  /* tp_hash */
		0,                              /* tp_call */
		0,                                  /* tp_str */
		0, // PyObject_GenericGetAttr,            /* tp_getattro */
		0, // PyObject_GenericSetAttr,            /* tp_setattro */
		0,                                  /* tp_as_buffer */
		Py_TPFLAGS_DEFAULT| Py_TPFLAGS_BASETYPE /* | Py_TPFLAGS_HAVE_GC */,/* tp_flags */
		0,                                  /* tp_doc */
		0, // (traverseproc)func_traverse,          /* tp_traverse */
		0,                                  /* tp_clear */
		0,                                  /* tp_richcompare */
		0, //offsetof(PyFunctionObject, func_weakreflist), /* tp_weaklistoffset */
		0,                                  /* tp_iter */
		0,                                  /* tp_iternext */
		0,                                  /* tp_methods */
		0, // func_memberlist,              /* tp_members */
		0,                /* tp_getset */
		0,                                  /* tp_base */
		0,                                  /* tp_dict */
		0,                 /* tp_descr_get */
		0,                                  /* tp_descr_set */
		0, //offsetof(PyFunctionObject, func_dict),      /* tp_dictoffset */
		0,                                      /* tp_init */
		0,                                      /* tp_alloc */
		ClassObjectNew,                                      /* tp_new */
		0,                                      /* tp_free */
		0,                                      /* tp_is_gc */
		0,                                      /* tp_bases */
		0,                                      /* tp_mro */
		0,                                      /* tp_cache */
		0,                                      /* tp_subclasses */
		0,                                      /* tp_weaklist */
#if PYTHON_API_VERSION >= 1012
		0                                       /* tp_del */
#endif
	};
}