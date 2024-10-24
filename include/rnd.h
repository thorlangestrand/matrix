#ifndef RND_H
#define RND_H

#include <random>

double rnd()
{
  static std::random_device device;
  static std::mt19937 gen(device());
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(gen);
}

double rnd(double low, double high)
{
  return rnd() * (high - low) + low;
}

#endif //RND_H