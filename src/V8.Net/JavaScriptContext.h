#pragma once
#include <v8.h>

using namespace System;

namespace V8Net {

	public ref class JavaScriptContext : public System::IDisposable
	{
		// TODO: Add your methods for this class here.
	public:
		JavaScriptContext();
		~JavaScriptContext();
	};
}
