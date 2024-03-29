#include <Engine/EngineGlobals.h>

void* operator new(size_t size) {
	return Neowise::GAlloc->allocate(size);
}

void operator delete(void *p, size_t size) {
	Neowise::GAlloc->free(p, size);
}
