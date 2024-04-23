#include "test_main.h"

TEST(d3VectorTest, DefaultConstructor) {
  d3::d3_vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(d3VectorTest, ParameterizedConstructor) {
  d3::d3_vector<int> v(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  EXPECT_FALSE(v.empty());
}

TEST(d3VectorTest, InitializerListConstructor) {
  d3::d3_vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(d3VectorTest, CopyConstructor) {
  d3::d3_vector<int> original = {1, 2, 3, 4, 5};
  d3::d3_vector<int> copy(original);
  EXPECT_EQ(copy.size(), 5);
  EXPECT_EQ(copy.capacity(), 5);
  EXPECT_FALSE(copy.empty());
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(original[i], copy[i]);
  }
}

TEST(d3VectorTest, MoveConstructor) {
  d3::d3_vector<int> original = {1, 2, 3, 4, 5};
  d3::d3_vector<int> temp(original);
  d3::d3_vector<int> moved(std::move(temp));
  EXPECT_EQ(moved.size(), 5);
  EXPECT_EQ(moved.capacity(), 5);
  EXPECT_FALSE(moved.empty());
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(original[i], moved[i]);
  }
  EXPECT_EQ(temp.size(), 0);
  EXPECT_EQ(temp.capacity(), 0);
  EXPECT_TRUE(temp.empty());
}

TEST(d3VectorTest, Destructor) {
  d3::d3_vector<int>* v = new d3::d3_vector<int>(5);
  delete v;
}

TEST(d3VectorTest, MoveAssignmentOperator) {
  d3::d3_vector<int> v1 = {1, 2, 3, 4, 5};
  d3::d3_vector<int> v2(10);
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);
  EXPECT_FALSE(v2.empty());
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
  EXPECT_TRUE(v1.empty());
}

TEST(d3VectorTest, DataMethod) {
  d3::d3_vector<int> v = {1, 2, 3, 4, 5};
  int* ptr = v.data();
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(ptr[i], v[i]);
  }
}

TEST(d3VectorTest, BeginEndMethods) {
  d3::d3_vector<int> v = {1, 2, 3, 4, 5};
  size_t i = 1;
  for (auto it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
}

TEST(d3VectorTest, EmptyMethod) {
  d3::d3_vector<int> v;
  EXPECT_TRUE(v.empty());
  v.push_back(1);
  EXPECT_FALSE(v.empty());
}

TEST(d3VectorTest, SizeMethod) {
  d3::d3_vector<int> v;
  EXPECT_EQ(v.size(), 0);
  v.push_back(1);
  EXPECT_EQ(v.size(), 1);
  v.pop_back();
  EXPECT_EQ(v.size(), 0);
}

TEST(d3VectorTest, MaxSizeMethod) {
  d3::d3_vector<int> v;
  EXPECT_EQ(v.max_size(), std::numeric_limits<size_t>::max());
}

TEST(d3VectorTest, ReserveMethod) {
  d3::d3_vector<int> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_GE(v.max_size(), v.capacity());
}

TEST(d3VectorTest, CapacityMethod) {
  d3::d3_vector<int> v;
  EXPECT_EQ(v.capacity(), 0);
  v.push_back(1);
  EXPECT_EQ(v.capacity(), 1);
}

TEST(d3VectorTest, ShrinkToFitMethod) {
  d3::d3_vector<int> v(10);
  v.push_back(1);
  EXPECT_EQ(v.capacity(), 20);
  v.shrink_to_fit();
  EXPECT_LE(v.capacity(), v.size());
}

TEST(d3VectorTest, ClearMethod) {
  d3::d3_vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(d3VectorTest, InsertMethod) {
  d3::d3_vector<int> v = {1, 2, 3, 6, 7};
  auto it = v.insert(v.begin() + 3, 4);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(d3VectorTest, EraseMethod) {
  d3::d3_vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.begin() + 2);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[2], 4);
}

TEST(d3VectorTest, PushBackMethod) {
  d3::d3_vector<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.back(), 4);
}

TEST(d3VectorTest, PopBackMethod) {
  d3::d3_vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);
}

TEST(d3VectorTest, SwapMethod) {
  d3::d3_vector<int> v1 = {1, 2, 3};
  d3::d3_vector<int> v2 = {4, 5};
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
}
