#include "stdafx.h"
#include "InteropHelper.h"

using namespace System::Runtime::InteropServices;
using namespace System::Text;
using namespace std;

namespace V8Net {

	std::string InteropHelper::ConvertToUtf8String(String^ value)
	{
		if (value->Length == 0)
			return string();

		auto byteArray = Encoding::UTF8->GetBytes(value);
		string result;
		result.resize(byteArray->Length);
		Marshal::Copy(byteArray, 0, IntPtr(&result[0]), byteArray->Length);
		return result;
	}
}
