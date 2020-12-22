// Copyright 2020 Alex Volodin <your_email>

#ifndef INCLUDE_STACK2_HPP_
#define INCLUDE_STACK2_HPP_
#include <iostream>
#include <type_traits>
#include <utility>
#include "stack1.hpp"

template <typename T>
class Stack2 {
 public:
  Stack2() = default;  // конструктор по умолчанию
  Stack2(const Stack2 &st) = delete; // шаблон - некопируемый!
  auto operator=(const Stack2 &st) -> Stack2 & = delete;
  Stack2(Stack2 &&st) noexcept = default; // шаблон - перемещаемый!
  auto operator=(Stack2 &&st) noexcept -> Stack2 & = default;
  ~Stack2();  // деструктор

  template <typename... Args>
  void push_emplace(Args &&... value);
  void push(T &&value);
  const T &head() const;
  T pop();

 private:
  Element<T> *HEAD = nullptr;
  Element<T> *TAIL = nullptr;
};

template <typename T>
void Stack2<T>::push(T &&value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *new_element = new Element<T>{std::forward<T>(value), HEAD};
  HEAD = new_element;
}

template <typename T>
T Stack2<T>::pop() {
  if (!HEAD) {
    throw std::out_of_range("Empty Stack!!!");
  }
  auto *FIRST = HEAD;
  HEAD = HEAD->prev;
  T value = std::move(FIRST->value);
  delete FIRST;
  return value;
}

template <typename T>
template <typename... Args>
void Stack2<T>::push_emplace(Args &&... value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *new_element = new Element<T>{{std::forward<Args>(value)...}, HEAD};
  HEAD = new_element;
}

template <typename T>
Stack2<T>::~Stack2() {
  while (HEAD) {
    auto *current_element = HEAD;  // текущий элемент - теперь "вершина"
    HEAD = HEAD->prev;  // "вершина" является предыдущим элементом
    delete current_element;  // уничтожаем текущий элемент
  }
}
#endif  // INCLUDE_STACK2_HPP_
