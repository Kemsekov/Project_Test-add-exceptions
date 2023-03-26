#pragma once

#include <iostream>

typedef unsigned int UINT;

class Matrixs
{

	friend void getMatrixMinor(Matrixs& Matrix, UINT row, UINT col, Matrixs& NewMatrix);
	friend float Det(Matrixs& matrix);
	friend Matrixs ReverseMatrix(Matrixs& matrix);
private:
	float** matrix;
	UINT rows, cols;
public:

	Matrixs(); // Default Constructor
	Matrixs(const UINT rows, const UINT cols); // Constructor
	Matrixs(const Matrixs& other); // Constructor copying
	void SetSizeMatrix(const UINT rows, const UINT cols);
	UINT GetRows() { return rows; }
	UINT GetCols() { return cols; }
	float OutputElement(const UINT row, const UINT col); // The matrix element output 
	void InputElementMatrix(const float value, UINT row = 0, UINT col = 0); // The matrix element input
	Matrixs T(); // Transposition matrix
	Matrixs& operator=(const Matrixs& otherMatrix);
	Matrixs operator+(const Matrixs& otherMatrix);
	Matrixs operator-(const Matrixs& otherMatrix);
	Matrixs operator*(const Matrixs& otherMatrix);
	Matrixs operator*(float s);
	Matrixs& operator+=(const Matrixs& otherMatrix);
	bool operator==(const Matrixs& otherMatrix);
	
	~Matrixs(); // destructor
};