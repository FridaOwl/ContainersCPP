#include "test_main.h"

TEST(List, Constructor) {
  d3::list<int> customList;
  std::list<int> stdList;
  EXPECT_EQ(customList.empty(), stdList.empty());
}

TEST(List, Constructor_Size) {
  d3::list<int> customListWithSize(10);
  std::list<int> stdListWithSize(10);
  EXPECT_EQ(customListWithSize.size(), stdListWithSize.size());

  d3::list<int> customListEmpty(0);
  std::list<int> stdListEmpty(0);
  EXPECT_EQ(customListEmpty.size(), stdListEmpty.size());
  EXPECT_EQ(customListEmpty.empty(), stdListEmpty.empty());
}

TEST(List, Constructor_Initializer_List) {
  d3::list<int> customList = {1, 2, 3, 4, 5};
  std::list<int> stdList = {1, 2, 3, 4, 5};
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Constructor_Copy) {
  d3::list<int> originalList = {1, 2, 3, 4, 5};
  d3::list<int> customListCopy(originalList);
  std::list<int> stdList = {1, 2, 3, 4, 5};
  EXPECT_EQ(originalList.front(), stdList.front());
  EXPECT_EQ(originalList.back(), stdList.back());
  EXPECT_EQ(customListCopy.front(), stdList.front());
  EXPECT_EQ(customListCopy.back(), stdList.back());
  EXPECT_EQ(originalList.size(), stdList.size());
  EXPECT_EQ(customListCopy.size(), stdList.size());
}

TEST(List, Constructor_Move) {
  d3::list<int> originalList = {1, 2, 3, 4, 5};
  d3::list<int> customListMoved(std::move(originalList));
  std::list<int> stdList = {1, 2, 3, 4, 5};
  EXPECT_EQ(originalList.empty(), true);
  EXPECT_EQ(customListMoved.front(), stdList.front());
  EXPECT_EQ(customListMoved.back(), stdList.back());
  EXPECT_EQ(originalList.size(), 0);
  EXPECT_EQ(customListMoved.size(), stdList.size());
}

TEST(List, Operator_Copy) {
  d3::list<int> originalList = {1, 2, 3, 4, 5};
  d3::list<int> customListCopy;
  customListCopy = originalList;
  std::list<int> stdList = {1, 2, 3, 4, 5};
  EXPECT_EQ(originalList.front(), stdList.front());
  EXPECT_EQ(originalList.back(), stdList.back());
  EXPECT_EQ(customListCopy.front(), stdList.front());
  EXPECT_EQ(customListCopy.back(), stdList.back());
  EXPECT_EQ(originalList.size(), stdList.size());
  EXPECT_EQ(customListCopy.size(), stdList.size());
  d3::list<int>::iterator customListIterator;
  std::list<int>::iterator stdListIterator;
  customListIterator = originalList.end();
  stdListIterator = stdList.end();
  EXPECT_EQ(*customListIterator, *stdListIterator);
  d3::list<int> customListCopy1;
  customListCopy1 = originalList;
  customListIterator = customListCopy1.end();
  EXPECT_EQ(*customListIterator, *stdListIterator);
}

TEST(List, Operator_Move) {
  d3::list<int> originalList = {1, 2, 3, 4, 5};
  d3::list<int> customListMoved;
  customListMoved = std::move(originalList);
  std::list<int> stdList = {1, 2, 3, 4, 5};
  EXPECT_EQ(originalList.empty(), true);
  EXPECT_EQ(customListMoved.front(), stdList.front());
  EXPECT_EQ(customListMoved.back(), stdList.back());
  EXPECT_EQ(originalList.size(), 0);
  EXPECT_EQ(customListMoved.size(), stdList.size());
}

TEST(List, Front) {
  d3::list<int> customList = {5, 4, 3, 2, 1};
  std::list<int> stdList = {5, 4, 3, 2, 1};
  EXPECT_EQ(customList.front(), stdList.front());
}

TEST(List, Back) {
  d3::list<int> customList = {5, 4, 3, 2, 1};
  std::list<int> stdList = {5, 4, 3, 2, 1};
  EXPECT_EQ(customList.back(), stdList.back());
}

TEST(List, Empty) {
  d3::list<int> customList = {5, 4, 3, 2, 1};
  std::list<int> stdList = {5, 4, 3, 2, 1};
  EXPECT_EQ(customList.empty(), stdList.empty());
}

