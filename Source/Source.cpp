#include <crtdbg.h>
#include "StackAllocator.h"
#include <cstdlib>
#include "Profiler.h"
#include <iostream>
#include "PoolAllocator.h"
Profiler g_profiler;
void StackAllocTest(int nrOfIntegers)
{
	g_profiler.start();

	size_t toAlloc = nrOfIntegers * sizeof(int);
	char* start = (char*)malloc(toAlloc);
	char* end = (char*)(start + toAlloc);
	StackAllocator alloc(start, end, sizeof(int));

	g_profiler.end();
	g_profiler.print("test.txt", "Stackallocator init: ");

	g_profiler.start();

	for (int i = 0; i < nrOfIntegers; i++)
	{
		int* tmp = (int*)alloc.Allocate();
		*tmp = 5;
	}
	g_profiler.end();
	g_profiler.print("test.txt", "StackAllocator allocating " + std::to_string(nrOfIntegers) + " integers");

	g_profiler.start();
	for (int i = 0; i < nrOfIntegers; i++)
	{
		alloc.Return(start + i * (sizeof(int)));
	}
	g_profiler.end();
	g_profiler.print("test.txt", "StackAllocator deallocating " + std::to_string(nrOfIntegers) + " integers");
}

void PoolAllocTest(int nrOfIntegers)
{
	g_profiler.start();
	size_t toAlloc = nrOfIntegers * (sizeof(int) + sizeof(entry));
	char* start = (char*)malloc(toAlloc);
	char* end = start + toAlloc;
	PoolAllocator alloc(start, end, sizeof(int));

	g_profiler.end();
	g_profiler.print("test.txt", "PoolAllocator init: ");

	g_profiler.start();

	for (int i = 0; i < nrOfIntegers; i++)
	{
		int* tmp = (int*)alloc.Allocate();
		*tmp = 5;
	}
	g_profiler.end();
	g_profiler.print("test.txt", "PoolAllocator allocating " + std::to_string(nrOfIntegers) + " integers");

	g_profiler.start();
	for (int i = 0; i < nrOfIntegers; i++)
	{
		alloc.Return(start + i * ((sizeof(int) + sizeof(entry))));
	}
	g_profiler.end();
	g_profiler.print("test.txt", "PoolAllocator deallocating " + std::to_string(nrOfIntegers) + " integers");
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	StackAllocTest(1000000);
	PoolAllocTest(1000000);

	return 0;
}