#pragma once
#include <Python.h>

namespace CPython {
	class GIL {
	private:
		PyGILState_STATE pyGILState_;
	public:
		GIL() {
			pyGILState_ = PyGILState_Ensure();
		}
		~GIL() {
			PyGILState_Release(pyGILState_);
		}
	};
}