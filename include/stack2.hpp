// Copyright 2020 Alex Volodin <your_email>

#ifndef TEMPLATE_STACK2_HPP
#define TEMPLATE_STACK2_HPP
#include <iostream>
#include <type_traits>
template <class T>
struct Element {
  T value;
  Element<T> *prev, *next;
};
template <typename T>
class Stack2
{
 public:
  template <typename ... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  const T& head() const;
  T pop();
 private:
  Element<T> *HEAD;
  Element<T> *TAIL;
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
  HEAD = HEAD->previous;
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
#endif  // TEMPLATE_STACK2_HPP
