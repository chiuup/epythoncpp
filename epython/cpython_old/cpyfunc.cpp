#include <Python.h>
#include "cpyfunc.h"

typedef struct {
	PyObject_HEAD
} CPyFuncObject;

PyObject* CPyFuncObjectCall(PyObject* callableObj, PyObject *args, PyObject* kw);

static PyTypeObject CPyFuncType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"cpyfunc",					/* tp_name */
	sizeof(CPyFuncObject),		/* tp_basicsize */
	0,							/* tp_itemsize */
	CPyFuncObjectDealloc,		/* tp_dealloc */
	0,							/* tp_print */
	0,							/* tp_getattr */
	0,							/* tp_setattr */
	0,							/* tp_reserved */
	0,							/* tp_repr */
	0,							/* tp_as_number */
	0,							/* tp_as_sequence */
	0,							/* tp_as_mapping */
	0,							/* tp_hash  */
	CPyFuncObjectCall,			/* tp_call */
	0,							/* tp_str */
	0,							/* tp_getattro */
	0,							/* tp_setattro */
	0,							/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,			/* tp_flags */
	"CPyFuncObject",			/* tp_doc */
	0,							/* tp_traverse */
	0,							/* tp_clear */
	0,							/* tp_richcompare */
	0,							/* tp_weaklistoffset */
	0,							/* tp_iter */
	0,							/* tp_iternext */
	0,							/* tp_methods */
	0,							/* tp_members */
	0,							/* tp_getset */
	0,							/* tp_base */
	0,							/* tp_dict */
	0,							/* tp_descr_get */
	0,							/* tp_descr_set */
	0,							/* tp_dictoffset */
	(initproc)CPyFuncObjectInit,	/* tp_init */
	CPyFuncObjectAlloc,			/* tp_alloc */
	CPyFuncObjectNew,			/* tp_new */
};