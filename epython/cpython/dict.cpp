#include <assert.h>
#include "dict.h"
using namespace CPython;

Dict::Dict() :Object() {
	// New reference, DECREF in base destructor
	PyObject* dict = PyDict_New();
	assert(dict != NULL);
	pyObject_ = dict;
}

void Dict::Set(Object& key, Object& value) {
	PyDict_SetItem(pyObject(), key.pyObject(), value.pyObject());
}

void Dict::Set(const char* key, Object& value)
{
	PyDict_SetItemString(pyObject(), key, value.pyObject());
}

bool Dict::Contains(const Object& key)
{
	return PyDict_Contains(pyObject(), key.pyObject()) ? true : false;
}

bool Dict::Contains(const char * key)
{
	Object pyKey(NewReference(PyUnicode_FromString(key)));
	return Contains(pyKey);
}

