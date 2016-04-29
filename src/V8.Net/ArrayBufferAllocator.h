#pragma once
#include <v8.h>

namespace V8Net
{
	class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator
	{
	public:
		virtual void* Allocate(size_t length) override;
		virtual void* AllocateUninitialized(size_t length) override;
		virtual void Free(void* data, size_t) override;
	};
}