TEST(List, Size) {
  d3::list<int> customList = {5, 4, 3, 2, 1};
  std::list<int> stdList = {5, 4, 3, 2, 1};
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Max_Size) {
  d3::list<int> customList = {5, 4, 3, 2, 1};
  std::list<int> stdList = {5, 4, 3, 2, 1};
  EXPECT_EQ(customList.max_size(), stdList.max_size());
}

TEST(List, Clear) {
  d3::list<int> customList = {5, 4, 3, 2, 1};
  std::list<int> stdList = {5, 4, 3, 2, 1};
  customList.clear();
  stdList.clear();
  EXPECT_EQ(customList.empty(), stdList.empty());
}

TEST(List, Push_Back) {
  d3::list<int> customList;
  std::list<int> stdList;
  customList.push_back(1);
  stdList.push_back(1);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
  customList.push_back(4);
  stdList.push_back(4);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Pop_Back) {
  d3::list<int> customList = {1, 2, 3, 4, 5};
  std::list<int> stdList = {1, 2, 3, 4, 5};
  customList.pop_back();
  stdList.pop_back();
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
  customList.pop_back();
  stdList.pop_back();
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Push_Front) {
  d3::list<int> customList;
  std::list<int> stdList;
  customList.push_front(1);
  stdList.push_front(1);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
  customList.push_front(4);
  stdList.push_front(4);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Pop_Front) {
  d3::list<int> customList = {1, 2};
  std::list<int> stdList = {1, 2};
  customList.pop_front();
  stdList.pop_front();
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
  customList.pop_front();
  stdList.pop_front();
  EXPECT_EQ(customList.empty(), stdList.empty());
}

TEST(List, Swap) {
  d3::list<int> customList = {1, 2, 3, 4, 5};
  d3::list<int> customList1 = {5, 4, 3, 2, 1};
  customList.swap(customList1);
  EXPECT_EQ(customList.front(), 5);
  EXPECT_EQ(customList.back(), 1);
  EXPECT_EQ(customList.size(), 5);
  EXPECT_EQ(customList1.front(), 1);
  EXPECT_EQ(customList1.back(), 5);
  EXPECT_EQ(customList1.size(), 5);
}

TEST(List, Reverse) {
  d3::list<int> customList = {1, 2, 3, 4, 5};
  std::list<int> stdList = {1, 2, 3, 4, 5};
  customList.reverse();
  stdList.reverse();
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Sort) {
  d3::list<int> customList = {1, 2, 3, 4, 5, 2, 4, 2, 1};
  std::list<int> stdList = {1, 2, 3, 4, 5, 2, 4, 2, 1};
  customList.sort();
  stdList.sort();
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Iterator) {
  d3::list<int> customList = {1234, 228, 123, 69};
  d3::list<int>::const_iterator customListIterator = customList.end();
  --customListIterator;
  EXPECT_EQ(*customListIterator, 69);
  ++customListIterator;
  EXPECT_EQ(*customListIterator, 4);
  ++customListIterator;
  EXPECT_EQ(*customListIterator, 1234);
  --customListIterator;
  EXPECT_EQ(*customListIterator, 4);
  customListIterator = customListIterator - 2;
  EXPECT_EQ(*customListIterator, 123);
  customListIterator = customListIterator + 2;
  EXPECT_EQ(*customListIterator, 4);
  d3::list<int>::iterator customListIterator1 = customList.begin();
  --customListIterator1;
  EXPECT_EQ(*customListIterator, 4);
}

