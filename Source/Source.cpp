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

void AllocationTests(const size_t sizePerInstance, const size_t instancesToAllocate)
{
	float initTime;
	float allocationTime;
	float deallocationTime;
	char** pointerHolder = new char*[instancesToAllocate];

	// StackAllocator test!
	g_profiler.start();
	size_t toAlloc = sizePerInstance * instancesToAllocate;
	char* start = (char*)malloc(toAlloc);
	char* end = start + toAlloc;
	StackAllocator alloc(start,end,sizePerInstance);
	g_profiler.end();
	initTime = g_profiler.getDuration();
	g_profiler.print("stackTest.txt", "Setup of StackAllocator with " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes as maximum allowed allocated memory.");
	
	g_profiler.start();

	for (int i = 0; i < instancesToAllocate; i++)
	{
		pointerHolder[i] = (char*)alloc.Allocate();
	}
	g_profiler.end();
	allocationTime = g_profiler.getDuration();
	g_profiler.print("stackTest.txt", "Allocation of " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes of memory with StackAllocator: " + std::to_string(g_profiler.getDuration()));
	
	g_profiler.start();
	for (int i = 0; i < instancesToAllocate; i++)
	{
		alloc.Return(pointerHolder[i]);
	}
	g_profiler.end();
	deallocationTime = g_profiler.getDuration();
	g_profiler.print("stackTest.txt", "Deallocation of " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes of memory with StackAllocator: " + std::to_string(g_profiler.getDuration()));

	g_profiler.print("stackTest.txt", "Total time to allocate and deallocate " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + 
		" bytes of memory with StackAllocator " + std::to_string(initTime + allocationTime + deallocationTime));
	g_profiler.print("stackTest.txt", "\n");


	// PoolAllocator test!
	g_profiler.start();
	size_t size = PoolAllocator::CalcSizeToAlloc(sizePerInstance, instancesToAllocate);
	start = (char*)malloc(size);
	PoolAllocator pool(start,(char*)(start + size), sizePerInstance);
	g_profiler.end();
	initTime = g_profiler.getDuration();
	g_profiler.print("poolTest.txt", "Setup of PoolAllocator with " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes as maximum allowed allocated memory: " + std::to_string(g_profiler.getDuration()));

	g_profiler.start();
	for (int i = 0; i < instancesToAllocate; i++)
		pointerHolder[i] = (char*)pool.Allocate();
	g_profiler.end();
	allocationTime = g_profiler.getDuration();
	g_profiler.print("poolTest.txt", "Allocation of " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes of memory with PoolAllocator: " + std::to_string(g_profiler.getDuration()));
	
	g_profiler.start();
	for (int i = 0; i < instancesToAllocate; i++)
		pool.Return(pointerHolder[i]);
	g_profiler.end();
	deallocationTime = g_profiler.getDuration();
	g_profiler.print("poolTest.txt", "Deallocation of " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes of memory with PoolAllocator: " + std::to_string(g_profiler.getDuration()));
	g_profiler.print("poolTest.txt", "Total time to allocate and deallocate " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) +
		" bytes of memory with PoolAllocator " + std::to_string(initTime + allocationTime + deallocationTime));
	g_profiler.print("poolTest.txt", "\n");

	// Malloc test!

	g_profiler.start();
	for (int i = 0; i < instancesToAllocate; i++)
		pointerHolder[i] = (char*)malloc(sizePerInstance);
	g_profiler.end();
	allocationTime = g_profiler.getDuration();
	g_profiler.print("mallocTest.txt", "Allocation of " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes of memory with malloc: " + std::to_string(g_profiler.getDuration()));

	g_profiler.start();
	for (int i = 0; i < instancesToAllocate; i++)
		free(pointerHolder[i]);
	g_profiler.end();
	deallocationTime = g_profiler.getDuration();
	g_profiler.print("mallocTest.txt", "Deallocation of " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) + " bytes of memory with  malloc: " + std::to_string(g_profiler.getDuration()));

	g_profiler.print("mallocTest.txt", "Total time to allocate and deallocate " + std::to_string(instancesToAllocate) + " instances of " + std::to_string(sizePerInstance) +
		" bytes of memory with malloc " + std::to_string(allocationTime + deallocationTime));
	g_profiler.print("mallocTest.txt", "\n");
	delete[] pointerHolder;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//StackAllocTest(1000000);
	//PoolAllocTest(1000000);
	AllocationTests(32, 10000);
	AllocationTests(16, 10000);
	AllocationTests(4 , 10000);
	AllocationTests(32, 1000000);
	AllocationTests(16, 1000000);
	AllocationTests(4 , 1000000);
	AllocationTests(32, 10000000);
	AllocationTests(16, 10000000);
	AllocationTests(4, 10000000);
	return 0;
}