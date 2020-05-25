#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

struct entry
{
	entry* next;
};

class PoolAllocator
{
private:
	char* m_pStart;
	char* m_pEnd;
	char* m_pHead;
public:
	PoolAllocator(char* start, char* end, size_t sizeOfObject);
	~PoolAllocator();
	static size_t CalcSizeToAlloc(size_t sizeOfObject, size_t nrOfObjects);
	void* Allocate();
	void Return(void* ptr);
};

#endif