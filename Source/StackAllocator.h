#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

class StackAllocator
{
private:
	char* m_pStart;
	char* m_pCurr;
	char* m_pEnd;
	size_t m_size;
public:
	StackAllocator(char* start, char* end, size_t size);
	~StackAllocator();
	void* Allocate();
	void Return(void* ptr);
	void Release();

};

#endif
