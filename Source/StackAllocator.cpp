#include "StackAllocator.h"
#include <cstdlib>
StackAllocator::StackAllocator(size_t size)
{
	m_pStart = (char*)malloc(size);
	m_pEnd = (m_pStart + size);
	m_pCurr = m_pStart;
}

StackAllocator::~StackAllocator()
{
	FreeAll();
}

void * StackAllocator::Allocate(size_t size)
{
	void* ptr = nullptr;
	if (m_pEnd > m_pCurr + size)
	{
		m_pCurr;
		m_pCurr += size;
	}
	return ptr;
}

void StackAllocator::DeAllocate(void * ptr)
{
	if (ptr < m_pEnd && ptr > m_pStart)
	{
		m_pCurr = (char*)ptr;
	}
}

StackAllocator* StackAllocator::Init(size_t size)
{
	static StackAllocator* pStack;
	if (!pStack)
	{
		pStack = (StackAllocator*)malloc(sizeof(StackAllocator));
		*pStack = StackAllocator(size);
	}
	return pStack;
}

void StackAllocator::FreeAll()
{
	m_pCurr = nullptr;
	free(m_pStart);
	m_pStart = nullptr;
	m_pEnd = nullptr;
}

void StackAllocator::SetMemRange(size_t size)
{
	if (!m_pStart)
	{
		m_pStart = (char*)malloc(size);
		m_pEnd = (m_pStart + size);
		m_pCurr = m_pStart;
	}
}