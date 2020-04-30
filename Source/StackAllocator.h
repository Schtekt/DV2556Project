#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

class StackAllocator
{
private:
	char* m_pStart;
	char* m_pCurr;
	char* m_pEnd;
	StackAllocator(size_t size);
public:
	~StackAllocator();
	void* Allocate(size_t size);
	void DeAllocate(void* ptr);
	static StackAllocator* Init(size_t size);
	void FreeAll();
	void SetMemRange(size_t size);
};

#endif
