#ifndef __MY_MATRIX_PLUS_HPP_
#define __MY_MATRIX_PLUS_HPP_

#include <cassert>
#include <iostream>
#include <cmath>
#include <exception>

class Matrix{
public:
  Matrix();
  Matrix(int line, int collumn);
  
  int get_collumn();
  int get_line();
  int get_element(int line, int collumn);
  
  void set_collumn(int collumn);
  void set_line(int line);
  void set_element(int line, int collumn, double new_value);
  
  bool Eq_matrix(const Matrix &other);
  void Sum_matrix(const Matrix &other);
  void Sub_matrix(const Matrix &other);
  void Mul_number(double num);
  void Mul_matrix(const Matrix &other);
  Matrix Transpose();
  
private:
  int collumn_;
  int line_;
  double** matrix_;
  double** allocate_matrix(int line, int collumn);
  void fill();
  
};

#endif //__MY_MATRIX_PLUS_HPP_
