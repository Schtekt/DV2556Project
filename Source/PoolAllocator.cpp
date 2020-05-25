#include "PoolAllocator.h"
#include <new>

PoolAllocator::PoolAllocator(char * start, char * end, size_t sizeOfObject): m_pStart(start), m_pEnd(end), m_pHead(start)
{
	int nrOfEntries = (m_pEnd - m_pStart) / (sizeOfObject + sizeof(entry));
	int sizePerEntry = sizeOfObject + sizeof(entry);
	for (int i = 0; i < nrOfEntries; i++)
	{
		((entry*)m_pHead)->next = (entry*)(m_pHead + sizePerEntry);
		m_pHead = m_pHead + sizePerEntry;
	}
	m_pHead = m_pStart;
}

PoolAllocator::~PoolAllocator()
{
	free(m_pStart);
}

size_t PoolAllocator::CalcSizeToAlloc(size_t sizeOfObject, size_t nrOfObjects)
{
	return (sizeOfObject + sizeof(entry))*nrOfObjects;
}

void * PoolAllocator::Allocate()
{
	void* pToReturn = nullptr;

	if (m_pHead != m_pEnd)
	{
		char* ptr = (char*)m_pHead;
		pToReturn = (void*)(ptr + sizeof(entry));
		m_pHead = ((char*)((entry*)m_pHead)->next);
	}

	return pToReturn;
}

void PoolAllocator::Return(void * ptr)
{
	if ((char*)ptr > m_pStart && (char*)ptr < m_pEnd)
	{
		entry* next = (entry*)((char*)ptr - sizeof(entry));
		next->next = (entry*)m_pHead;
		m_pHead = (char*)next;
	}
}
