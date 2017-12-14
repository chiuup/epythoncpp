#pragma once
#include <Python.h>

template<class C>
struct CPyClassHolder {

};

template<class C>
static void CPyClass(const char* name, const char* doc) {
	typedef struct {
		PyObject_HEAD
			C* wrapped;
	} wrappedObject;

	static PyTypeObject wrappedType = {
		PyVarObject_HEAD_INIT(NULL, 0)
		"noddy.Noddy",             /* tp_name */
		sizeof(Noddy),             /* tp_basicsize */
		0,                         /* tp_itemsize */
		(destructor)Noddy_dealloc, /* tp_dealloc */
		0,                         /* tp_print */
		0,                         /* tp_getattr */
		0,                         /* tp_setattr */
		0,                         /* tp_reserved */
		0,                         /* tp_repr */
		0,                         /* tp_as_number */
		0,                         /* tp_as_sequence */
		0,                         /* tp_as_mapping */
		0,                         /* tp_hash  */
		0,                         /* tp_call */
		0,                         /* tp_str */
		0,                         /* tp_getattro */
		0,                         /* tp_setattro */
		0,                         /* tp_as_buffer */
		Py_TPFLAGS_DEFAULT |
		Py_TPFLAGS_BASETYPE,   /* tp_flags */
		0,           /* tp_doc */
		0,                         /* tp_traverse */
		0,                         /* tp_clear */
		0,                         /* tp_richcompare */
		0,                         /* tp_weaklistoffset */
		0,                         /* tp_iter */
		0,                         /* tp_iternext */
		Noddy_methods,             /* tp_methods */
		Noddy_members,             /* tp_members */
		0,                         /* tp_getset */
		0,                         /* tp_base */
		0,                         /* tp_dict */
		0,                         /* tp_descr_get */
		0,                         /* tp_descr_set */
		0,                         /* tp_dictoffset */
		(initproc)Noddy_init,      /* tp_init */
		0,                         /* tp_alloc */
		Noddy_new,                 /* tp_new */
	};


}