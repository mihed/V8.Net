#pragma once
#include <v8.h>

using namespace System;

namespace V8Net {

 	public ref class JavaScriptInterop sealed
	{
		static v8::Handle<v8::Number> ConvertToV8Value(v8::Isolate* isolate, double value);
		static v8::Handle<v8::Boolean> ConvertToV8Value(v8::Isolate* isolate, bool value);
		static v8::Handle<v8::Value> ConvertToV8Value(v8::Isolate* isolate, DateTime value);

		static double ConvertFromV8Value(v8::Handle<v8::Number> value);
		static bool ConvertFromV8Value(v8::Handle<v8::Boolean> value);
		static DateTime ConvertFromV8Value(v8::Handle<v8::Date> value);
	};
}

