#include <os32u4/util/fixes.hh>

void* operator new(size_t size) { return malloc(size); }