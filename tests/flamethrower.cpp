#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"
#include "Path.h"
#include "Line.h"
#include "Target.h"
#include "rnd.h"

#define PI 3.1415926535897932384626433
const double windowx = 1400.0;
const double windowy = 1400.0;
const double midx = windowx / 2.0;
const double midy = windowy / 2.0;
int score = 0;



struct Bullet
{
  double angle;             // Initial angle upon being fired
  double x, y, r;              // Coordinates
  double a = 255;
  double velocity = 100.0; // Initial velocity
};



std::vector<Target> targets; // All targets currently in play
std::vector<Bullet> bullets; // All bullets currently in play




/**
 * @brief
 * Clear objects that are out of bounds
 * @tparam T
 * @param _v
 */
template <typename T>
void clearOOB(std::vector<T>& _v)
{
  for (typename std::vector<T>::iterator it = _v.begin(); it != _v.end();)
  {
    if ((*it).x < -100 || (*it).x > windowx + 100 || (*it).y < -100 || (*it).y > windowy + 100)
    {
      it = _v.erase(it);
    }
    else {
      it++;
    }
  }
}



// Adding a bit of randomness to angle gives us a shotgun effect, cool!
// Could use this for a particle system too maybe?
void fireCannons(Path& _p, double angle, double _scale, double bulletVelocity)
{
  Bullet b;
  // Get tip of rocket
  vec2 _r = Matrix<1, 2>::rotatePointPivot2D(_p.getPoint(6), angle, _p.centre);
  b.x = _r.x; b.y = _r.y;

  b.r = 5.0; // Radius
  b.velocity = bulletVelocity;
  b.angle = angle;

  bullets.push_back(b);

}

void updateBullets(double dt)
{
  // Remove offscreen 
  clearOOB(bullets);


  for (Bullet& b : bullets)
  {
    b.x += -sin(b.angle) * b.velocity * dt;
    b.y += -cos(b.angle) * b.velocity * dt;
  }

}


void newTarget()
{
  Target t(rnd(100, windowx - 100), rnd(100, windowy - 100), rnd(50, 100));
  targets.push_back(t);
}


bool hit(Bullet& _b, Target& _t)
{
  return ((_t.x - _b.x) * (_t.x - _b.x) + (_t.y - _b.y) * (_t.y - _b.y)) <= (_b.r + _t.r) * (_b.r + _t.r);
}



void scoreUp()
{
  std::cout << "Points: " << ++score << "\n";
}





int main()
{

  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");
  //window.setFramerateLimit(144);

  double angle = 0;

  //sf::CircleShape p; p.setRadius(1.0f); p.setFillColor(sf::Color::Red); p.setPosition(midx, midy);

  double scale = 25;

  Path _p = { {-scale,scale}, {scale,scale}, {-scale,-scale}, {scale,-scale}, {-scale,scale},{-scale,-scale}, {0 * scale,-2 * scale}, {scale,-scale}, {scale,scale} };
  _p.translate({ midx,midy });


  // Deltatime
  sf::Clock clock;
  clock.restart();
  float dt = 0.f;

  // Fire delay, used so we don't get infinite firing speed
  double fireDelay = 0.0;
  const double fireRateScalar = 1000.0;
  const double angleScalar = 8.0;
  const double translateScalar = 800.0;
  const double bulletVelocityScalar = 100.0;
  double targetSpawnDelay = 0.0;
  const double targetSpawnTimeScalar = 0.0;
  const double alphaFadeScalar = 100.0;

  // Used to draw bullets
  sf::CircleShape bulletParticle;
  bulletParticle.setFillColor(sf::Color::Red);

  // Used to draw targets
  sf::CircleShape targetParticle;

  while (window.isOpen())
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { angle += angleScalar * dt; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { angle -= angleScalar * dt; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { _p.translate({ -sin(angle) * translateScalar * dt, -cos(angle) * translateScalar * dt }); } // Rotate left relative to tip
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { _p.translate({ sin(angle) * translateScalar * dt, cos(angle) * translateScalar * dt }); } // Rotate right relative to tip
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { if (fireDelay > 1) { fireCannons(_p, angle + rnd(-0.5, 0.5), scale, bulletVelocityScalar); fireDelay = 0; } }

    if (targetSpawnDelay > 1.0) { newTarget(); targetSpawnDelay = 0.0; }
    dt = clock.restart().asSeconds();

    sf::Event evt;
    while (window.pollEvent(evt))
    {
      if (evt.type == sf::Event::Closed) { window.close(); }
      if (evt.type == sf::Event::KeyPressed) { if (evt.key.code == sf::Keyboard::Escape) { window.close(); } }
    }


    updateBullets(dt);
    window.clear();
    _p.draw(window, angle);








    for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
    {
      bool _hit = false;
      for (std::vector<Target>::iterator jt = targets.begin(); jt != targets.end();)
      {
        if (hit(*it, *jt)) { jt = targets.erase(jt); _hit = true; scoreUp(); }
        else { jt++; }
      }
      if (_hit) { it = bullets.erase(it); }
      else { it++; }
    }
    for (Target& t : targets)
    {
      if (t.a < 255) { t.a += alphaFadeScalar * (double)dt; }
      targetParticle.setOrigin({ (float)t.r, (float)t.r });
      targetParticle.setPosition({ (float)t.x, (float)t.y });
      targetParticle.setRadius((float)t.r);
      targetParticle.setFillColor(sf::Color(255, 255, 255, t.a));
      window.draw(targetParticle);
    }
    for (Bullet& b : bullets)
    {
      bulletParticle.setOrigin({ (float)b.r, (float)b.r });
      bulletParticle.setPosition({ (float)b.x, (float)b.y });
      bulletParticle.setRadius((float)b.r);

      bulletParticle.setFillColor(sf::Color(0, 255, 255, b.a));
      if (b.a > 0) { b.a -= 0.5; };
      window.draw(bulletParticle);
    }
    window.display();

    fireDelay += fireRateScalar * (double)dt;
    targetSpawnDelay += targetSpawnTimeScalar * (double)dt;
    //alphaUpdateDelay += 1 * (double)dt;
    //fireCannons(_p, angle, scale, bulletVelocityScalar);
  }

  std::cout << "Final score: " << score << "\n";
  std::cout << "notbroken";

  return 0;
}