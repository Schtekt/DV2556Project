#include <crtdbg.h>
#include "StackAllocator.h"
#include <cstdlib>
#include "Profiler.h"
#include <iostream>
#include "PoolAllocator.h"

void StackAllocTest(int nrOfIntegers)
{
	size_t toAlloc = nrOfIntegers * sizeof(int);
	char* start = (char*)malloc(toAlloc);
	char* end = (char*)(start + toAlloc);
	StackAllocator alloc(start, end, sizeof(int));

	for (int i = 0; i < nrOfIntegers; i++)
	{
		int* tmp = (int*)alloc.Allocate();
		*tmp = 5;
		alloc.Return(tmp);
	}
}

void PoolAllocTest(int nrOfIntegers)
{
	size_t toAlloc = nrOfIntegers * (sizeof(int) + sizeof(entry));
	char* start = (char*)malloc(toAlloc);
	char* end = (char*)(start + toAlloc);
	PoolAllocator alloc(start, end, sizeof(int));

	for (int i = 0; i < nrOfIntegers; i++)
	{
		int* tmp = (int*)alloc.Allocate();
		*tmp = 5;
		alloc.Return(tmp);
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Profiler profiler;
	profiler.start();

	StackAllocTest(20);
	PoolAllocTest(20);
	profiler.end();
	profiler.print("test.txt", "StackAllocTest:");

	return 0;
}