#pragma once
#include <optional>
#include "CMyListIterator.h"

template<typename T>
class CMyList
{
	struct CMyListMember
	{
		CMyListMember()
			: prev(nullptr), next(nullptr)
		{
		}

		CMyListMember(const T& data, CMyListMember* prev, CMyListMember* next)
			: data(data), prev(prev), next(next)
		{
		}

		CMyListMember(const T&& data, CMyListMember* prev, CMyListMember* next)
			: data(data), prev(prev), next(next)
		{
		}

		~CMyListMember()
		{
			if (!next)
			{
				delete next;
			}
			if (!prev)
			{
				delete prev;
			}
			
		}

		std::optional<T> data;

		CMyListMember* prev;
		CMyListMember* next;
	};

public:
	using Iterator = CListIterator<CMyListMember, T>;
	using ConstIterator = CListIterator<CMyListMember, const T>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CMyList();
	CMyList(const CMyList& list);
	~CMyList();

	Iterator begin();
	Iterator end();
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	Iterator Insert(Iterator const& pos, T const& data);
	Iterator Erase(Iterator const& pos);

	void PushFront(const T& data);
	void PushBack(const T& data);

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	CMyList<T>& operator=(const CMyList<T>& rhs);
private:
	size_t m_size;

	CMyListMember* m_first;
	CMyListMember* m_last;
};

template <typename T>
CMyList<T>::CMyList()
	: m_size(0)
{
	try
	{
		m_first = new CMyListMember;
		m_last = new CMyListMember;
		m_first->next = m_last;
		m_last->prev = m_first;
	}
	catch (const std::exception& error)
	{
		throw error;
	}
}

template <typename T>
CMyList<T>::CMyList(const CMyList& list)
	: CMyList()
{
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		PushBack(*it);
	}
}

template <typename T>
CMyList<T>::~CMyList()
{
	Clear();
	m_first->next = nullptr;
	m_last->prev = nullptr;
}

template <typename T>
CMyList<T>& CMyList<T>::operator=(const CMyList<T>& rhs)
{
	if (std::addressof(rhs) != this)
	{
		CMyList<T> copy(rhs);
		std::swap(m_first, copy.m_first);
		std::swap(m_last, copy.m_last);
		std::swap(m_size, copy.m_size);
	}

	return *this;
}

template <typename T>
void CMyList<T>::Clear()
{
	if (m_first->next != m_last)
	{
		CMyListMember* node = m_first->next;
		m_first->next = m_last;
		node->prev = nullptr;
		m_last->prev->next = nullptr;
		delete node;

		m_size = 0;
	}
}

template <typename T>
typename CMyList<T>::Iterator CMyList<T>::begin()
{
	return Iterator(m_first->next);
}

template <typename T>
typename CMyList<T>::Iterator CMyList<T>::end()
{
	return Iterator(m_last);
}

template <typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cbegin() const
{
	return ConstIterator(m_first->next);
}

template <typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cend() const
{
	return ConstIterator(m_last);
}

template <typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::rbegin()
{
	return std::reverse_iterator<Iterator>(end());
}

template <typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::rend()
{
	return std::reverse_iterator<Iterator>(begin());
}

template <typename T>
typename CMyList<T>::Iterator CMyList<T>::Insert(Iterator const& pos, T const& data)
{
	auto newNode = new CMyListMember(data, nullptr, nullptr);

	CMyListMember* beforeNew = pos.m_pNode->prev;
	CMyListMember* afterNew = beforeNew->next;

	newNode->prev = beforeNew;
	newNode->next = afterNew;

	beforeNew->next = newNode;
	afterNew->prev = newNode;

	++m_size;

	return Iterator(newNode);
}

template <typename T>
typename CMyList<T>::Iterator CMyList<T>::Erase(Iterator const& pos)
{
	CMyListMember* beforePos = pos.m_pNode->prev;
	CMyListMember* afterPos = pos.m_pNode->next;

	pos.m_pNode->prev = nullptr;
	pos.m_pNode->next = nullptr;

	beforePos->next = afterPos;
	afterPos->prev = beforePos;

	--m_size;

	return Iterator(afterPos);
}

template <typename T>
void CMyList<T>::PushFront(const T& data)
{
	auto newNode = new CMyListMember(data, m_first, m_first->next);

	m_first->next = newNode;
	newNode->next->prev = newNode;

	++m_size;
}

template <typename T>
void CMyList<T>::PushBack(const T& data)
{
	auto newNode = new CMyListMember(data, m_last->prev, m_last);

	m_last->prev = newNode;
	newNode->prev->next = newNode;

	++m_size;
}

template <typename T>
size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template <typename T>
bool CMyList<T>::IsEmpty() const
{
	return m_size == 0;
}