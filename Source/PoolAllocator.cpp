#include "PoolAllocator.h"
#include <new>

PoolAllocator::PoolAllocator(char * start, char * end, size_t sizeOfObject): m_pStart(start), m_pEnd(end), m_pHead((entry*)start)
{
	int nrOfEntries = (m_pEnd - m_pStart) / (sizeOfObject + sizeof(entry)) - 1;
	int sizePerEntry = sizeOfObject + sizeof(entry);
	char* curr = (char*)m_pHead;
	curr += sizePerEntry;
	while(curr < m_pEnd - sizePerEntry)
	{
		entry* next = new(curr + sizePerEntry) entry;
		next->next = m_pHead;
		m_pHead = next;
		curr += sizePerEntry;
	}
}

PoolAllocator::~PoolAllocator()
{
	free(m_pStart);
}

void * PoolAllocator::Allocate()
{
	void* pToReturn = nullptr;

	if (m_pHead != nullptr)
	{
		char* ptr = (char*)m_pHead;
		pToReturn = (void*)(ptr + sizeof(entry));
		m_pHead = m_pHead->next;
	}

	return pToReturn;
}

void PoolAllocator::Return(void * ptr)
{
	if ((char*)ptr > m_pStart && (char*)ptr < m_pEnd)
	{
		entry* next = (entry*)((char*)ptr - sizeof(entry));
		next->next = m_pHead;
		m_pHead = next;
	}
}
