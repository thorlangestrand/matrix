#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <random>
#include <list>
#include <type_traits>
#include <functional>
#include "vec2.h"
//#define __DEBUG__
#include "Array.h"


template<size_t R, size_t C, typename T = double>
class Matrix
{
public:
  size_t rows, cols;
  //std::vector<std::vector<T>> entries;
  Array<Array<T, C>, R > entries;

private:
  /**
   * @brief
   * builtin functions stinky
   */
  T _abs(T _v) { return _v > 0 ? _v : -_v; }

  /**
   * @brief
   * Fill vector of Matrix type with number given in val
   * @note just use std::fill if you're not ill in the head
   *
   * @param first     Start iterator
   * @param last      End iterator
   * @param val       Value to fill
   */
  void vecFill(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last, const T val) { while (first != last) { *first = val; first++; } }

  void arrFill(Array<Array<T, C>, R>& _v) {
    for (size_t i = 0; i < _v.size(); i++)
    {
      for (size_t j = 0; j < _v[i].size(); j++)
      {
        _v[i][j] = 0;
      }
    }
  }



  /**
   * @brief
   * Clamp members between -0.001 and 0.001 to 0
   */
  void clampZero() {
    for (size_t i = 0; i < R; i++) {
      for (size_t j = 0; j < C; j++) {
        if (_abs((*this)[i][j]) < 0.001) { (*this)[i][j] = 0; }
      }
    }
  };


  /**
   * @brief
   * Perform some function with return void param T
   * on every member of Matrix
   *
   * Not entirely sure what my plan with this was but
   * I'll keep it in for now
   */
  void each(std::function<void(T)>f)
  {
    for (size_t i = 0; i < R; i++) {
      for (size_t j = 0; j < C; j++) { f((*this)[i][j]); }
    }
  }

  /**
   * @brief
   * Throw error and exit program if given template size
   * and provided size don't match
   */
  void throwSizeMismatchError() {
    std::cout
      << "Error, provided template size and actual size not equal" << "\n"
      << "Error occured at matrix with size " << R << "x" << C << "\n"
      << "Exiting..." << std::endl;
    exit(1);
  }

  /**
   * @brief
   * Throw error and exit program if attempted
   * rotation on non point, currently defined as
   */
  void throwPointRotationMismatchError()
  {
    std::cout
      << "Attempted point rotation on non point!\n"
      << "Expected dimensions for matrix of type point is 1x2\n"
      << "Passed matrix was of dimensions " << rows << "x" << cols << "\n"
      << "Exiting..." << std::endl;
    exit(1);
  }

  /**
 * @brief
 *
 * Zero intializes matrix of size n and returns an identity matrix
 * of size nxn
 *
 * Gotta love c++ errors
 *
 *
 * return Matrix& with return value *this obviously should crash
 * the program as you're saying you're returning a reference
 * but you're actually returning an object
 *
 * What I don't understand is why that raises a
 * std::bad_array_new_length error
 *
 *
 *
 * @return Matrix
 */
  inline Matrix identity()
  {
    this->ZeroInitialize();
    for (size_t i = 0; i < rows; i++) { entries[i][i] = 1; }
    return *this;
  }
public:



  /**
   * @brief
   * Initialize all values in matrix to 0
   */
  inline void ZeroInitialize()
  {
    //entries.resize(rows, std::vector<T>());
    for (size_t i = 0; i < rows; i++) {
      //entries[i].resize(cols);
      //vecFill(entries[i].begin(), entries[i].end(), 0);
      arrFill(this->entries);
    }
  }


  /**
   * @brief
   * Print overload
   * @param out               Stream written to
   * @param m                 Matrix being printed
   * @return std::ostream&    Reference to output stream
   */
  friend std::ostream& operator << (std::ostream& out, Matrix m) {
    out << "\n";
    for (size_t i = 0; i < m.rows; i++)
    {
      out << "{ ";
      for (size_t j = 0; j < m.cols - 1; j++)
      {
        out << m.entries[i][j] << " ";
      }
      out << m.entries[i][m.cols - 1] << " }\n";
    }


    out << "\n";

    for (size_t i = 0; i < m.rows; i++)
    {
      out << "{ ";
      for (size_t j = 0; j < m.cols - 1; j++)
      {
        out << m.entries_s[i][j] << " ";
      }
      out << m.entries_s[i][m.cols - 1] << " }\n";
    }
    return out;
  }





