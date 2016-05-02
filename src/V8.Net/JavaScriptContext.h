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
		v8::Persistent<v8::Context>* _context;
		bool _isTerminating = false;
	public:
		JavaScriptContext();
		~JavaScriptContext();

		System::Object^ GetParameter(System::String^ name);

		void SetParameter(System::String^ name, System::Object^ object);

		void TerminateExecution();

		property bool IsTerminatingExecution {
			bool get()
			{
				return _isTerminating;
			}
			void set(bool value)
			{
				_isTerminating = value;
			}
		}
	};
}
