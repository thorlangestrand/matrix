#include <iostream>
#include "matrix.h"
#define PI 3.1415926535897932384626433
#include <SFML/Graphics.hpp>

int main(int argc, char const* argv[])
{
  //using Matrix = Matrix<double>;
  //Matrix m(4, 5);
  //std::cout << m << "ming";
  //Matrix<double> huh = Matrix<double>::identityMatrix(5);

  //std::cout << huh;

  //mat2x2<double> m1;
  //mat2x2<double> m3;

  //m1 = m3;
  //m1.setVal({ { 2,3 },{ 9,4 } });

  //mat3x2<double> m2;

  //std::cout << m1 * m2;

  //using mat2x2 = Matrix<double>::tb2();

  //Matrix<double> uhm = Matrix<double>::tb2();
  //std::cout << huh * uhm;

//  using mat2x3 = Matrix<double, 2, 3>;
//  using mat3x2 = Matrix<double, 3, 2>;



/*   using mat2x2 = Matrix<2, 2>;

  mat2x2 A{ {1,2},{2,0} };
  mat2x2 B{ {1,6},{4,2} };

  //A = A ^ 2;
  std::cout << A * B;
 */


  using mat3x3 = Matrix<3, 3>;
  using mat5x5 = Matrix<5, 5>;

  //using mat1x1 = Matrix<1, 1, int>;
  //  size_t d = 2;
/*   std::vector<int> cum = { 2 };
  std::vector<std::vector<double>> d = { {3,2,1} };
 */
 /*
   mat3x3 m4 = mat3x3::identityMatrix<3>();


   mat5x5 m5 = mat5x5::identityMatrix<5>(); */
  using mat2x2 = Matrix<2, 2>;
  /*   using mat3x2 = Matrix<3, 2>;

    using mat2x3 = Matrix<2, 3>;
    mat2x3 m1 = { { 2,0,3 }, { -1,1,0 } };
    mat2x3 m3 = { { 2,-5,3 }, { 1,1,0 } };
    mat3x2 m2 = { { 4, 3 }, { 2,2 }, { -2, -1 } };



    mat2x2 m6{ { 3,4 }, { 9,1 } };

    std::cout << m1;
    std::cout << m2;
    std::cout << m1 << " * " << m2 << " = " << m1 * m2;

    std::cout << m1 << " + " << m3 << " = " << m1 + m3;

    std::cout << m1 << " - " << m3 << " = " << m1 - m3;

    std::cout << m1 << " * " << 2 << " = " << m1 * 2;

    //std::cout << m1 << " * " << m4 << " = " << m1 * m4;
    std::cout << m6;

    std::cout << Matrix<5, 5>::identityMatrix();

    Matrix<5, 5> z;
    z.entries[0][3] = 2;
    z.ZeroInitialize();
    std::cout << z; */
    /*   mat3x3 A4 = { {0,1,0},{1,1,2},{0,2,0} };

      mat2x2 aaa = { {0,1},{-1,0} };
      //std::cout << "(A1)" << A1 << "A1 ^ 3 = " << (A1 ^ 3);
      A4 ^= 2;
      std::cout << A4;
      std::cout << (aaa ^ 2);
      std::cout << v * a;


      using mat2x3 = Matrix<2, 3>;
      using mat3x2 = Matrix<3, 2>;
      mat2x3 cum = { {3,4,9},{-5,2,5} };
      mat3x2 semen = { {9,7},{-9,9},{1,0} };
      mat3x3 balls = { {9,9,1},{7,63,1},{9,-1,4} };
      std::cout << cum * semen;

      std::cout << cum * balls; */


  mat2x2 A1 = { {1,2},{2,0} };
  mat2x2 A2 = { {1,2},{2,0} };
  //A1.identity();
  using mat3x3 = Matrix<3, 3>;

  mat3x3 A3 =
  { {0,1,0},
    {1,1,2},
    {0,2,0}, };

  using mat1x3 = Matrix<1, 3>;
  using mat3x1 = Matrix<3, 1>;

  mat1x3 v = { {4,3,1} };
  mat3x1 a = { {1},{0},{0} };


  /*   mat3x3 Rx = { {1,0,0},{0,cos(PI / 2),-sin(PI / 2)},{0,sin(PI / 2),cos(PI / 2)} };

    std::cout << "huh";
    //a = Rx * a;

    using mat1x2 = Matrix<1, 2>;
    mat1x2 vpos = { {5,2} };
    mat2x2 R = { {cos(PI / 2),-sin(PI / 2)},{sin(PI / 2),cos(PI / 2)} };

    using mat1x1 = Matrix<1, 1>;
    mat1x1 p1 = { {5} };
    mat1x1 p2 = { {2} };

    using mat2x1 = Matrix<2, 1>;
    mat2x1 rotPoint = { {3},{2} };

    mat2x1 Rv = R * rotPoint;


    mat2x1 real2r = { {3 * cos(PI / 2) - 2 * sin(PI / 2)},{3 * sin(PI / 2) + 2 * cos(PI / 2)} };


    std::cout << vpos * R; */


  Matrix<1, 2> val = { {1,1} };
  Matrix<2, 2> R = { {1 / sqrt(2),-1 / sqrt(2)},{1 / sqrt(2),1 / sqrt(2)} };


  std::cout << val * R;
  //std::cout << Rv;

  //std::cout << v * Rx;



  std::cout << "notbroken";

  return 0;
}