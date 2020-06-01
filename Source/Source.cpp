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
	const unsigned int redoTest = 100;
	float initTimeAvg = 0;
	float allocTimeAvg = 0;
	float deallocTimeAvg = 0;
	char** pointerHolder = new char*[instancesToAllocate];
	char* start;
	char* end;
	// StackAllocator test!

	for (int j = 0; j < redoTest; j++)
	{
		g_profiler.start();
		size_t toAlloc = sizePerInstance * instancesToAllocate;
		start = (char*)malloc(toAlloc);
		end = start + toAlloc;
		StackAllocator alloc(start, end, sizePerInstance);
		g_profiler.end();
		initTimeAvg += g_profiler.getDuration();
		g_profiler.start();

		for (int i = 0; i < instancesToAllocate; i++)
		{
			pointerHolder[i] = (char*)alloc.Allocate();
		}
		g_profiler.end();

		allocTimeAvg = g_profiler.getDuration();

		g_profiler.start();
		for (int i = 0; i < instancesToAllocate; i++)
		{
			alloc.Return(pointerHolder[i]);
		}
		g_profiler.end();
		deallocTimeAvg = g_profiler.getDuration();
	}
	
	// calc and print
	initTimeAvg /= redoTest;
	allocTimeAvg /= redoTest;
	deallocTimeAvg /= redoTest;
	g_profiler.print("StackTest.txt", std::to_string(sizePerInstance) + ", " + std::to_string(instancesToAllocate) + ", " + std::to_string(initTimeAvg) + ", " + std::to_string(allocTimeAvg) + ", " + std::to_string(deallocTimeAvg) + "\n");
	// reset
	initTimeAvg = 0;
	allocTimeAvg = 0;
	deallocTimeAvg = 0;

	// PoolAllocator test!
	for (int j = 0; j < redoTest; j++)
	{
		g_profiler.start();
		size_t size = PoolAllocator::CalcSizeToAlloc(sizePerInstance, instancesToAllocate);
		start = (char*)malloc(size);
		PoolAllocator pool(start, (char*)(start + size), sizePerInstance);
		g_profiler.end();
		initTimeAvg += g_profiler.getDuration();
		
		g_profiler.start();
		for (int i = 0; i < instancesToAllocate; i++)
			pointerHolder[i] = (char*)pool.Allocate();
		g_profiler.end();
		allocTimeAvg = g_profiler.getDuration();
		
		g_profiler.start();
		for (int i = 0; i < instancesToAllocate; i++)
			pool.Return(pointerHolder[i]);
		g_profiler.end();
		deallocTimeAvg += g_profiler.getDuration();
	}

	// calc and print
	initTimeAvg /= redoTest;
	allocTimeAvg /= redoTest;
	deallocTimeAvg /= redoTest;
	g_profiler.print("PoolTest.txt", std::to_string(sizePerInstance) + ", " + std::to_string(instancesToAllocate) + ", " + std::to_string(initTimeAvg) + ", " + std::to_string(allocTimeAvg) + ", " + std::to_string(deallocTimeAvg) + "\n");
	
	// reset
	initTimeAvg = 0;
	allocTimeAvg = 0;
	deallocTimeAvg = 0;

	// Malloc test!
	for (int j = 0; j < redoTest; j++)
	{
		g_profiler.start();
		for (int i = 0; i < instancesToAllocate; i++)
			pointerHolder[i] = (char*)malloc(sizePerInstance);
		g_profiler.end();
		allocTimeAvg += g_profiler.getDuration();

		g_profiler.start();
		for (int i = 0; i < instancesToAllocate; i++)
			free(pointerHolder[i]);
		g_profiler.end();
		deallocTimeAvg += g_profiler.getDuration();
	}
	
	// calc and print
	allocTimeAvg /= redoTest;
	deallocTimeAvg /= redoTest;
	g_profiler.print("MallocTest.txt", std::to_string(sizePerInstance) + ", " + std::to_string(instancesToAllocate) + ", -, " + std::to_string(allocTimeAvg) + ", " + std::to_string(deallocTimeAvg) + "\n");
	// reset
	allocTimeAvg = 0;
	deallocTimeAvg = 0;

	// Finish tests.
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