  /**
   * @brief
   * Probably gonna get deleted
   * @param z
   * @return true
   * @return false
   */
  bool setVal(std::vector<std::vector<T>> z)
  {
    return false;
  }



  /**
   * @brief
   * Add values of passed matrix of identical structure to this matrix
   *
   * @param _m
   * @return Matrix<R, C, T>
   */
  inline Matrix<R, C, T> operator + (Matrix <R, C, T> _m)  const
  {
    Matrix<R, C, T> m;

    //m.entries.resize(entries.size());

    for (size_t i = 0; i < entries.size(); i++)
    {
      for (size_t j = 0; j < entries[i].size(); j++)
      {
        m.entries[i][j] = this->entries[i][j] + _m.entries[i][j];
      }
    }
    return m;
  };

  /**
   * @brief
   * Detract values of passed matrix of identical structure from this matrix
   *
   * @param _m
   * @return Matrix<R, C, T>
   */
  inline Matrix<R, C, T> operator - (Matrix <R, C, T> _m) const
  {
    Matrix<R, C, T> m;

    //m.entries.resize(entries.size());

    for (size_t i = 0; i < entries.size(); i++)
    {
      for (size_t j = 0; j < entries[i].size(); j++)
      {
        m.entries[i][j] = this->entries[i][j] - _m.entries[i][j];
      }
    }
    return m;
  }

  /**
   * @brief
   * Matrix Multiplication
   *
   * I desperately feel like I need to explain this to future me
   *
   *
   * Template arguments given to Matrix are
   * R - Int      - Row count
   * C - Int      - Column count
   * T - Typename - Type of data stored in Matrix
   *
   * For two matrices to be able to be multiplied, the first matrix
   * needs to have as many columns as the second matrix has rows
   *
   * As an example, mat2x3 * mat3x2 would be valid as 3 == 3, whereas
   * mat3x2 * mat3x3 would not as 2 != 3
   *
   * This operator takes the first argument R as C
   *
   *
   * This operation is valid only if this current Matrix' column count
   * is equal to the passed Matrix' row count
   *
   * L is required as a placeholder without prior value since
   * we're completely fine with current Matrix row count
   * and passed Matrix column count being different
   *
   * The resulting matrix will be of the dimensions
   * R, current Matrix' row count for rows
   * L, other Matirx' column count for columns
   *
   * @tparam L                  Temporary template variable used to allow different rows in m1 and cols in m2
   * @param _m                  Matrix being multiplied by
   * @return Matrix<R, L, T>    New matrix
   */
  template <size_t L>
  Matrix<R, L, T> operator * (const Matrix<C, L, T>& _m) const {
    Matrix<R, L, T>m;

    for (size_t i = 0; i < R; i++) {
      //m.entries.resize(L);
    }

    /**
     * @brief
     * Loop over row
     * Visual aid because I'm slow in the head
     * {  2, 0, 3 }
     * { -1, 1, 0 } <-- ROW
     *
     *
     * {  2, 0, 3 }
     * { -1, 1, 0 }
     *    ^
     *    |
     *    |
     *  COLUMN
     *
     */
    for (size_t i = 0; i < R; i++)
    {
      for (size_t k = 0; k < L; k++)
      {
        T accum = 0;
        for (size_t j = 0; j < C; j++)
        {
          accum += this->entries[i][j] * _m.entries[j][k];
        }
        m.entries[i][k] = accum;
      }
    }
    m.clampZero();
    return m;
  }



  /**
   * @brief
   * Scalar multiplication
   */
  inline Matrix<R, C, T> operator *(size_t _v) const
  {
    Matrix<R, C, T> m;
    //m.entries.resize(this->entries.size());

    for (size_t i = 0; i < this->entries.size(); i++)
    {
      for (size_t j = 0; j < this->entries[i].size(); j++)
      {
        m.entries[i][j] = this->entries[i][j] * _v;
      }
    }
    return m;
  }

