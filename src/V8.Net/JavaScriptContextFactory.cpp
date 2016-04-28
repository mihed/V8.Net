#include "stdafx.h"
#include "JavaScriptContextFactory.h"

using namespace System::Threading;

namespace V8Net {

	JavaScriptContext^ JavaScriptContextFactory::CreateContext()
	{
		try
		{
			Monitor::Enter(_locker);
			if (!_isInitialized)
				throw gcnew Exception("The engine has not been initialized");

			return gcnew JavaScriptContext();
		}
		finally
		{
			Monitor::Exit(_locker);
		}
	}

	void JavaScriptContextFactory::InitializeRuntime()
	{
		try
		{
			Monitor::Enter(_locker);
			if (_isInitialized)
				return;

			v8::V8::InitializeICU();
			_platform = v8::platform::CreateDefaultPlatform();
			v8::V8::InitializePlatform(_platform);
			v8::V8::Initialize();

			_isInitialized = true;
		}
		finally
		{
			Monitor::Exit(_locker);
		}
	}

	void JavaScriptContextFactory::DestroyRuntime()
	{
		try
		{
			Monitor::Enter(_locker);
			if (!_isInitialized)
				return;

			v8::V8::Dispose();
			v8::V8::ShutdownPlatform();
			delete _platform;

			_isInitialized = false;
		}
		finally
		{
			Monitor::Exit(_locker);
		}
	}
	
}
