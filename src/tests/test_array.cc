#include <gtest/gtest.h>

#include "test_main.h"

TEST(d3ArrayTest, Data) {
  d3::d3_array<int, 3> arr = {1, 2, 3};

  int* data_ptr = arr.data();
  EXPECT_EQ(*data_ptr, 1);

  *data_ptr = 100;
  EXPECT_EQ(arr[0], 100);
}

TEST(d3ArrayTest, ConstData) {
  const d3::d3_array<int, 3> arr = {1, 2, 3};

  const int* data_ptr = arr.data();
  EXPECT_EQ(*data_ptr, 1);
}

TEST(d3ArrayTest, BeginEnd) {
  d3::d3_array<int, 3> arr = {1, 2, 3};

  auto it_begin = arr.begin();
  auto it_end = arr.end();

  EXPECT_EQ(*it_begin, 1);
  EXPECT_EQ(*(it_end - 1), 3);

  *it_begin = 100;
  EXPECT_EQ(arr[0], 100);
}

TEST(d3ArrayTest, ConstBeginEnd) {
  const d3::d3_array<int, 3> arr = {1, 2, 3};

  auto it_begin = arr.begin();
  auto it_end = arr.end();

  EXPECT_EQ(*it_begin, 1);
  EXPECT_EQ(*(it_end - 1), 3);
}

TEST(d3ArrayTest, FrontAt) {
  d3::d3_array<int, 3> arr = {1, 2, 3};

  EXPECT_EQ(arr.front(), 1);
}

TEST(d3ArrayTest, OperatorBracket) {
  d3::d3_array<int, 3> arr = {1, 2, 3};

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(d3ArrayTest, Front) {
  d3::d3_array<int, 3> arr = {1, 2, 3};

  EXPECT_EQ(arr.front(), 1);
}

TEST(d3ArrayTest, Back) {
  d3::d3_array<int, 3> arr = {1, 2, 3};

  EXPECT_EQ(arr.back(), 3);
}

TEST(d3ArrayTest, CopyConstructor) {
  d3::d3_array<int, 3> arr = {1, 2, 3};
  d3::d3_array<int, 3> copy_arr(arr);

  EXPECT_EQ(copy_arr[0], arr[0]);
  EXPECT_EQ(copy_arr[1], arr[1]);
  EXPECT_EQ(copy_arr[2], arr[2]);
}

TEST(d3ArrayTest, MoveConstructor) {
  d3::d3_array<int, 3> arr = {1, 2, 3};
  d3::d3_array<int, 3> move_arr(std::move(arr));

  EXPECT_EQ(move_arr[0], 1);
  EXPECT_EQ(move_arr[1], 2);
  EXPECT_EQ(move_arr[2], 3);

  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr[1], 0);
  EXPECT_EQ(arr[2], 0);
}

TEST(d3ArrayTest, Fill) {
  d3::d3_array<int, 3> arr = {1, 2, 3};

  arr.fill(5);

  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 5);
  EXPECT_EQ(arr[2], 5);
}

TEST(d3ArrayTest, Swap) {
  d3::d3_array<int, 3> arr1 = {1, 2, 3};
  d3::d3_array<int, 3> arr2 = {4, 5, 6};

  swap(arr1, arr2);

  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(d3ArrayTest, AssignmentOperators) {
  d3::d3_array<int, 3> arr1 = {1, 2, 3};
  d3::d3_array<int, 3> arr2;

  arr2 = arr1;

  EXPECT_EQ(arr2[0], arr1[0]);
  EXPECT_EQ(arr2[1], arr1[1]);
  EXPECT_EQ(arr2[2], arr1[2]);

  arr2 = std::move(arr1);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}
