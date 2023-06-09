
#include "Matrixs.h"

using namespace std;

#pragma region exceptions
void __throw_if_out_of_range(Matrixs *m, UINT row, UINT col)
{
	if (row >= m->GetRows() || col >= m->GetCols())
	{
		throw std::out_of_range("Out of range!");
	}
}
void __throw_if_matrices_size_does_not_match(const Matrixs *a, const Matrixs *b)
{
	if (a->GetRows() != b->GetRows() || a->GetCols() != b->GetCols())
		throw std::invalid_argument("The size of the matrices does not match!");
}

void __throw_if_matrix_does_not_exist(float **matrix_array)
{
	if (!matrix_array)
		throw std::invalid_argument("The matrix don't exist!");
}
void __throw_if_non_square_matrix(Matrixs *m)
{
	if (m->GetRows() != m->GetCols())
		throw std::invalid_argument(" The matrix is not square!");
}
void __throw_if_determinant_equals_zero(float detMatrix)
{
	if (detMatrix == 0)
	{
		throw std::invalid_argument(" Determinant matrix equal to zero!");
	}
}
#pragma endregion

Matrixs::Matrixs()
{
	this->rows = 1;
	this->cols = 1;
	this->matrix = new float *[rows];
	for (UINT i = 0; i < rows; i++)
		this->matrix[i] = new float[cols];
	for (UINT i = 0; i < this->rows; i++)
		for (UINT j = 0; j < this->cols; j++)
			this->matrix[i][j] = NULL;
}

Matrixs::Matrixs(const UINT rows, const UINT cols)
{
	SetSizeMatrix(rows, cols);
}

Matrixs::Matrixs(const Matrixs &otherMatrix)
{
	this->SetSizeMatrix(otherMatrix.rows, otherMatrix.cols);
	for (UINT i = 0; i < otherMatrix.rows; i++)
		for (UINT j = 0; j < otherMatrix.cols; j++)
			this->matrix[i][j] = otherMatrix.matrix[i][j];
}

Matrixs::~Matrixs()
{
	for (UINT i = 0; i < this->rows; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;
}

void Matrixs::SetSizeMatrix(const UINT rows, const UINT cols)
{
	this->rows = rows;
	this->cols = cols;
	this->matrix = new float *[rows];
	for (UINT i = 0; i < rows; i++)
		this->matrix[i] = new float[cols];
	for (UINT i = 0; i < this->rows; i++)
		for (UINT j = 0; j < this->cols; j++)
			this->matrix[i][j] = NULL;
}



void Matrixs::InputElementMatrix(const float value, UINT row, UINT col)
{
	__throw_if_out_of_range(this, row, col);
	matrix[row][col] = value;
}

float Matrixs::OutputElement(const UINT row, const UINT col)
{
	__throw_if_out_of_range(this, row, col);
	return matrix[row][col];
}



Matrixs Matrixs::operator+(const Matrixs &otherMatrix)
{

	__throw_if_matrix_does_not_exist(otherMatrix.matrix);
	__throw_if_matrices_size_does_not_match(this, &otherMatrix);
	Matrixs temp;
	temp.SetSizeMatrix(otherMatrix.rows, otherMatrix.cols);
	for (UINT i = 0; i < temp.rows; i++)
		for (UINT j = 0; j < temp.cols; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] + otherMatrix.matrix[i][j];
		}
	return temp;
}

Matrixs Matrixs::operator-(const Matrixs &otherMatrix)
{
	__throw_if_matrix_does_not_exist(otherMatrix.matrix);
	__throw_if_matrices_size_does_not_match(this, &otherMatrix);
	Matrixs temp;
	temp.SetSizeMatrix(otherMatrix.rows, otherMatrix.cols);
	for (UINT i = 0; i < temp.rows; i++)
		for (UINT j = 0; j < temp.cols; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] - otherMatrix.matrix[i][j];
		}
	return temp;
}

Matrixs Matrixs::operator*(const Matrixs &otherMatrix)
{

	__throw_if_matrix_does_not_exist(otherMatrix.matrix);
	__throw_if_matrices_size_does_not_match(this, &otherMatrix);
	if (this->cols == otherMatrix.rows)
	{
		Matrixs temp;
		UINT k, j, i;
		temp.SetSizeMatrix(rows, otherMatrix.cols);
		for (k = 0; k < temp.rows; k++)
			for (j = 0; j < temp.cols; j++)
			{
				temp.matrix[k][j] = 0;
				for (i = 0; i < cols; i++)
					temp.matrix[k][j] += this->matrix[k][i] * otherMatrix.matrix[i][j];
			}
		return temp;
	}
}

