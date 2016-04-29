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
	}

	JavaScriptContext::~JavaScriptContext()
	{
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
		throw gcnew NotImplementedException();
	}
}

