#include "test_main.h"

TEST(Stack, Constructor_Default) {
  d3::stack<int> stack;
  std::stack<int> stack_std;
  EXPECT_EQ(stack.empty(), stack_std.empty());
}

TEST(Stack, Constructor_List) {
  d3::stack<int> stack = {1, 2, 3};
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  EXPECT_EQ(stack.top(), stack_std.top());
  EXPECT_EQ(stack.size(), stack_std.size());
}

TEST(Stack, Constructor_Copy) {
  d3::stack<int> stack = {1, 2, 3};
  d3::stack<int> stack_copy(stack);
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  std::stack<int> stack_std_copy(stack_std);
  EXPECT_EQ(stack_copy.top(), stack_std_copy.top());
  EXPECT_EQ(stack_copy.size(), stack_std_copy.size());
}

TEST(Stack, Constructor_Move) {
  d3::stack<int> stack = {1, 2, 3};
  d3::stack<int> stack_move(std::move(stack));
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  std::stack<int> stack_std_move(std::move(stack_std));
  EXPECT_EQ(stack_move.top(), stack_std_move.top());
  EXPECT_EQ(stack_move.size(), stack_std_move.size());
  EXPECT_EQ(stack.empty(), stack_std.empty());
}

TEST(Stack, Operator_Copy) {
  d3::stack<int> stack = {1, 2, 3};
  std::stack<int> stack_std;
  d3::stack<int> stack_copy;
  std::stack<int> stack_std_copy;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  stack_copy = stack;
  stack_std_copy = stack_std;
  EXPECT_EQ(stack_copy.top(), stack_std_copy.top());
  EXPECT_EQ(stack_copy.size(), stack_std_copy.size());
  EXPECT_EQ(stack.empty(), stack_std.empty());
}

TEST(Stack, Operator_Move) {
  d3::stack<int> stack = {1, 2, 3};
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  d3::stack<int> stack_move;
  std::stack<int> stack_std_move;
  stack_move = std::move(stack);
  stack_std_move = std::move(stack_std);
  EXPECT_EQ(stack_move.top(), stack_std_move.top());
  EXPECT_EQ(stack_move.size(), stack_std_move.size());
  EXPECT_EQ(stack.empty(), stack_std.empty());
}

TEST(Stack, Top) {
  d3::stack<int> stack = {1, 2, 3};
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  EXPECT_EQ(stack.top(), stack_std.top());
}

TEST(Stack, Empty) {
  d3::stack<int> stack = {1, 2, 3};
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  EXPECT_EQ(stack.empty(), stack_std.empty());
  d3::stack<int> stack_1;
  std::stack<int> stack_std_1;
  EXPECT_EQ(stack_1.empty(), stack_std_1.empty());
}

TEST(Stack, Size) {
  d3::stack<int> stack = {1, 2, 3};
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  EXPECT_EQ(stack.size(), stack_std.size());
  d3::stack<int> stack_1;
  std::stack<int> stack_std_1;
  EXPECT_EQ(stack_1.size(), stack_std_1.size());
}

TEST(Stack, Push) {
  d3::stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  EXPECT_EQ(stack.top(), stack_std.top());
  EXPECT_EQ(stack.size(), stack_std.size());
}

TEST(Stack, Pop) {
  d3::stack<int> stack = {1, 2, 3};
  stack.pop();
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  stack_std.pop();
  EXPECT_EQ(stack.top(), stack_std.top());
  EXPECT_EQ(stack.size(), stack_std.size());
  stack.pop();
  stack.pop();
  stack_std.pop();
  stack_std.pop();
  EXPECT_EQ(stack.empty(), stack_std.empty());
}

TEST(Stack, Swap) {
  d3::stack<int> stack = {1, 2, 3};
  std::stack<int> stack_std;
  stack_std.push(1);
  stack_std.push(2);
  stack_std.push(3);
  d3::stack<int> stack_1;
  std::stack<int> stack_std_1;
  stack_1.swap(stack);
  stack_std_1.swap(stack_std);
  EXPECT_EQ(stack_1.top(), stack_std_1.top());
  EXPECT_EQ(stack_1.size(), stack_std_1.size());
  EXPECT_EQ(stack.empty(), stack_std.empty());
}
