#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;
template <class T>
class take_enumerator;
















template<typename T>
class enumerator {
public:

  virtual const T& operator*() = 0;
  virtual enumerator& operator++() = 0;
  virtual operator bool() = 0;


  auto drop(int count) {
    return drop_enumerator(*this, count);
  }

  auto take(int count) {
    return take_enumerator(*this, count);
  }

  template<typename U = T, typename F>
  auto select(F func) {
    return select_enumerator<U, T,F>(*this, std::move(func));
  }

  template<typename F>
  auto until(F func) {
    return until_enumerator<T, F>(*this, std::move(func));
  }

  auto until_eq(T value) {
    return until([=](T elem){return elem == value;});
  }

  template<typename F>
  auto where(F predicate){
    return where_enumerator<T, F>(*this, std::move(predicate));
  }

  auto where_neq(T value){
    return where([=](T elem){return elem != value;});
  }



  std::vector<T> to_vector() {
    std::vector <T> result;
    while(*this) {
      result.push_back(**this);
      ++(*this);
    }
    return result;
  }

  template<typename Iter>
  void copy_to(Iter it) {
    while (*this){
      *it = **this;
      ++it;
      ++(*this);
    }
  }
};



















template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
  range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}
  
  const T& operator*() override{
    return *begin_;
  }

  enumerator<T>& operator++() override{
    ++begin_;
    return *this;
  }
  operator bool() override{
    return begin_ != end_;
  }


private:
  Iter begin_, end_;
};












template<typename T>
class drop_enumerator : public enumerator<T> {
public:
  drop_enumerator(enumerator<T> &parent, int count): parent_(parent){
    for (int i = 0; i< count; i++){
      ++parent_;
    }
  }

  const T& operator*() override{
    return *parent_;
  }

  enumerator<T>& operator++() override{
    ++parent_;
    return *this;
  }
  operator bool() override{
    return static_cast<bool>(parent_);
  }

private:
  enumerator<T>& parent_;
};










template <class T>
class take_enumerator : public enumerator<T> {
public:
  take_enumerator(enumerator<T>& parent, int count) : parent_(parent), count_(count) {}

  enumerator<T>& operator++() override {
    --count_;
    if (parent_)
      ++parent_;
    return *this;
  }

  operator bool() override {
    return (count_ > 0 && static_cast<bool>(parent_));
  }

  const T& operator* () override {
    return *parent_;
  }

private:
  enumerator<T>& parent_;
  int count_;
};












template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
  select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(std::move(func)) {}

  const T& operator*() override{
    value = func_(*parent_);
    return value;
  }

  enumerator<T>& operator++() override{
    ++parent_;
    return *this;
  }

  operator bool() override{
    return parent_;
  }

private:
  enumerator<U> &parent_;
  F func_;
  T value;
};







template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
  until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), 
    predicate_(std::move(predicate)), predicate_was_true(false) {
      if (*this && predicate_(*parent_)){
        predicate_was_true = true;
      }
    }

  const T& operator*() override{
    if (!predicate_(*parent_) && !predicate_was_true){
      return *parent_;
    }
    return *parent_;  //UB :O
  }

  enumerator<T>& operator++() override{
    if (parent_)
      ++parent_;
    if (predicate_(*parent_)){
      predicate_was_true = true;
    }
    return *this;
  }

  operator bool() override{
    return parent_ && !predicate_was_true;
  }


private:
  enumerator<T> &parent_;
  F predicate_;
  bool predicate_was_true;
};




















template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
  where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), 
    predicate_(std::move(predicate)) {}

  const T& operator*() override{
    if (predicate_(*parent_)){
      return *parent_;
    }
    return *parent_;  //UB :O
  }

  enumerator<T>& operator++() override{
    while (!predicate_(*parent_) && parent_){
      ++parent_;
    }
    return *this;
  }

  operator bool() override{
    return parent_;
  }


private:
  enumerator<T> &parent_;
  F predicate_;
};






 

} // namespace impl













template<typename T>
auto from(T begin, T end) {
  return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

} // namespace linq

#endif
