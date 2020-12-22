// Copyright 2020 Alex Volodin <your_email>

#ifndef INCLUDE_STACK1_HPP_
#define INCLUDE_STACK1_HPP_
#include <stdexcept>
#include <utility>

template <class T>
struct Element {
  T value;  // значение элемента
  Element<T> *prev = nullptr,
             *next = nullptr;  // ссылки на предыдущий и следующий элемент
};
// некопируемый перемещаемый шаблон класса stack с методами pop, push, head
template <typename T>
class Stack1 {
 public:
  Stack1() = default;  // конструктор по умолчанию
  Stack1(const Stack1 &st) = delete; // шаблон - некопируемый!
  auto operator=(const Stack1 &st) -> Stack1 & = delete;
  Stack1(Stack1 &&st) noexcept = default; // шаблон - перемещаемый!
  auto operator=(Stack1 &&st) noexcept -> Stack1 & = default;
  ~Stack1();  // деструктор

  void push(const T &value);  // вставка элемента
  void push(T &&value);       // вставка элемента
  void pop();                 // уничтожение элемента
  const T &head() const;      // доступ к вершине стека

 private:
  Element<T> *HEAD = nullptr;  // верхушка стека
  Element<T> *TAIL = nullptr;  // "хвост" стека
};
template <typename T>
void Stack1<T>::push(const T &value) {
  auto *new_element = new Element<T>{value, HEAD};
  HEAD = new_element;
}

template <typename T>
void Stack1<T>::push(T &&value) {
  auto *new_element = new Element<T>{std::forward<T>(value), HEAD};
  HEAD = new_element;
}

template <typename T>
void Stack1<T>::pop() {
  if (HEAD) {
    auto *FIRST = HEAD;
    HEAD = HEAD->prev;  // теперь "вершина" стека - это предыдущий элемент
    delete FIRST;
  } else {
    throw std::out_of_range("Stack is empty!");
  }
}
template <typename T>
const T &Stack1<T>::head() const {
  if (!HEAD) {
    throw std::out_of_range("Stack is empty!");
  }
  return HEAD->value;  // возвращаем значение элемента
}

template <typename T>
Stack1<T>::~Stack1() {
  while (HEAD) {
    auto *current_element = HEAD;  // текущий элемент - теперь "вершина"
    HEAD = HEAD->prev;  // "вершина" является предыдущим элементом
    delete current_element;  // уничтожаем текущий элемент
  }
}
#endif  // INCLUDE_STACK1_HPP_