TEST(List, Insert) {
  d3::list<int> customList = {1, 2, 3, 4};
  std::list<int> stdList = {1, 2, 3, 4};
  d3::list<int>::iterator customListIterator;
  std::list<int>::iterator stdListIterator;
  customListIterator = customList.begin();
  stdListIterator = stdList.begin();
  customList.insert(customListIterator, 13);
  stdList.insert(stdListIterator, 13);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
  customListIterator = customList.end();
  stdListIterator = stdList.end();
  customList.insert(customListIterator, 1234);
  stdList.insert(stdListIterator, 1234);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());

  d3::list<int> customList1;
  d3::list<int>::iterator customListIterator1;
  std::list<int> stdList1;
  std::list<int>::iterator stdListIterator1;
  customListIterator1 = customList1.begin();
  stdListIterator1 = stdList1.begin();
  customList1.insert(customListIterator1, 5);
  stdList1.insert(stdListIterator1, 5);
  EXPECT_EQ(customList1.front(), stdList1.front());
  EXPECT_EQ(customList1.back(), stdList1.back());
  EXPECT_EQ(customList1.size(), stdList1.size());
  customList1.insert(customListIterator1, 7);
  stdList1.insert(stdListIterator1, 7);
  customList1.insert(customListIterator1, 9);
  stdList1.insert(stdListIterator1, 9);
  EXPECT_EQ(customList1.front(), stdList1.front());
  EXPECT_EQ(customList1.back(), stdList1.back());
  EXPECT_EQ(customList1.size(), stdList1.size());

  d3::list<int> customList2 = {1, 2, 3, 4, 5, 6};
  d3::list<int>::iterator customListIterator2 = customList2.end();
  std::list<int> stdList2 = {1, 2, 3, 4, 5, 6};
  std::list<int>::iterator stdListIterator2 = stdList2.end();
  customListIterator2 = customList2.insert(customListIterator2, 1234);
  stdListIterator2 = stdList2.insert(stdListIterator2, 1234);
  EXPECT_EQ(customList2.front(), stdList2.front());
  EXPECT_EQ(customList2.back(), stdList2.back());
}

TEST(List, Erase) {
  d3::list<int> customList = {1, 2, 3, 4, 5, 6, 7};
  d3::list<int>::iterator customListIterator;

  std::list<int> stdList = {1, 2, 3, 4, 5, 6, 7};
  std::list<int>::iterator stdListIterator;

  customList.erase(customList.begin());
  stdList.erase(stdList.begin());
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());

  customListIterator = customList.begin();
  ++customListIterator;
  stdListIterator = stdList.begin();
  ++stdListIterator;
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());

  customListIterator = customList.end();
  stdListIterator = stdList.end();
  --customListIterator;
  --stdListIterator;
  customList.erase(customListIterator);
  stdList.erase(stdListIterator);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());

  customListIterator = customList.begin();
  stdListIterator = stdList.begin();
  ++customListIterator;
  ++stdListIterator;
  ++customListIterator;
  ++stdListIterator;
  ++customListIterator;
  ++stdListIterator;
  customList.erase(customListIterator);
  stdList.erase(stdListIterator);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Splice) {
  d3::list<int> customList = {1};
  d3::list<int> customList1 = {2, 3, 4, 5};
  std::list<int> stdList = {1};
  std::list<int> stdList1 = {2, 3, 4, 5};
  d3::list<int>::iterator it = customList.begin();
  std::list<int>::iterator it_std = stdList.begin();
  customList.splice(it, customList1);
  stdList.splice(it_std, stdList1);
  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Unique) {
  d3::list<int> list = {1, 2, 2, 2, 3, 4, 5, 5, 5};
  std::list<int> list_std = {1, 2, 2, 2, 3, 4, 5, 5, 5};
  list.unique();
  list_std.unique();
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Merge) {
  d3::list<int> customList = {1, 2, 3, 4};
  d3::list<int> customListToMerge = {2, 5, 4, 3};
  std::list<int> stdList = {1, 2, 3, 4};
  std::list<int> stdListToMerge = {2, 5, 4, 3};

  customList.sort();
  customListToMerge.sort();
  stdList.sort();
  stdListToMerge.sort();

  customList.merge(customListToMerge);
  stdList.merge(stdListToMerge);

  EXPECT_EQ(customList.front(), stdList.front());
  EXPECT_EQ(customList.back(), stdList.back());
  EXPECT_EQ(customList.size(), stdList.size());
}

TEST(List, Insert_Many) {
  d3::list<int> list = {1, 5, 6};
  d3::list<int>::iterator it = list.begin();
  ++it;
  list.insert_many(it, 2, 3, 4);
  it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(List, Insert_Many_Back) {
  d3::list<int> list = {1, 2, 3};
  d3::list<int>::iterator it;
  list.insert_many_back(4, 5, 6);
  it = list.end();
  --it;
  EXPECT_EQ(*it, 6);
  --it;
  EXPECT_EQ(*it, 5);
  --it;
  EXPECT_EQ(*it, 4);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(List, Insert_Many_Front) {
  d3::list<int> list = {4, 5, 6};
  d3::list<int>::iterator it;
  list.insert_many_front(3, 2, 1);
  it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}
