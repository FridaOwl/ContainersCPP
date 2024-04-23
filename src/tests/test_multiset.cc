#include "test_main.h"

TEST(multiset, Init_elements) {
  d3::multiset<int> test = {53, 55, 48, 49, 51};
  std::multiset<int> test2 = {53, 55, 48, 49, 51};
  std::multiset<int>::iterator it;
  d3::multiset<int>::iterator it2 = test.begin();
  for (it = test2.begin(); it != test2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(multiset, Lower) {
  d3::multiset<int> test = {53, 56, 48, 49, 52};
  d3::multiset<int>::iterator it2;
  it2 = test.lower_bound(-3);
  std::multiset<int> test2 = {53, 56, 48, 49, 52};
  std::multiset<int>::iterator it3;
  it3 = test2.lower_bound(-3);
  EXPECT_EQ(*it2, *it3);
}

TEST(multiset, Upper) {
  d3::multiset<int> test = {53, 56, 48, 49, 52};
  d3::multiset<int>::iterator it2;
  it2 = test.upper_bound(53);
  std::multiset<int> test2 = {53, 56, 48, 49, 52};
  std::multiset<int>::iterator it3;
  it3 = test2.upper_bound(53);
  EXPECT_EQ(*it2, *it3);
}

TEST(multiset, range) {
  d3::multiset<int> test = {53, 56, 48, 49, 52};
  std::multiset<int> test2 = {53, 56, 48, 49, 52};
  std::pair<d3::multiset<int>::iterator, d3::multiset<int>::iterator> check =
      test.equal_range(2);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> check2 =
      test2.equal_range(2);
  EXPECT_EQ(*check.first, *check2.first);
  EXPECT_EQ(*check.second, *check2.second);
}

TEST(multiset, count) {
  d3::multiset<int> test = {10, 20, 20, 30, 30, 30};

  EXPECT_EQ(test.count(20), 2);
  EXPECT_EQ(test.count(30), 3);
  EXPECT_EQ(test.count(40), 0);
}

TEST(multiset, lower_and_upper_bound) {
  d3::multiset<int> test = {10, 20, 20, 30, 30, 30};

  auto lower = test.lower_bound(20);
  auto upper = test.upper_bound(20);

  EXPECT_EQ(*lower, 20);
  EXPECT_EQ(*upper, 30);
}

TEST(multiset, large_elemnts_2) {
  d3::multiset<int> m = {};

  for (int i = 0; i < 3000; ++i) {
    m.insert(i);
  }

  for (int i = 0; i < 3000; ++i) {
    ASSERT_TRUE(m.contains(i));
  }
}

TEST(multiset, count2) {
  d3::multiset<int> test = {3, 6, 1, 1, 5};

  EXPECT_EQ(test.count(1), 2);
  EXPECT_EQ(test.count(2), 0);
  EXPECT_EQ(test.count(3), 1);
}

TEST(multiset, lower_bound2) {
  d3::multiset<int> test = {3, 6, 1, 1, 5};

  auto it = test.lower_bound(2);
  EXPECT_EQ(*it, 3);

  it = test.lower_bound(4);
  EXPECT_EQ(*it, 5);
}

TEST(multiset, upper_bound2) {
  d3::multiset<int> test = {3, 6, 1, 1, 5};

  auto it = test.upper_bound(2);
  EXPECT_EQ(*it, 3);

  it = test.upper_bound(4);
  EXPECT_EQ(*it, 5);
}
