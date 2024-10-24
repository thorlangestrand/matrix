#include <SFML/Graphics.hpp>
struct Bullet
{
  double angle;           // Initial angle upon being fired
  double x, y;            // Coordinates
  double velocity = 1000.0; // Initial velocity
  sf::CircleShape p;      // Visual portion
};
