#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

template<typename T, size_t S>
class Array
{
public:
  Array() {}
  ~Array() {}

  /**
   * The reason why this is being called instead of the nested initializer list (I believe)
   * is because of the way it's structured
   * Array<double,2> a = {3,2} is read as INITIALIZER LIST {3,2}
   *
   * Array<Array<double,2>,2> a2 = {{1,2},{3,4}} is read as initializer list with 2 members
   * for each initializer list member call this constructor again
   *
   *
   */
  Array(std::initializer_list<T> _v)
  {
    size_t i = 0;
    for (typename std::initializer_list<T>::const_iterator it = _v.begin(); it != _v.end(); it++)
    {
      m_Data[i] = (*it);
      i++;
    }
  }

  /**
   *
   * As opposed to what was mentioned above, in order to access this constructor you have to write something
   * like
   * Array<double,2> a = {{3,2}}, which is not only a logical error but also completely undefined
   */
  Array(std::initializer_list<std::initializer_list<T>> _v)
  {
    size_t i = 0;
    for (typename std::initializer_list<std::initializer_list<T>>::const_iterator it = _v.begin(); it != _v.end(); it++)
    {
      size_t j = 0;
      for (typename std::initializer_list<T>::const_iterator jt = it->begin(); jt != it->end(); jt++)
      {
        m_Data[i] = (*jt);
      }
    }
  }


  constexpr size_t size() { return S; }

  T& operator [] (size_t i)
  {
    /// DEBUG
#ifdef __DEBUG__
    if (!(i < S)) { std::cout << "Error out of array bounds\nGiven index: " << i << "\nArray size: " << S << "\nExiting..."; exit(1); }
#endif
    return m_Data[i];
  }

  const T& operator [] (size_t i) const
  {
    /// DEBUG
#ifdef __DEBUG__
    if (!(i < S)) { std::cout << "Error out of array bounds\nGiven index: " << i << "\nArray size: " << S << "\nExiting..."; exit(1); }
#endif
    return m_Data[i];
  }

  friend std::ostream& operator << (std::ostream& out, Array a)
  {
    out << "{";
    for (size_t i = 0; i < S; i++) { out << a[i] << (i == S - 1 ? "" : ", "); }
    out << "}";
    return out;
  }
private:
  T m_Data[S];
};


#endif //ARRAY_H