#include "test_main.h"

TEST(map, move_assignment) {
  d3::map<int, int> test = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  d3::map<int, int> test2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  test2 = std::move(test);
  std::map<int, int> map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> map2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  map2 = std::move(map);
  std::map<int, int>::iterator it;
  d3::map<int, int>::iterator it2 = test2.begin();
  for (it = map2.begin(); it != map2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test.size(), map.size());
}

TEST(map, move_constructor) {
  d3::map<int, int> test = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  d3::map<int, int> test2(std::move(test));
  std::map<int, int> map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> map2(std::move(map));
  std::map<int, int>::iterator it;
  d3::map<int, int>::iterator it2 = test2.begin();
  for (it = map2.begin(); it != map2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test.size(), map.size());
}

TEST(map, init_constructor) {
  d3::map<int, int> test = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  d3::map<int, int>::iterator it = test.begin();
  std::map<int, int> test2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int>::iterator it2;
  for (it2 = test2.begin(); it2 != test2.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}

TEST(map, init_constructor2) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  d3::map<std::string, int>::iterator it = test.begin();
  std::map<std::string, int> test2 = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::map<std::string, int>::iterator it2;
  for (it2 = test2.begin(); it2 != test2.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}

TEST(map, insert_bool) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::pair<d3::map<std::string, int>::iterator, bool> check =
      test.insert({"kaka", 5});
  std::map<std::string, int> test2 = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::pair<std::map<std::string, int>::iterator, bool> check2 =
      test2.insert({"kaka", 5});
  EXPECT_EQ(*check.first, *check2.first);
  EXPECT_EQ(check.second, check2.second);
}

TEST(map, insert_0r_assign) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::pair<d3::map<std::string, int>::iterator, bool> check =
      test.insert_or_assign("kringe", 5);
  std::map<std::string, int> test2 = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::pair<std::map<std::string, int>::iterator, bool> check2 =
      test2.insert_or_assign("kringe", 5);
  EXPECT_EQ(*check.first, *check2.first);
  EXPECT_EQ(check.second, check2.second);
}

TEST(map, swap) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  d3::map<std::string, int> test2 = {
      {"klava", 2}, {"1", 3}, {"2", 4}, {"3", 1}, {"1", 3}};
  std::map<std::string, int> map = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::map<std::string, int> map2 = {
      {"klava", 2}, {"1", 3}, {"2", 4}, {"3", 1}, {"1", 3}};

  test2.swap(test);
  map2.swap(map);
  std::map<std::string, int>::iterator it;
  d3::map<std::string, int>::iterator it2 = test2.begin();
  for (it = map2.begin(); it != map2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  it2 = test.begin();
  for (it = map.begin(); it != map.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(map, merge) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  d3::map<std::string, int> test2 = {
      {"klava", 2}, {"1", 3}, {"2", 4}, {"3", 1}, {"1", 3}};
  std::map<std::string, int> map = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::map<std::string, int> map2 = {
      {"klava", 2}, {"1", 3}, {"2", 4}, {"3", 1}, {"1", 3}};
  test2.merge(test);
  map2.merge(map);
  std::map<std::string, int>::iterator it;
  d3::map<std::string, int>::iterator it2 = test2.begin();
  for (it = map2.begin(); it != map2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(map, insert_many) {
  d3::map<int, std::string> m = {{1, "1"}, {2, "2"}};

  m.insert_many(
      std::make_pair(5, std::string("5")), std::make_pair(3, std::string("3")),
      std::make_pair(3, std::string("3")), std::make_pair(4, std::string("4")));

  std::map<int, std::string> std_m = {
      {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"}};
  d3::map<int, std::string>::iterator it = m.begin();
  std::map<int, std::string>::iterator it2;
  for (it2 = std_m.begin(); it2 != std_m.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}

TEST(map, max) {
  d3::map<int, int> test = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> test2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  EXPECT_EQ(test.max_size(), test2.max_size());
}

TEST(map, brackets) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::map<std::string, int> test2 = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  EXPECT_EQ(test["lol"], test2["lol"]);
}

TEST(map, at) {
  d3::map<int, int> test = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> test2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  EXPECT_EQ(test.at(4), test2.at(4));
}

TEST(map, default_constructor) {
  d3::map<int, int> test;
  std::map<int, int> test2;
  EXPECT_EQ(test.size(), test2.size());
  EXPECT_TRUE(test.empty());
}

TEST(map, size) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::map<std::string, int> test2 = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  EXPECT_EQ(test.size(), test2.size());
}

TEST(map, empty) {
  d3::map<std::string, int> test0;
  EXPECT_TRUE(test0.empty());
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  EXPECT_FALSE(test.empty());
}

TEST(map, clear) {
  d3::map<std::string, int> test = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  std::map<std::string, int> test2 = {
      {"lol", 2}, {"lal", 3}, {"lalk", 4}, {"kek", 1}, {"check", 3}};
  test.clear();
}

TEST(map, move_constructor_with_initializer_list) {
  d3::map<int, int> test = {{5, 2}, {6, 3}, {7, 4}, {8, 1}, {9, 3}};
  std::map<int, int> map = {{5, 2}, {6, 3}, {7, 4}, {8, 1}, {9, 3}};
  d3::map<int, int>::iterator it = test.begin();
  for (auto it2 = map.begin(); it2 != map.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}

TEST(map, move_constructor_empty) {
  d3::map<int, int> test;
  d3::map<int, int> test2(std::move(test));
  EXPECT_TRUE(test.empty());
}

TEST(map, move_assignment_empty) {
  d3::map<int, int> test;
  d3::map<int, int> test2;
  test2 = std::move(test);
  EXPECT_TRUE(test.empty());
}

TEST(map, initializer_list_constructor) {
  d3::map<int, int> test = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  d3::map<int, int> test2 = {{5, 2}, {6, 3}, {7, 4}, {8, 1}, {9, 3}};
  std::map<int, int> map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> map2 = {{5, 2}, {6, 3}, {7, 4}, {8, 1}, {9, 3}};
  d3::map<int, int>::iterator it = test.begin();
  for (auto it2 = map.begin(); it2 != map.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
  it = test2.begin();
  for (auto it2 = map2.begin(); it2 != map2.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}

TEST(map, move_constructor_with_initializer_lis2t) {
  d3::map<int, int> test = {{5, 2}, {6, 3}, {7, 4}, {8, 1}, {9, 3}};
  std::map<int, int> map = {{5, 2}, {6, 3}, {7, 4}, {8, 1}, {9, 3}};
  d3::map<int, int>::iterator it = test.begin();
  for (auto it2 = map.begin(); it2 != map.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}