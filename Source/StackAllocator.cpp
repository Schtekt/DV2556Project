#include "StackAllocator.h"
#include <cstdlib>


StackAllocator::StackAllocator(char* start, char* end, size_t size): m_pStart(start), m_pEnd(end), m_pCurr(start), m_size(size)
{

}

StackAllocator::~StackAllocator()
{
	free(m_pStart);
}

void* StackAllocator::Allocate()
{
	void* toReturn = nullptr;
	if (m_pCurr + m_size <= m_pEnd)
	{
		toReturn = m_pCurr;
		m_pCurr += m_size;
	}
	return toReturn;
}

void StackAllocator::Return(void* ptr)
{
	if (((char*)ptr) < m_pCurr && m_pStart <= ((char*)ptr))
	{
		m_pCurr = (char*)ptr;
	}
}

void StackAllocator::Release()
{
	m_pCurr = m_pStart;
}
