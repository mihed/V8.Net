// This is the main DLL file.

#include "stdafx.h"
#include "JavaScriptContext.h"

namespace V8Net
{
	JavaScriptContext::JavaScriptContext()
	{
		_allocator = new ArrayBufferAllocator();
		v8::Isolate::CreateParams createParameters;
		createParameters.array_buffer_allocator = _allocator;
		_isolate = v8::Isolate::New(createParameters);
		v8::Isolate::Scope isolateScope(_isolate);
		v8::HandleScope scope(_isolate);
		_context = new v8::Persistent<v8::Context>(_isolate, v8::Context::New(_isolate));
	}

	JavaScriptContext::~JavaScriptContext()
	{
		delete _context;
		_isolate->Dispose();
		delete _allocator;
	}

	System::Object^ JavaScriptContext::GetParameter(System::String^ name)
	{
		throw gcnew NotImplementedException();
	}

	void JavaScriptContext::SetParameter(System::String^ name, System::Object^ object)
	{
		throw gcnew NotImplementedException();
	}

	void JavaScriptContext::TerminateExecution()
	{
		_isTerminating = true;
		v8::V8::TerminateExecution(_isolate);
		_isTerminating = false;
	}
}

