#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"
#include "Line.h"
#define PI 3.1415926535897932384626433


#define mat3x3 Matrix<3,3>

using v2 = vector2<double>;


float rnd() {
  static std::random_device device;
  static std::mt19937 gen(device());
  static std::uniform_real_distribution<float> dist(0.0F, 1.0F);
  return dist(gen);
}

float rnd(float low, float high) {
  return rnd() * (high - low) + low;
}

int main(int argc, char const* argv[])
{
  const double windowx = 1400.0;
  const double windowy = 1400.0;
  const double midx = windowx / 2.0;
  const double midy = windowy / 2.0;

  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");

  double angle = 0;

  sf::CircleShape p; p.setRadius(1.0f); p.setFillColor(sf::Color::Red); p.setPosition(midx, midy);

  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt)) { if (evt.type == sf::Event::Closed) { window.close(); } }

    window.clear();

    Line root = { {midx,midy},{midx,midy},sf::Color::Green };
    Line rootr = root.rotate(angle * 0.5, { midx,midy });
    std::vector<Line> test;
    test.push_back(root);
    window.draw(rootr);
    for (int i = 0; i < 10; i++)
    {
      Line l = { {test.back().end}, {test.back().end + (rnd() > 0.01f ? -50 : 50)}, sf::Color::Red };
      Line lr = l.rotate(angle * (double)rnd(), test.back().end, (rnd() > 0.5f ? true : false));
      test.push_back(lr);
      window.draw(lr);
    }
    window.draw(p);
    window.display();
    angle += 0.0001;
  }

  std::cout << "notbroken";

  return 0;
}