  inline Matrix<R, C, T> operator *= (Matrix<R, C, T> _m) { *this = (*this) * _m; return *this; }

  inline Matrix<R, C, T> operator ^ (size_t v) const
  {
    Matrix<R, C, T> m = Matrix::identityMatrix();

    for (size_t i = 0; i < v; i++) { m *= *this; }
    return m;
  }

  inline Matrix<R, C, T> operator^= (size_t v)
  {
    Matrix<R, C, T>m = Matrix::identityMatrix();

    for (size_t i = 0; i < v; i++) { m *= *this; }
    *this = m;
    return *this;
  }

  /**
   * @brief
   *
   * Returns values in column given by row i
   *
   * Constexpr means it can be evaluated at compile time, which means this won't
   * (shouldn't, haven't tested) work with run-time allocations such as user
   * input, but it should bring the tiniest micron of a performance increase
   * (should, again, haven't tested)
   * @param i     Row
   *
   * @return constexpr std::vector<T>&
   * Vector of values at column given by i
   */
   //constexpr inline std::vector<T>& operator [] (size_t i) noexcept { return entries[i]; }

  constexpr inline Array <T, C>& operator[] (size_t i) noexcept { return entries[i]; }



  /**
   * @brief
   * Returns identity matrix based on passed size
   *
   * @tparam _v                 Dimensions of matrix
   * @return Matrix<_v, _v, T>  Identity matrix of given size
   */
  static inline Matrix<R, C, T> identityMatrix()
  {
    Matrix<R, C, T> m;
    m.ZeroInitialize(); for (size_t i = 0; i < m.rows; i++) m.entries[i][i] = 1; return m;
  }


  /**
   * @brief
   * Rotate a 2x2 matrix based on angle (Radians)
   *
   * Rotation is counter-clockwise in a lefthanded system
   *
   * @param angle
   * @return Matrix<2, 2, T>
   */
  static inline Matrix<2, 2, T> rotate2(double angle)
  {
    Matrix<2, 2, T> m{ {cos(angle), -sin(angle)} ,{sin(angle), cos(angle)} };
    return m;
  }

  /*   static inline Matrix<2, 2, T> rotate2(double angle, vec2 pivot)
    {

    }
    */

    /**
     * @brief
     * Rotate a 2x2 matrix based on angle (Radians)
     *
     * Rotation is clockwise in a lefthanded system
     *
     * @param angle
     * @return Matrix<2, 2, T>
     */
  static inline Matrix<2, 2, T> rotate2cw(double angle)
  {
    Matrix<2, 2, T> m = { {cos(angle), sin(angle)} ,{-sin(angle), cos(angle)} };
    return m;
  }

  static inline Matrix<3, 3, T> rotate3(double angle)
  {
    Matrix<3, 3, T> m;
    return m;
  }

  /**
   * @brief
   *
   * Rotates a point around pivot by a given angle
   *
   * @param angle                   Angle to rotate by (radians)
   * @param pivot                   Pivot point (as given in a lefthanded system)
   * @param ccw                     Rotation direction. Counter-Clockwise by default,
   *                                set to false for clockwise rotation
   *
   * @return Matrix<1, 2, T>        Rotated point
   */
  inline Matrix<1, 2, T> rotatePointPivot2D(double angle, vec2 pivot, bool ccw = true)
  {
    // Ensure correct dimensions
    if (this->rows != 1 || this->cols != 2) { throwPointRotationMismatchError(); }
    Matrix<1, 2, T> ret = { {(*this)[0][0] - pivot.x, (*this)[0][1] - pivot.y } };
    if (ccw) { ret = ret * Matrix<2, 2>::rotate2(angle); }
    else { ret = ret * Matrix<2, 2>::rotate2cw(angle); }
    ret[0][0] += pivot.x;
    ret[0][1] += pivot.y;
    return ret;
  }

