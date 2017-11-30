#include <assert.h>
#include "cpydict.h"

CPyDict::CPyDict()
{
	// New reference, DECREF in base destructor
	PyObject* dict = PyDict_New();
	assert(dict != NULL);
	pyObject_ = dict;
}

void CPyDict::Set(CPyObject * key, CPyObject * value)
{
	PyDict_SetItem(pyObject(), key->pyObject(), value->pyObject());
}

void CPyDict::Set(const char * key, CPyObject * value)
{
	PyDict_SetItemString(pyObject(), key, value->pyObject());
}

PyObject * CPyDict::Get(CPyObject * key)
{
	return PyDict_GetItem(pyObject(), key->pyObject());
}

PyObject * CPyDict::Get(const char * key)
{
	return PyDict_GetItemString(pyObject(), key);
}

bool CPyDict::Contains(CPyObject * key)
{
	return PyDict_Contains(pyObject(), key->pyObject()) ? true : false;
}

bool CPyDict::Contains(const char * key)
{
	CPyObject pyKey(PyUnicode_FromString(key));
	return Contains(&pyKey);
}

