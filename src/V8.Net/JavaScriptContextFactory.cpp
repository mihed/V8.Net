#include "stdafx.h"
#include "JavaScriptContextFactory.h"
#include "JavaScriptContextFactoryException.h"
#include "InteropHelper.h"

using namespace System;
using namespace System::Threading;
using namespace System::IO;
using namespace System::Reflection;

namespace V8Net {

	JavaScriptContext^ JavaScriptContextFactory::CreateContext()
	{
		try
		{
			Monitor::Enter(_locker);
			if (!_isInitialized)
				throw gcnew JavaScriptContextFactoryException("The JavaScript runtime has not been initialized");

			if (_isDestroyed)
				throw gcnew JavaScriptContextFactoryException("The JavaScript runtime has been destroyed and cannot be restarted");

			return gcnew JavaScriptContext();
		}
		finally
		{
			Monitor::Exit(_locker);
		}
	}

	void JavaScriptContextFactory::InitializeRuntime()
	{
		String^ assemblyPath = Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location);
		String^ nativeBlob = Path::Combine(assemblyPath, "natives_blob.bin");
		String^ snapshotBlob = Path::Combine(assemblyPath, "snapshot_blob.bin");
		
		if (!File::Exists(nativeBlob))
			throw gcnew JavaScriptContextFactoryException("The native blob is not found");
		if (!File::Exists(snapshotBlob))
			throw gcnew JavaScriptContextFactoryException("The snapshot blob is not found");

		try
		{
			Monitor::Enter(_locker);

			if (_isDestroyed)
				throw gcnew JavaScriptContextFactoryException("The JavaScript runtime has been destroyed and cannot be restarted");

			if (_isInitialized)
				return;

			auto nativeString = InteropHelper::ConvertToUtf8String(nativeBlob);
			auto snapshotString = InteropHelper::ConvertToUtf8String(snapshotBlob);
			v8::V8::InitializeICU();
			v8::V8::InitializeExternalStartupData(nativeString.c_str(), snapshotString.c_str());
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

			if (_isDestroyed)
				return;

			v8::V8::Dispose();
			v8::V8::ShutdownPlatform();
			delete _platform;

			_isDestroyed = true;
		}
		finally
		{
			Monitor::Exit(_locker);
		}
	}

	System::String^ JavaScriptContextFactory::V8Version::get()
	{
		return gcnew System::String(v8::V8::GetVersion());
	}
}
