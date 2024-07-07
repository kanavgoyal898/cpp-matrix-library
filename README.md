# C++ Matrix Library

## Overview

This library provides robust classes and functions to work with matrices and fractions in C++. It is designed to facilitate complex mathematical computations and ease the process of handling matrices and fractions. The library includes comprehensive features for matrix operations, file I/O for CSV files, and various utility functions for diverse mathematical computations.

<div style="text-align: center;">
  <img src="./matrix.png" alt="Preview" style="width: 100%;">
</div>

## Features

### Fraction Class

#### Constructors

- `Fraction()`
  - Default constructor.
- `Fraction(int num, int den)`
  - Parameterized constructor with numerator (`num`) and denominator (`den`).

#### Setter Functions

- `void setNumerator(int num)`
  - Set numerator to `num`.
- `void setDenominator(int den)`
  - Set denominator to `den`.
- `void setFraction(int num, int den)`
  - Set both numerator and denominator.

#### Getter Functions

- `int getNumerator() const`
  - Get the numerator.
- `int getDenominator() const`
  - Get the denominator.
- `std::pair<int, int> getFraction() const`
  - Get the fraction as a pair.

#### Utility Functions

- `int gcd(int a, int b) const`
  - Calculate the greatest common divisor (GCD).
- `void simplify()`
  - Simplify the fraction to its simplest form.

#### Display Function

- `void display() const`
  - Display the fraction in `numerator/denominator` format.

#### Operations

- `Fraction inverse() const`
  - Get the inverse of the fraction.

#### Operator Overloading

- `Fraction operator+(const Fraction& other) const`
  - Addition with another fraction.
- `Fraction operator-(const Fraction& other) const`
  - Subtraction with another fraction.
- `Fraction operator*(const Fraction& other) const`
  - Multiplication with another fraction.
- `Fraction operator/(const Fraction& other) const`
  - Division with another fraction.
- `Fraction operator+(int value) const`
  - Addition with an integer.
- `Fraction operator-(int value) const`
  - Subtraction with an integer.
- `Fraction operator*(int value) const`
  - Multiplication with an integer.
- `Fraction operator/(int value) const`
  - Division with an integer.
- `Fraction operator-() const`
  - Unary negation.
- `friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction)`
  - Output stream operator.
- `friend std::istream& operator>>(std::istream& is, Fraction& fraction)`
  - Input stream operator.

### Matrix Class

#### Constructors

- `Matrix()`
  - Default constructor.
- `Matrix(int rows, int cols)`
  - Parameterized constructor with number of rows (`rows`) and columns (`cols`).
- `Matrix(int size, const Fraction& diagonalValue)`
  - Parameterized constructor for diagonal scalar matrix.
- `Matrix(int rows, int cols, const std::vector<std::vector<Fraction>>& elements)`
  - Parameterized constructor with elements from an array.
- `Matrix(const Matrix& other)`
  - Copy constructor.

#### Destructor

- `~Matrix()`
  - Properly deallocates memory.

#### Display Function

- `void display() const`
  - Display the matrix.

#### Set and Get Functions

- `void setElement(int row, int col, const Fraction& value)`
  - Set the element at `row` and `col` to `value`.
- `Fraction getElement(int row, int col) const`
  - Get the element at `row` and `col`.

#### In-Built Functions

- `Fraction trace() const`
  - Calculate the trace of the matrix.
- `Fraction determinant() const`
  - Calculate the determinant of the matrix.
- `int rowMajorOrder(int row, int col) const`
  - Calculate the position in row-major order.
- `int columnMajorOrder(int row, int col) const`
  - Calculate the position in column-major order.
- `Matrix power(int exponent) const`
  - Raise the matrix to a power of `exponent`.
- `Matrix reshape(int newRows, int newCols) const`
  - Reshape the matrix to `newRows` x `newCols`.
- `Matrix transpose() const`
  - Transpose the matrix.
- `Matrix concatenateRows(const Matrix& other) const`
  - Concatenate with another matrix along rows.
- `Matrix concatenateColumns(const Matrix& other) const`
  - Concatenate with another matrix along columns.
- `std::vector<Fraction> characteristicPolynomial() const`
  - Calculate the characteristic polynomial of the matrix.

#### Operator Overloading

- `Matrix operator*(const Fraction& value) const`
  - Multiplication by a fraction.
- `Matrix operator+(const Matrix& other) const`
  - Addition with another matrix.
- `Matrix operator-(const Matrix& other) const`
  - Subtraction with another matrix.
- `Matrix operator*(const Matrix& other) const`
  - Multiplication with another matrix.
- `Matrix& operator=(const Matrix& other)`
  - Assignment operator.
- `std::vector<Fraction>& operator[](int index)`
  - Subscript operator for accessing rows.
- `friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix)`
  - Output stream operator.

### File I/O

- `void readCSV(const std::string& filename)`
  - Reads a matrix from a CSV file.
- `void writeCSV(const std::string& filename) const`
  - Writes a matrix and its properties (trace, determinant, transpose, characteristic polynomial) to a CSV file.

## Usage

- Create or import matrices.
- Perform various matrix operations.
- Read and write matrices to and from CSV files.

## Authors

- Himanshu Dania [GitHub](https://github.com/Himanshu-Dania)
- Kanav Goyal [GitHub](https://github.com/kanavgoyal898)