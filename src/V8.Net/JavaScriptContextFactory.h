#pragma once
#include <v8.h>
#include <libplatform/libplatform.h>

#include "JavascriptContext.h"

using namespace System;

namespace V8Net {
	public ref class JavaScriptContextFactory sealed
	{
	private:
		static bool _isInitialized;
		static v8::Platform* _platform;
		static initonly Object^ _locker = gcnew Object();
	public:
		static JavaScriptContext^ CreateContext();
		static void InitializeRuntime();
		static void DestroyRuntime();
		static property bool IsInitialized
		{
			bool get()
			{
				return _isInitialized;
			}
			void set(bool value)
			{
				_isInitialized = value;
			}
		}
	};
}

