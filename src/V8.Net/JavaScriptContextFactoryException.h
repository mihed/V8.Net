#pragma once

using namespace System;

namespace V8Net
{
	ref class JavaScriptContextFactoryException : Exception
	{
	public:
		JavaScriptContextFactoryException(){};
		JavaScriptContextFactoryException(String^ message) :
			Exception(message){};
	};
}

