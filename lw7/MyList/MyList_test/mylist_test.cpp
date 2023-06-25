#include "../../../catch/catch.hpp"
#include "../MyList/MyList.h"
#include "../MyList/CMyListIterator.h"

TEST_CASE("Checking the list has a size and is it empty or not")
{
	CMyList<int> testList;

	REQUIRE(testList.IsEmpty());
	REQUIRE(testList.GetSize() == 0);

	testList.PushBack(1);
	REQUIRE(!testList.IsEmpty());
	REQUIRE(testList.GetSize() == 1);
}

TEST_CASE("Checking the assignment and copying of the list")
{
	CMyList<int> testList1;
	CMyList<int> testList2;

	REQUIRE(testList1.IsEmpty());
	REQUIRE(testList1.GetSize() == 0);

	testList1.PushBack(1);
	testList2 = testList1;

	REQUIRE(!testList2.IsEmpty());
	REQUIRE(testList2.GetSize() == 1);

	CMyList<int> copyList(testList2);

	REQUIRE(!copyList.IsEmpty());
	REQUIRE(copyList.GetSize() == 1);
}

TEST_CASE("Check push back and front, insert and erase")
{
	CMyList<int> testList;

	testList.PushBack(1);
	REQUIRE(testList.GetSize() == 1);

	testList.PushFront(0);
	REQUIRE(testList.GetSize() == 2);

	testList.Insert(++testList.begin(), 3);
	REQUIRE(testList.GetSize() == 3);

	testList.Erase(--testList.end());
	REQUIRE(testList.GetSize() == 2);

	testList.Clear();
	REQUIRE(testList.GetSize() == 0);
}

TEST_CASE("Check work iterator")
{
	CMyList<int> testList;
	testList.PushBack(1);
	testList.PushBack(2);
	testList.PushBack(3);

	CMyList<int>::Iterator it = testList.begin();
	REQUIRE(*it == 1);
	REQUIRE(1 == *(it++));
	REQUIRE(*it == 2);
	REQUIRE(3 == *(++it));
	REQUIRE(*it == 3);
	
	CMyList<int>::ReverseIterator reit = testList.rend();
	--reit;
	REQUIRE(*reit == 1);
	REQUIRE(1 == *(reit--));
	REQUIRE(*reit == 2);
	REQUIRE(1 == *(++reit));
	REQUIRE(*reit == 1);
	
	CMyList<int>::ConstIterator cbit = testList.cbegin();
	REQUIRE(*cbit == 1);
	REQUIRE(1 == *(cbit++));
	REQUIRE(*cbit == 2);
	REQUIRE(3 == *(++cbit));
	REQUIRE(*cbit == 3);
	
	CMyList<int>::ReverseIterator rbit = testList.rbegin();
	REQUIRE(*rbit == 3);
	REQUIRE(3 == *(rbit++));
	REQUIRE(*rbit == 2);
	REQUIRE(3 == *(--rbit));
	REQUIRE(*rbit == 3);

	CMyList<int>::ConstIterator ceit = testList.cend();
	REQUIRE(ceit == testList.cend());
	ceit--;
	REQUIRE(*ceit == 3);
	REQUIRE(3 == *(ceit--));
	REQUIRE(*ceit == 2);
	REQUIRE(3 == *(++ceit));
	REQUIRE(*ceit == 3);
}