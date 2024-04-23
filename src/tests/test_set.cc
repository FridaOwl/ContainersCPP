#include "test_main.h"

TEST(set, constructor) {
  d3::set<int> test;
  EXPECT_TRUE(test.empty());
}

TEST(set, init) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it;
  d3::set<int>::iterator it2 = test.begin();
  for (it = test2.begin(); it != test2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, copy_constructor) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int> test2(test);
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2(set);
  std::set<int>::iterator it;
  d3::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, move_constructor) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int> test2(std::move(test));
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2(std::move(set));
  std::set<int>::iterator it;
  d3::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test.size(), set.size());
}

TEST(set, move_assignment) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int> test2 = {7, 4, 8, 0, -1};
  test2 = std::move(test);
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2 = {7, 4, 8, 0, -1};
  set2 = std::move(set);
  std::set<int>::iterator it;
  d3::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test.size(), set.size());
}

TEST(set, begin) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int>::iterator it;
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2;
  it = test.begin();
  it2 = test2.begin();
  ASSERT_EQ(*it, *it2);
  it++;
  it2++;
  ASSERT_EQ(*it, *it2);
}

TEST(set, minus) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int>::iterator it;
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2;
  // как-то нкжно это пофиксить наверно
  it = test.begin();
  it2 = test2.begin();
  it++;
  it2++;
  it--;
  it2--;
  ASSERT_EQ(*it, *it2);
}

TEST(set, find) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int>::iterator it;
  it = test.find(45);
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2;
  it2 = test2.find(45);
  ASSERT_EQ(*it, *it2);
}

TEST(set, contains) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  bool check = test.contains(60);
  ASSERT_FALSE(check);
}

TEST(set, insert) {
  std::set<int> test = {52, 54, 45, 48, 53};
  std::pair<std::set<int>::iterator, bool> check = test.insert(45);
  d3::set<int> test2 = {52, 54, 45, 48, 53};
  std::pair<d3::set<int>::iterator, bool> check2 = test2.insert(45);
  ASSERT_EQ(*check.first, *check2.first);
  ASSERT_EQ(check.second, check2.second);
}

TEST(set, insert2) {
  std::set<int> test = {52, 54, 45, 48, 53};
  std::pair<std::set<int>::iterator, bool> check = test.insert(0);
  d3::set<int> test2 = {52, 54, 45, 48, 53};
  std::pair<d3::set<int>::iterator, bool> check2 = test2.insert(0);
  ASSERT_EQ(*check.first, *check2.first);
  ASSERT_EQ(check.second, check2.second);
}

TEST(set, clear) {
  std::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int> test2 = {52, 54, 45, 48, 53};
  test.clear();
  test2.clear();
  ASSERT_EQ(test.size(), test2.size());
}

TEST(set, size) {
  std::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int> test2 = {52, 54, 45, 48, 53};
  ASSERT_EQ(test.size(), test2.size());
}

TEST(set, empty) {
  d3::set<int> test2;
  ASSERT_TRUE(test2.empty());
  test2.insert(45);
  ASSERT_FALSE(test2.empty());
}

TEST(set, swap) {
  d3::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int> test2 = {7, 4, 8, 0, -1, 48, 53};
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2 = {7, 4, 8, 0, -1, 48, 53};
  test2.swap(test);
  set2.swap(set);
  std::set<int>::iterator it;
  d3::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  it2 = test.begin();
  for (it = set.begin(); it != set.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, erase) {
  std::set<int> test = {52, 54, 45, 48, 53};
  d3::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it = test.begin();
  d3::set<int>::iterator it2 = test2.begin();
  ++it;
  ++it2;
  test.erase(it);
  test2.erase(it2);
  it = test.begin();
  it2 = test2.begin();
  for (; it != test.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, insert_many) {
  d3::set<int> m = {3, 6, 1, -1, 5};

  m.insert_many(-2, -1, 7);

  std::set<int> std_m = {-2, -1, 3, 6, 1, 5, 7};
  d3::set<int>::iterator it = m.begin();
  std::set<int>::iterator it2;
  for (it2 = std_m.begin(); it2 != std_m.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}

TEST(set, large_elemnts) {
  d3::set<int> m = {};

  for (int i = 0; i < 5000; ++i) {
    m.insert(i);
  }

  for (int i = 0; i < 5000; ++i) {
    ASSERT_TRUE(m.contains(i));
  }
}
