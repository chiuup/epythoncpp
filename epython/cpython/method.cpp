#include "tuple.h"
#include "converter.h"
#include "method.h"

namespace CPython {
	static void MethodDealloc(PyObject* p);
	static PyObject* MethodCall(PyObject* self, PyObject* args, PyObject* kwargs);
	// Stolen from Python's funcobject.c
	static PyObject* MethodDescrGet(PyObject *func, PyObject *obj, PyObject *type_);

	static PyObject* MethodGetName(PyObject* obj, void *);
	static PyObject* MethodGetModule(PyObject* obj, void *);
	static PyObject* MethodGetClass(PyObject* obj, void *);
	static PyObject* MethodGetDoc(PyObject* obj, void *);

	static PyGetSetDef MethodGetSetList[] = {
		{ "__name__", (getter)MethodGetName, 0, 0, 0 },
	{ "func_name", (getter)MethodGetName, 0, 0, 0 },
	{ "__module__", (getter)MethodGetModule, 0, 0, 0 },
	{ "func_module", (getter)MethodGetModule, 0, 0, 0 },
	{ "__class__", (getter)MethodGetClass, 0, 0, 0 },    // see note above
	{ "__doc__", (getter)MethodGetDoc, 0, 0, 0 },
	{ "func_doc", (getter)MethodGetDoc, 0, 0, 0 },
	{ NULL, 0, 0, 0, 0 } /* Sentinel */
	};

	PyTypeObject MethodType = {
		PyVarObject_HEAD_INIT(NULL, 0)
		"cpython.method",
		sizeof(Method),
		0,
		(destructor)MethodDealloc,               /* tp_dealloc */
		0,                                  /* tp_print */
		0,                                  /* tp_getattr */
		0,                                  /* tp_setattr */
		0,                                  /* tp_compare */
		0, //(reprfunc)func_repr,                   /* tp_repr */
		0,                                  /* tp_as_number */
		0,                                  /* tp_as_sequence */
		0,                                  /* tp_as_mapping */
		0,                                  /* tp_hash */
		MethodCall,                              /* tp_call */
		0,                                  /* tp_str */
		0, // PyObject_GenericGetAttr,            /* tp_getattro */
		0, // PyObject_GenericSetAttr,            /* tp_setattro */
		0,                                  /* tp_as_buffer */
		Py_TPFLAGS_DEFAULT /* | Py_TPFLAGS_HAVE_GC */,/* tp_flags */
		0,                                  /* tp_doc */
		0, // (traverseproc)func_traverse,          /* tp_traverse */
		0,                                  /* tp_clear */
		0,                                  /* tp_richcompare */
		0, //offsetof(PyFunctionObject, func_weakreflist), /* tp_weaklistoffset */
		0,                                  /* tp_iter */
		0,                                  /* tp_iternext */
		0,                                  /* tp_methods */
		0, // func_memberlist,              /* tp_members */
		MethodGetSetList,                /* tp_getset */
		0,                                  /* tp_base */
		0,                                  /* tp_dict */
		MethodDescrGet,                 /* tp_descr_get */
		0,                                  /* tp_descr_set */
		0, //offsetof(PyFunctionObject, func_dict),      /* tp_dictoffset */
		0,                                      /* tp_init */
		0,                                      /* tp_alloc */
		0,                                      /* tp_new */
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

	void MethodDealloc(PyObject * p)
	{
		delete static_cast<Method*>(p);
	}
	PyObject * MethodCall(PyObject * self, PyObject * args, PyObject * kwargs)
	{
		Method* func = static_cast<Method*>(self);
		return func->operator()(self, args, kwargs);
	}
	PyObject * MethodDescrGet(PyObject * func, PyObject * obj, PyObject * type_)
	{
		// The implement is different in Python 3 because of the removal of unbound method
		if (obj == Py_None || obj == NULL) {
			Py_INCREF(func);
			return func;
		}
		return PyMethod_New(func, obj);
	}
	PyObject * MethodGetName(PyObject * obj, void *)
	{
		Method* func = (Method*)obj;
		PyObject* result = func->name().pyObject();
		Py_XINCREF(result);
		return result;
	}
	PyObject * MethodGetModule(PyObject * obj, void *)
	{
		Method* func = (Method*)obj;
		PyObject* result = func->module().pyObject();
		Py_XINCREF(result);
		return result;
	}
	PyObject * MethodGetClass(PyObject * obj, void *)
	{
		PyObject* result = (PyObject*)&PyCFunction_Type;
		Py_XINCREF(result);
		return result;
	}
	PyObject * MethodGetDoc(PyObject * obj, void *)
	{
		Method* func = (Method*)obj;
		PyObject* result = func->doc().pyObject();
		Py_XINCREF(result);
		return result;
	}
	Method::Method(Private::MethodInvokerBase * invoker) : invoker_(invoker)
	{
		PyObject* p = this;
		if (Py_TYPE(&MethodType) == 0)
		{
			Py_TYPE(&MethodType) = &PyType_Type;
			PyType_Ready(&MethodType);
		}

		(void)(     // warning suppression for GCC
			PyObject_INIT(p, &MethodType)
			);
	}
}