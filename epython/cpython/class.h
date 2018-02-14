#pragma once
#include <Python.h>
#include "scope.h"
#include "method.h"
#include "converter.h"

namespace CPython {

	template<class T>
	class Class {
	public:
		typedef typename Class<T> Self;

		Class(const char* name, const char* doc) {
			InstanceType.tp_name = name;
			InstanceType.tp_doc = doc;
			if (Py_TYPE(&InstanceType) == 0)
			{
				Py_TYPE(&InstanceType) = &PyType_Type;
				PyType_Ready(&InstanceType);
			}
			PyObject* p = (PyObject*)&InstanceType;

			Private::Scope current;
			Dict moduleDict = current.GetAttr("__dict__");
			moduleDict.Set(name, Object(BorrowedReference(p)));
		}
		Class(const char* name) : Class(name, 0) {}

		virtual ~Class() {}

		static struct InstanceObject : PyObject {
			inline T* instance() {
				return instance_;
			}
			inline void instance(T* i) {
				instance_ = i;
			}
		private:
			T * instance_;
		};
		template<typename T>
		Self& AddVariable(const char* name, T t) {
			Object typeObj = Object(BorrowedReference((PyObject*)&InstanceType));
			Object nameObj = Object::From<const char*>(name);
			PyObject_GenericSetAttr(typeObj.pyObject(), nameObj.pyObject(), Converter<T>::ToPyObject(t));
			return *this;
		}

		template<typename F>
		Self& AddMethod(const char* name, F func, const char* doc)
		{
			Method* funcObj = MakeMethod<F, InstanceObject>(func);
			Object typeObj = Object(BorrowedReference((PyObject*)&InstanceType));

			funcObj->AddToType(typeObj, name, doc);
			Py_DECREF((PyObject*)funcObj);
			return *this;
		}

		template<typename F>
		Self& AddMethod(const char* name, F func) {
			return AddMethod<F>(name, func, 0);
		}

		template<typename F>
		Self& AddInit(F func, const char* doc)
		{
			Method* funcObj = MakeMethod<F, InstanceObject>(func);
			Object typeObj = Object(BorrowedReference((PyObject*)&InstanceType));


			funcObj->AddToType(typeObj, "___init__", doc);
			Py_DECREF((PyObject*)funcObj);
			return *this;
		}

		template<typename F>
		Self& AddInit(F func) {
			return AddInit<F>(func, 0);
		}

		static PyObject* InstanceNew(PyTypeObject *type, PyObject*args, PyObject* kwargs) {
			InstanceObject* self = (InstanceObject*)type->tp_alloc(type, 0);
			assert(self != NULL);
			return (PyObject*)self;
		}
		static void InstanceDealloc(PyObject* p) {
			delete ((InstanceObject*)p)->instance();
			Py_TYPE(p)->tp_free(p);
		}
		static int InstanceInit(PyObject* self, PyObject* args, PyObject* kwargs) {
			Object obj = Object(BorrowedReference(self));
			Tuple argTuple = Tuple(BorrowedReference(args));
			InstanceObject* instanceType = (InstanceObject*)self;
			instanceType->instance(new T());
			obj.GetAttr("___init__")(Object(BorrowedReference(args)), Object(BorrowedReference(kwargs)));
			return 0;
		}

		static PyTypeObject InstanceType;
	private:
		Class();
	};

	template<class T>
	PyTypeObject Class<T>::InstanceType = {
		PyVarObject_HEAD_INIT(NULL, 0)
		"cpython.instance", // tp_name
		sizeof(InstanceObject),
		0,
		InstanceDealloc,					/* tp_dealloc */
		0,                                  /* tp_print */
		0,                                  /* tp_getattr */
		0,                                  /* tp_setattr */
		0,                                  /* tp_compare */
		0,									/* tp_repr */
		0,                                  /* tp_as_number */
		0,                                  /* tp_as_sequence */
		0,                                  /* tp_as_mapping */
		0,                                  /* tp_hash */
		0,									/* tp_call */
		0,                                  /* tp_str */
		0,									/* tp_getattro */
		0,									/* tp_setattro */
		0,                                  /* tp_as_buffer */
		Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE /* | Py_TPFLAGS_HAVE_GC */,/* tp_flags */
		0,                                  /* tp_doc */
		0,									/* tp_traverse */
		0,                                  /* tp_clear */
		0,                                  /* tp_richcompare */
		0,									/* tp_weaklistoffset */
		0,                                  /* tp_iter */
		0,                                  /* tp_iternext */
		0,                                  /* tp_methods */
		0,									/* tp_members */
		0,									/* tp_getset */
		0,                                  /* tp_base */
		0,                                  /* tp_dict */
		0,									/* tp_descr_get */
		0,                                  /* tp_descr_set */
		0,								    /* tp_dictoffset */
		InstanceInit,						/* tp_init */
		PyType_GenericAlloc,				/* tp_alloc */
		InstanceNew,                        /* tp_new */
		0,                                  /* tp_free */
		0,                                  /* tp_is_gc */
		0,                                  /* tp_bases */
		0,                                  /* tp_mro */
		0,                                  /* tp_cache */
		0,                                  /* tp_subclasses */
		0,                                  /* tp_weaklist */
#if PYTHON_API_VERSION >= 1012
		0                                   /* tp_del */
#endif
	};
}