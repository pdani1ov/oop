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

		CMyListMember(const T& data, std::shared_ptr<CMyListMember> prev, std::shared_ptr<CMyListMember> next)
			: data(data), prev(prev), next(next)
		{
		}

		CMyListMember(const T&& data, std::shared_ptr<CMyListMember> prev, std::shared_ptr<CMyListMember> next)
			: data(data), prev(prev), next(next)
		{
		}

		std::optional<T> data;

		std::shared_ptr<CMyListMember> prev;
		std::shared_ptr<CMyListMember> next;
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

	std::shared_ptr<CMyListMember> m_first;
	std::shared_ptr<CMyListMember> m_last;
};

template <typename T>
CMyList<T>::CMyList()
	: m_size(0), m_first(std::make_shared<CMyListMember>()), m_last(std::make_shared<CMyListMember>())
{
	m_first->next = m_last;
	m_last->prev = m_first;
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
	std::shared_ptr<CMyListMember> node = m_first->next;

	while (node->next != nullptr)
	{
		m_first->next = node->next;
		node->next->prev = m_first;

		node->prev = nullptr;
		node->next = nullptr;

		node = m_first->next;
	}

	m_size = 0;
}

template <typename T>
typename CMyList<T>::Iterator CMyList<T>::begin()
{
	return Iterator(m_first->next.get());
}

template <typename T>
typename CMyList<T>::Iterator CMyList<T>::end()
{
	return Iterator(m_last.get());
}

template <typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cbegin() const
{
	return ConstIterator(m_first->next.get());
}

template <typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cend() const
{
	return ConstIterator(m_last.get());
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
	auto newNode = std::make_shared<CMyListMember>(data, nullptr, nullptr);

	std::shared_ptr<CMyListMember> beforeNew = pos.m_pNode->prev;
	std::shared_ptr<CMyListMember> afterNew = beforeNew->next;

	newNode->prev = beforeNew;
	newNode->next = afterNew;

	beforeNew->next = newNode;
	afterNew->prev = newNode;

	++m_size;

	return Iterator(newNode.get());
}

template <typename T>
typename CMyList<T>::Iterator CMyList<T>::Erase(Iterator const& pos)
{
	std::shared_ptr<CMyListMember> beforePos = pos.m_pNode->prev;
	std::shared_ptr<CMyListMember> afterPos = pos.m_pNode->next;

	pos.m_pNode->prev = nullptr;
	pos.m_pNode->next = nullptr;

	beforePos->next = afterPos;
	afterPos->prev = beforePos;

	--m_size;

	return Iterator(afterPos.get());
}

template <typename T>
void CMyList<T>::PushFront(const T& data)
{
	auto newNode = std::make_shared<CMyListMember>(data, m_first, m_first->next);

	m_first->next = newNode;
	newNode->next->prev = newNode;

	++m_size;
}

template <typename T>
void CMyList<T>::PushBack(const T& data)
{
	auto newNode = std::make_shared<CMyListMember>(data, m_last->prev, m_last);

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