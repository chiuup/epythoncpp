#include "tuple.h"
#include "converter.h"
#include "function.h"

namespace CPython {
	static void FunctionDealloc(PyObject* p);
	static PyObject* FunctionCall(PyObject* self, PyObject* args, PyObject* kwargs);
	// Stolen from Python's funcobject.c
	static PyObject* FunctionDescrGet(PyObject *func, PyObject *obj, PyObject *type_);

	static PyObject* FunctionGetName(PyObject* obj, void *);
	static PyObject* FunctionGetModule(PyObject* obj, void *);
	static PyObject* FunctionGetClass(PyObject* obj, void *);
	static PyObject* FunctionGetDoc(PyObject* obj, void *);

	static PyGetSetDef FunctionGetSetList[] = {
		{ "__name__", (getter)FunctionGetName, 0, 0, 0 },
		{ "func_name", (getter)FunctionGetName, 0, 0, 0 },
		{ "__module__", (getter)FunctionGetModule, 0, 0, 0 },
		{ "func_module", (getter)FunctionGetModule, 0, 0, 0 },
		{ "__class__", (getter)FunctionGetClass, 0, 0, 0 },    // see note above
		{ "__doc__", (getter)FunctionGetDoc, 0, 0, 0 },
		{ "func_doc", (getter)FunctionGetDoc, 0, 0, 0 },
		{ NULL, 0, 0, 0, 0 } /* Sentinel */
	};

	PyTypeObject FunctionType = {
		PyVarObject_HEAD_INIT(NULL, 0)
		const_cast<char*>("cpython.function"),
		sizeof(Function),
		0,
		(destructor)FunctionDealloc,               /* tp_dealloc */
		0,                                  /* tp_print */
		0,                                  /* tp_getattr */
		0,                                  /* tp_setattr */
		0,                                  /* tp_compare */
		0, //(reprfunc)func_repr,                   /* tp_repr */
		0,                                  /* tp_as_number */
		0,                                  /* tp_as_sequence */
		0,                                  /* tp_as_mapping */
		0,                                  /* tp_hash */
		FunctionCall,                              /* tp_call */
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
		FunctionGetSetList,                /* tp_getset */
		0,                                  /* tp_base */
		0,                                  /* tp_dict */
		FunctionDescrGet,                 /* tp_descr_get */
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

	void FunctionDealloc(PyObject * p)
	{
		delete static_cast<Function*>(p);
	}
	PyObject * FunctionCall(PyObject * self, PyObject * args, PyObject * kwargs)
	{
		Function* func = static_cast<Function*>(self);
		return func->operator()(self, args, kwargs);
	}
	PyObject * FunctionDescrGet(PyObject * func, PyObject * obj, PyObject * type_)
	{
		// The implement is different in Python 3 because of the removal of unbound method
		if (obj == Py_None || obj == NULL) {
			Py_INCREF(func);
			return func;
		}
		return PyMethod_New(func, obj);
	}
	PyObject * FunctionGetName(PyObject * obj, void *)
	{
		Function* func = (Function*)obj;
		PyObject* result = func->name().pyObject();
		Py_XINCREF(result);
		return result;
	}
	PyObject * FunctionGetModule(PyObject * obj, void *)
	{
		Function* func = (Function*)obj;
		PyObject* result = func->module().pyObject();
		Py_XINCREF(result);
		return result;
	}
	PyObject * FunctionGetClass(PyObject * obj, void *)
	{
		PyObject* result = (PyObject*)&PyCFunction_Type;
		Py_XINCREF(result);
		return result;
	}
	PyObject * FunctionGetDoc(PyObject * obj, void *)
	{
		Function* func = (Function*)obj;
		PyObject* result = func->doc().pyObject();
		Py_XINCREF(result);
		return result;
	}
	Function::Function(Private::FunctionInvokerBase * invoker) : invoker_(invoker)
	{
		PyObject* p = this;
		if (Py_TYPE(&FunctionType) == 0)
		{
			Py_TYPE(&FunctionType) = &PyType_Type;
			PyType_Ready(&FunctionType);
		}

		(void)(     // warning suppression for GCC
			PyObject_INIT(p, &FunctionType)
			);
	}
}