#pragma once
#include <v8.h>
#include <libplatform/libplatform.h>

#include "JavascriptContext.h"

namespace V8Net {
	public ref class JavaScriptContextFactory sealed
	{
	private:
		static bool _isInitialized;
		static bool _isDestroyed;
		static v8::Platform* _platform;
		static initonly System::Object^ _locker = gcnew System::Object();
	public:
		static JavaScriptContext^ CreateContext();
		static void InitializeRuntime();
		static void DestroyRuntime();

		property static System::String^ V8Version { System::String^ get(); }

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

