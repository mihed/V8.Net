#include "stdafx.h"
#include "JavaScriptInterop.h"
#include <type_traits>

using namespace std;

namespace V8Net {

	v8::Handle<v8::Number> JavaScriptInterop::ConvertToV8Value(v8::Isolate* isolate, double value)
	{
		return v8::Number::New(isolate, value);
	}

	v8::Handle<v8::Boolean> JavaScriptInterop::ConvertToV8Value(v8::Isolate* isolate, bool value)
	{
		return v8::Boolean::New(isolate, value);
	}

	v8::Handle<v8::Value> JavaScriptInterop::ConvertToV8Value(v8::Isolate* isolate, DateTime value)
	{
		System::DateTime startDate(1970, 1, 1);
		auto timespan = System::TimeSpan::FromTicks(value.Ticks - startDate.Ticks);
		return v8::Date::New(isolate, timespan.TotalMilliseconds);
	}

	double JavaScriptInterop::ConvertFromV8Value(v8::Handle<v8::Number> value)
	{
		return value->Value();
	}

	bool JavaScriptInterop::ConvertFromV8Value(v8::Handle<v8::Boolean> value)
	{
		return value->Value();
	}

	DateTime JavaScriptInterop::ConvertFromV8Value(v8::Handle<v8::Date> value)
	{
		DateTime startDate(1970, 1, 1);
		auto timespan = System::TimeSpan::FromMilliseconds(value->NumberValue());
		return DateTime(timespan.Ticks + startDate.Ticks);
	}

}
