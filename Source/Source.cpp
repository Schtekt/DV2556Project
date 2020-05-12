#include <crtdbg.h>
#include "StackAllocator.h"
#include <cstdlib>
#include "Profiler.h"
#include <iostream>

void StackAllocTest()
{
	StackAllocator* alloc = StackAllocator::Init(sizeof(int)*1024);
	for (int i = 0; i < 1024; i++)
	{
		int* tmp = (int*)alloc->Allocate(sizeof(int));
	}
	free(alloc);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Profiler profiler;
	profiler.start();

	StackAllocTest();

	profiler.end();
	profiler.print("test.txt", "StackAllocTest:");

	return 0;
}