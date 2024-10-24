#ifndef SCOPEDTIMER_H
#define SCOPEDTIMER_H
#include <iostream>
#include <chrono>

class ScopedTimer
{
private:
  const std::string& m_name;
  std::chrono::_V2::system_clock::time_point m_created;
public:
  ScopedTimer(const std::string& _name)
    : m_name(_name)
  {
    m_created = std::chrono::high_resolution_clock::now();
  };
  ~ScopedTimer()
  {
    std::cout << m_name << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_created).count() << "ms\n";
  };
};

class ScopedTimerNs
{
private:
  const std::string& m_name;
  std::chrono::_V2::system_clock::time_point m_created;
public:
  ScopedTimerNs(const std::string& _name)
    : m_name(_name)
  {
    m_created = std::chrono::high_resolution_clock::now();
  };
  ~ScopedTimerNs()
  {
    std::cout << m_name << ": " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_created).count() << "ns\n";
  };
};


#endif //SCOPEDTIMER_H