Matrixs Matrixs::operator*(float s)
{
	__throw_if_matrix_does_not_exist(this->matrix);
	Matrixs temp;
	temp.SetSizeMatrix(rows, cols);
	for (UINT i = 0; i < temp.rows; i++)
		for (UINT j = 0; j < temp.cols; j++)
		{
			temp.matrix[i][j] = s * this->matrix[i][j];
		}
	return temp;
}

Matrixs &Matrixs::operator=(const Matrixs &otherMatrix)
{
	__throw_if_matrix_does_not_exist(otherMatrix.matrix);

	this->SetSizeMatrix(otherMatrix.rows, otherMatrix.cols);
	for (UINT i = 0; i < this->rows; i++)
		for (UINT j = 0; j < this->cols; j++)
		{
			this->matrix[i][j] = otherMatrix.matrix[i][j];
		}
	return *this;
}

Matrixs &Matrixs::operator+=(const Matrixs &otherMatrix)
{
	__throw_if_matrix_does_not_exist(otherMatrix.matrix);
	__throw_if_matrices_size_does_not_match(this, &otherMatrix);

	for (UINT i = 0; i < this->rows; i++)
		for (UINT j = 0; j < this->cols; j++)
		{
			this->matrix[i][j] = this->matrix[i][j] + otherMatrix.matrix[i][j];
		}
	return *this;
}

bool Matrixs::operator==(const Matrixs &otherMatrix)
{
	try
	{
		__throw_if_matrix_does_not_exist(otherMatrix.matrix);
		__throw_if_matrices_size_does_not_match(this, &otherMatrix);
	}
	catch (std::exception)
	{
		return false;
	}

	for (UINT i = 0; i < this->rows; i++)
		for (UINT j = 0; j < this->cols; j++)
		{
			if (this->matrix[i][j] != otherMatrix.matrix[i][j])
			{
				return false;
			}
		}
	return true;
}

Matrixs Matrixs::T()
{
	__throw_if_matrix_does_not_exist(this->matrix);

	Matrixs NewMatrix(cols, rows);
	for (UINT i = 0; i < rows; i++)
		for (UINT j = 0; j < cols; j++)
		{
			NewMatrix.matrix[j][i] = matrix[i][j];
		}
	Matrixs temp(cols, rows);
	for (UINT i = 0; i < rows; i++)
		for (UINT j = 0; j < cols; j++)
		{
			temp.matrix[j][i] = matrix[i][j];
		}
	for (UINT i = 0; i < cols; i++)
		for (UINT j = 0; j < rows; j++)
		{
			NewMatrix.matrix[i][j] = temp.matrix[i][j];
		}
	return NewMatrix;
}

void getMatrixMinor(Matrixs &Matrix, UINT row, UINT col, Matrixs &NewMatrix)
{
	UINT offsetRow = 0;
	UINT offsetCol = 0;
	for (UINT i = 0; i < Matrix.rows - 1; i++)
	{

		if (i == row)
		{
			offsetRow = 1;
		}

		offsetCol = 0;
		for (UINT j = 0; j < Matrix.rows - 1; j++)
		{
			if (j == col)
			{
				offsetCol = 1;
			}
			NewMatrix.matrix[i][j] = Matrix.matrix[i + offsetRow][j + offsetCol];
		}
	}
}



float Det(Matrixs &Matrix)
{
	__throw_if_non_square_matrix(&Matrix);
	int det = 0;
	if (Matrix.rows == 1)
		return Matrix.matrix[0][0];
	if (Matrix.rows == 2)
		return Matrix.matrix[0][0] * Matrix.matrix[1][1] - Matrix.matrix[0][1] * Matrix.matrix[1][0];
	else
	{
		Matrixs NewMatrix;
		NewMatrix.SetSizeMatrix(Matrix.rows - 1, Matrix.rows - 1);
		for (UINT j = 0; j < Matrix.rows; j++)
		{
			getMatrixMinor(Matrix, 0, j, NewMatrix);
			det += pow(-1, j) * Matrix.matrix[0][j] * Det(NewMatrix);
		}
	}
	return det;
}



Matrixs ReverseMatrix(Matrixs &Matrix)
{
	__throw_if_non_square_matrix(&Matrix);
	float detMatrix = Det(Matrix);
	__throw_if_determinant_equals_zero(detMatrix);
	UINT size = Matrix.rows;
	// create new matrix about size diff one
	Matrixs NewMatrix;
	NewMatrix.SetSizeMatrix(size - 1, size - 1);
	Matrixs ReverseMatrix;
	ReverseMatrix.SetSizeMatrix(size, size);
	for (UINT row = 0; row < size; row++)
		for (UINT col = 0; col < size; col++)
		{
			getMatrixMinor(Matrix, row, col, NewMatrix);
			ReverseMatrix.matrix[row][col] = (pow(-1, row + col) * (1 / detMatrix) * Det(NewMatrix));
		}

	return ReverseMatrix.T();
}