  inline Matrix<1, 2, T> rotatePoint2D(double angle, bool ccw = true)
  {
    if (this->rows != 1 || this->cols != 2) { throwPointRotationMismatchError(); }

    Matrix<1, 2, T> ret = { {(*this)[0][0], (*this)[0][1]} };

    if (ccw) { ret = ret * Matrix<2, 2>::rotate2(angle); }
    else { ret = ret * Matrix<2, 2>::rotate2cw(angle); }

    return ret;
  }

  static inline vec2 rotatePointPivot2D(vec2 point, double angle, vec2 pivot, bool ccw = true)
  {
    Matrix<1, 2> tmp = { point.x - pivot.x, point.y - pivot.y };
    if (ccw) { tmp = tmp * Matrix<2, 2>::rotate2(angle); }
    else { tmp = tmp * Matrix<2, 2>::rotate2cw(angle); }
    return vec2{ tmp[0][0] + pivot.x, tmp[0][1] + pivot.y };
  }

  static inline vec2 rotatePoint2D(vec2 point, double angle, bool ccw = true)
  {
    Matrix<1, 2> tmp = { point.x, point.y };
    if (ccw) { tmp = tmp * Matrix<2, 2>::rotate2(angle); }
    else { tmp = tmp * Matrix<2, 2>::rotate2cw(angle); }
    return vec2{ tmp[0][0], tmp[0][1] };
  }

  /**
   * @brief Construct a new Matrix object
   * Default template initializer
   */
  Matrix() { rows = R; cols = C; this->ZeroInitialize(); }

  /**
   * @brief Construct a new matrix object
   * Default value initializer
   * @param _rows       Amount of rows in matrix
   * @param _cols       Amount of columns in matrix
   */
  Matrix(size_t _rows, size_t _cols) { rows = _rows; cols = _cols; this->ZeroInitialize(); }



  /**
   * @brief Construct a new Matrix object
   *
   * Initialize with for example
   *
   * Matrix<2,2,double> m = {{3,2},{4,1}};
   *
   * Unfortunately it is not possible to ensure that the rvalue is valid
   * at compile time, making error checking while using the library entirely
   * up to the user's competence
   *
   * @param _v          Value castable to list of list, e.g. {{3,2},{9,3}}
   */
  Matrix(std::initializer_list<std::initializer_list<T>> _v) {
    rows = R; cols = C;
    //entries.resize(rows, std::vector<T>());

    size_t acc = 0; // Keep track of actual amount of rows

    for (typename std::initializer_list<std::initializer_list<T>>::const_iterator i = _v.begin(); i != _v.end(); i++) {
      int inneracc = 0; // Keep track of actual amount of items in each row
      for (typename std::initializer_list<T>::const_iterator j = i->begin(); j != i->end(); j++) {
        entries[acc][inneracc] = (*j);
        inneracc++;
      }
      if (inneracc != C) { throwSizeMismatchError(); return; } // Throw if provided dimensions don't match template arguments
      acc++;
    }

    if (acc != R) { throwSizeMismatchError(); return; } // Throw if provided dimensions don't match template arguments
  }

  /**
   * @brief Construct a new Matrix object
   *
   * Initialize point with simple x,y coordinates
   *-
   * Example
   *
   * Matrix<1,2> m = { 3,2 };
   *
   * @param _v
   */
  Matrix(std::initializer_list<T> _v)
  {
    rows = R; cols = C; //entries.resize(rows, std::vector<T>());
    size_t accum = 0;
    for (typename std::initializer_list<T>::const_iterator i = _v.begin(); i != _v.end(); i++) { entries[0][accum] = (*i); accum++; }
    if (accum != C) { throwSizeMismatchError(); return; }
  }

  Matrix(std::initializer_list<int> _v)
  {
    rows = R; cols = C; //entries.resize(rows, std::vector<T>());
    size_t accum = 0;
    for (typename std::initializer_list<int>::const_iterator i = _v.begin(); i != _v.end(); i++) { entries[0][accum] = (*i); accum++; }
    if (accum != C) { throwSizeMismatchError(); return; }
  }

  ~Matrix() {};
};


#endif //MATRIX_H




