#include <crtdbg.h>
#include "StackAllocator.h"
#include <cstdlib>
#include "Profiler.h"
#include <iostream>
#include "PoolAllocator.h"

void StackAllocTest()
{
	StackAllocator* alloc = StackAllocator::Init(sizeof(int)*1024);
	for (int i = 0; i < 1024; i++)
	{
		int* tmp = (int*)alloc->Allocate(sizeof(int));
	}
	free(alloc);
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

	//Profiler profiler;
	//profiler.start();

	//StackAllocTest();
	PoolAllocTest(20);
	//profiler.end();
	//profiler.print("test.txt", "StackAllocTest:");

	return 0;
}