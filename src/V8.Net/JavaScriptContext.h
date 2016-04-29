#pragma once
#include <v8.h>
#include "ArrayBufferAllocator.h"

using namespace System;

namespace V8Net {

	public ref class JavaScriptContext : public System::IDisposable
	{
	private:
		ArrayBufferAllocator* _allocator;
		v8::Isolate* _isolate;
	public:
		JavaScriptContext();
		~JavaScriptContext();

		System::Object^ GetParameter(System::String^ name);

		void SetParameter(System::String^ name, System::Object^ object);

		void TerminateExecution();
	};
}
