#pragma once
#include <string>

using namespace System;

namespace V8Net {

	public ref class InteropHelper
	{
	public:
		static std::string ConvertToUtf8String(String^ value);
	};
}

