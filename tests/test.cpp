// Copyright 2020 Alex Volodin <your_email>

#include <gtest/gtest.h>
#include <stack1.hpp>
#include <stack2.hpp>
class Apple {
 public:
  std::string type;
  int diagonal, screen_resolution, rom;
  Apple() = default;
  Apple(std::string TYPE, int DIAGONAL, int SCREEN_RESOLUTION, int ROM)
      :type(TYPE), diagonal(DIAGONAL), screen_resolution(SCREEN_RESOLUTION), rom(ROM) {}
  Apple(Apple&& value) noexcept = default;
  Apple(const Apple& value) = delete;
  auto operator=(Apple&& value) noexcept -> Apple& = default;
  auto operator=(const Apple& value) -> Apple& = delete;
};

class Samsung {
 public:
  std::string model, processor;
  int memory;
  Samsung() = default;
  Samsung(std::string MODEL, std::string PROCESSOR, int MEMORY)
      :model(MODEL), processor(PROCESSOR), memory(MEMORY) {}
  Samsung(Samsung&& value) noexcept = default;
  Samsung(const Samsung& value) = delete;
  auto operator=(Samsung&& value) noexcept -> Samsung& = default;
  auto operator=(const Samsung& value) -> Samsung& = delete;
};

TEST(Apple, Movy_Copy) {
  EXPECT_TRUE(std::is_move_constructible<Apple>::value);
  EXPECT_FALSE(std::is_copy_constructible<Apple>::value);
}

TEST(Samsung, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<Samsung>::value);
  EXPECT_TRUE(std::is_copy_constructible<Samsung>::value);
}

TEST(Stack1, Move) {
  EXPECT_TRUE(std::is_move_constructible<Stack1<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack1<int>>::value);
}
TEST(Stack1, Copy) {
  EXPECT_FALSE(std::is_copy_constructible<Stack1<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack1<int>>::value);
}

TEST(Stack2, Move) {
  EXPECT_TRUE(std::is_move_constructible<Stack2<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack2<int>>::value);
}

TEST(Stack2, Copy) {
  EXPECT_FALSE(std::is_copy_constructible<Stack2<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack2<int>>::value);
}
//Check methods class Stack
TEST(Stack1, Copy_Push) {
  Stack1<int> stack;
  stack.push(static_cast<const int&>(100));
  stack.push(static_cast<const int&>(200));
  EXPECT_EQ(stack.head(), 200);
  stack.pop();
  EXPECT_EQ(stack.head(), 100);
}

TEST(Stack1, Pop) {
  Stack1<int> stack;
  EXPECT_ANY_THROW(stack.pop());
}

TEST(Stack1, Move_Push) {
  Stack1<int> stack;
  stack.push(300);
  EXPECT_EQ(stack.head(), 300);
}

TEST(Stack1, Head) {
  Stack1<int> stack;
  EXPECT_ANY_THROW(stack.head());
}
//Check methods class NonCopiedStack
TEST(NonCopiedStack, ErorrMovePush) {
//  Stack2<Samsung> stack;
  Samsung phone1{};
  phone1.model = "A51";
//  EXPECT_ANY_THROW(stack.push(std::move(phone1)));
}

TEST(Stack2, Move_Push) {
  Stack2<Apple> stack;
  Apple phone1{"5S", 25, 1024, 32};
  stack.push(std::move(phone1));
  Apple phone2{stack.pop()};
  EXPECT_EQ(phone2.type, "6");
  EXPECT_EQ(phone2.diagonal, 27);
  EXPECT_EQ(phone2.screen_resolution, 2048);
  EXPECT_EQ(phone2.rom, 64);
}
/*
TEST(Stack2, Push) {
  Stack2<Apple> stack;
  stack.push(Apple("SE", 27, 2048, 64));
  stack.push_emplace("Xr", 27, 2048, 64);
  EXPECT_EQ(stack.head().x, 3);
  stack.pop();
  EXPECT_EQ(stack.head().y, 4);
}*/

TEST(NonCopiedStack, Pop) {
  Stack2<Apple> stack;
  EXPECT_ANY_THROW(stack.pop());
}
