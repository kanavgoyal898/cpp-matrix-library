#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Fraction;
class Matrix {
    private:
        int row;
        int col;
        Fraction **arr;
        friend class Fraction;
    public:
    // Constructors
        Matrix() {
            row = 0;
            col = 0;
        }
        Matrix(int row, int col) {
            try {
                if(row==0 || col==0){
                    throw("Dimensions Mismatch");
                }
                this->row = row;
                this->col = col;
                arr = new Fraction*[row];
                for(int i = 0; i < row; i++) {
                    arr[i] = new Fraction[col];
                    for(int j = 0; j < col; j++) {
                        arr[i][j] = 0;
                    }
                }
            } catch(const char*e){
                cout << e;
                exit(2);
            }
        }
    // Diagonal Scalar Matrix
        Matrix(int row, int col, int diagonalElement) {
            try{
                if(row==0 || col==0){
                    throw("Dimensions Mismatch");
                }
                this->row = row;
                this->col = col;
                arr = new Fraction*[row];
                for(int i = 0; i < row; i++) {
                    arr[i] = new Fraction[col];
                    for(int j = 0; j < col; j++) {
                        if(i == j) {
                            arr[i][j] = diagonalElement;
                        } else {
                            arr[i][j] = 0;
                        }
                    }
                }
            } catch(const char*e) {
                cout << e;
                exit(2);
            } 
        }
        Matrix(int row, int col, Fraction diagonalElement) {
            try{
                if(row==0 || col==0){
                    throw("Dimensions Mismatch");
                }
                this->row = row;
                this->col = col;
                arr = new Fraction*[row];
                for(int i = 0; i < row; i++) {
                    arr[i] = new Fraction[col];
                    for(int j = 0; j < col; j++) {
                        if(i == j) {
                            arr[i][j].frac.first = diagonalElement.frac.first;
                            arr[i][j].frac.second = diagonalElement.frac.second;
                        } else {
                            arr[i][j] = 0;
                        }
                    }
                }
            } catch(const char*e) {
                cout << e;
                exit(2);
            }
        }
    // Diagonal Matrix
        Matrix(int row, int col, int arry[], int n) {
            try{
                if(row==0 || col==0){
                    throw("Dimensions Mismatch");
                }
                this->row = row;
                this->col = col;
                int k = 0;
                arr = new Fraction*[row];
                for(int i = 0; i < row; i++) {
                    arr[i] = new Fraction[col];
                    for(int j = 0; j < col; j++) {
                        // type-conversion (primitive to non-primitive)
                        arr[i][j] = k>=n?Fraction():Fraction(arry[k++]);
                    }
                }
            } catch(char*e) {
                cout << e;
                exit(2);
            }
        }
        Matrix(int row, int col, Fraction arry[], int n) {
            try{
                if(row==0 || col==0){
                    throw("Dimensions Mismatch");
                }
                this->row = row;
                this->col = col;
                
                int k = 0;
                arr = new Fraction*[row];
                for(int i = 0; i < row; i++) {
                    arr[i] = new Fraction[col];
                    for(int j = 0; j < col; j++) {
                        arr[i][j] = k>=n?Fraction():arry[k++]; 
                    }
                }
            } catch(const char*e) {
                cout << e;
                exit(2);
            }
        }
    // Copy Constructor
        Matrix(const Matrix &m) {
            row = m.row;
            col = m.col;
            arr = new Fraction*[row];
            for(int i = 0; i < row; i++) {
                arr[i] = new Fraction[col];
                for(int j = 0; j < col; j++) {
                    arr[i][j] = m.arr[i][j];
                }
            }
        }
    // Destructor
        ~Matrix() {
            for (int i = 0; i < row; i++) {
                delete[] arr[i];
            }
            delete[] arr;
        }
    // Display Function
        void display() {
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    arr[i][j].display();
                }
                cout << endl;
            }
        }
    // Set Individual Elements
        int getR() {
            return row;
        }
        int getC() {
            return col;
        }
        Fraction setElement(int row, int col, Fraction value) {
            try{
                if(row>this->row || col>this->col){
                    throw("Dimension Mismatch");
                }
                arr[row][col] = value;
                return value;
            }
            catch(const char* e){
               throw(e);
               exit(2); 
            }
        }
        Fraction getElement(int i, int j) {
            return arr[i][j];
        }
    
    // In-Built Functions:
        Fraction trace();
        Fraction determinant();
        Fraction positionRowMajor(int);
        Fraction positionColMajor(int);
        Matrix power(int);
        Matrix reshape(int, int);
        Matrix transpose();
        Matrix concatenate(Matrix&, int);
        Matrix characteristicPolynomial();
    // Operator Overloading:
        Matrix operator *(int);
        Matrix operator *(Fraction);
        Matrix operator +(Matrix &);
        Matrix operator -(Matrix &);
        Matrix operator *(Matrix &);
        Matrix& operator=(const Matrix &m);
        Fraction* operator[](int i) {
            try {
                if (i < 0 || i >= row) {
                    throw("Dimension Mistmatch");
                }
                return arr[i];
            } catch(char* e){
                cout << e;
                exit(2);
            } 
        }
        friend void operator << (ostream & cout, Matrix& m) {
            for(int i = 0; i < m.row; i++) {
                for(int j = 0; j < m.col; j++) {
                    m.arr[i][j].display();
                }
                cout << endl;
            }
        }
};

Fraction Matrix::trace() {
    try{
        if(row != col){
            throw("Dimensions Mismatch");
        }
        Fraction fAns;
        for(int i = 0; i < row; i++) {
            fAns = fAns + arr[i][i];
        }
        // fAns.simplestForm();
        return fAns;
    } catch(char* e){
        cout << e;
        exit(2);
    }
}
Fraction Matrix::determinant() {
    Matrix mAns = characteristicPolynomial();
     if (row & 1) {
       return mAns.arr[0][0] * (-1);
    }
    return mAns.arr[0][0];
}
Fraction Matrix::positionRowMajor(int x) {
    return arr[x/col][x%col];
}
Fraction Matrix::positionColMajor(int x) {
    return arr[x%row][x/row];
}
Matrix Matrix::power(int k) {
    Matrix m = *this;
    Matrix mAns(row, col, 1);
    while (k > 0) {
      if (k & 1) {
        mAns = mAns * m;
      }
      m = m * m;
      k >>= 1;
    }
    return mAns;
}
Matrix Matrix::reshape(int r, int c) {
    int x = 0, y = 0;
    Matrix mAns(r, c);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        mAns.arr[i][j] = arr[x][y];
        y++;
        if (y == col) {
          y = 0;
          x++;
        }
      }
    }
    return mAns;
}
Matrix Matrix::transpose() {
    Matrix mAns(col, row);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mAns.arr[j][i] = arr[i][j];
        }
    }
    return mAns;
}
Matrix Matrix::concatenate(Matrix& other, int axis) {
    try{
        if (axis == 0) { 
            // Concatenate along rows
            if(col!=other.col){
                throw("Dimension Mismatch");
            }
            Matrix result(row + other.row, col);
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < col; ++j) {
                    result.arr[i][j] = arr[i][j];
                }
            }
            for (int i = 0; i < other.row; ++i) {
                for (int j = 0; j < col; ++j) {
                    result.arr[row + i][j] = other.arr[i][j];
                }
            }
            return result;
        } else if (axis == 1) { 
            // Concatenate along columns
            if(row!=other.row){
                throw("Dimension Mismatch");
            }
            Matrix result(row, col + other.col);
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < col; ++j) {
                    result.arr[i][j] = arr[i][j];
                }
            }
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < other.col; ++j) {
                    result.arr[i][col + j] = other.arr[i][j];
                }
            }
            return result;
        } else {
            throw("Wrong Axis value. Only 0 or 1 allowed");
            return Matrix(0, 0);
        }
    } catch(char* e){
        cout << e;
        exit(2);
    }
}
Matrix Matrix::characteristicPolynomial() {
    int n = row;
    Matrix mAns(n + 1, 1, 0);
    Matrix a(*this);
    Matrix b(*this);
    mAns.arr[n][0] = 1;
    for(int i = n - 1; i >= 0; i--) {
        if (i < n - 1) {
            Matrix m(n, n, 1);
            Fraction temp = mAns.arr[i + 1][0];
            Matrix temp1 = m * temp;
            Matrix temp2 = b + temp1;
            Matrix temp3 = a * temp2;
            b = temp3;
        }
        Fraction temp1 = b.trace();
        Fraction temp2 = temp1*(-1);
        int j = n - i;
        Fraction temp3 = temp2 / j;
        mAns.arr[i][0] = temp3;
    }
    return mAns;
}
Matrix Matrix::operator *(int num) {
    Matrix mAns(row, col);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mAns.arr[i][j] = arr[i][j] * num; 
        }
    }
    return mAns;
}
Matrix Matrix::operator *(Fraction num) {
    Matrix mAns(row, col);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mAns.arr[i][j] = arr[i][j] * num; 
        }
    }
    return mAns;
}
Matrix Matrix::operator +(Matrix &m) {
    Matrix mAns(row, col);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mAns.arr[i][j] = arr[i][j] + m.arr[i][j]; 
        }
    }
    return mAns;
}
Matrix Matrix::operator -(Matrix &m) {
    Matrix mAns(row, col);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mAns.arr[i][j] = arr[i][j] - m.arr[i][j]; 
        }
    }
    return mAns;
}
Matrix Matrix::operator *(Matrix &m) {
    Matrix mAns(row, m.col);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < m.col; j++) {
            for(int k = 0; k < col; k++) {
                Fraction temp1 = arr[i][k] * m.arr[k][j];
                Fraction temp2 = mAns.arr[i][j] + temp1;
                mAns.arr[i][j] = temp2;
            }
        }
    }
    return mAns;
}
Matrix& Matrix::operator=(const Matrix &m) {
    if (this != &m) {
        for (int i = 0; i < row; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        row = m.row;
        col = m.col;
        arr = new Fraction*[row];
        for (int i = 0; i < row; i++) {
            arr[i] = new Fraction[col];
            for (int j = 0; j < col; j++) {
                arr[i][j] = m.arr[i][j];
            }
        }
    }
    return *this;
}

Matrix readCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "'." << endl;
        exit(EXIT_FAILURE);
    }
    int rows = 0;
    int cols = 0;
    string firstLine;
    if (getline(file, firstLine)) {
        stringstream firstLineStream(firstLine);
        string cell;
        while (getline(firstLineStream, cell, ',')) {
            ++cols;
        }
        ++rows;
    } else {
        cerr << "Error: Empty CSV file." << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(file, line)) {
        ++rows;
    }
    file.clear();
    file.seekg(0, ios::beg);
    Matrix result(rows, cols);
    int row = 0;
    while (getline(file, line) && row < rows) {
        stringstream ss(line);
        string cell;
        int col = 0;
        while (getline(ss, cell, ',')) {
            size_t pos = cell.find('/');
            if (pos != string::npos) {
                int numerator = stoi(cell.substr(0, pos));
                int denominator = stoi(cell.substr(pos + 1));
                result.setElement(row, col, Fraction(numerator, denominator));
            } else {
                result.setElement(row, col, Fraction(stoi(cell)));
            }
            ++col;
        }
        ++row;
    }
    file.close();
    return result;
}
int writeMatrixToCSV(Matrix matrix, ofstream& outputFile) {
    for (int i = 0; i < matrix.getR(); ++i) {
        outputFile << ", ";
        for (int j = 0; j < matrix.getC(); ++j) {
            if(matrix.getElement(i, j).getD() == 1) {
                outputFile << matrix.getElement(i, j).getN();
                outputFile << ", ";
            } else {
                outputFile << matrix.getElement(i, j).getN() << "/" << matrix.getElement(i, j).getD();
                outputFile << ", ";

            }
        }
        outputFile << endl;
    }
    return 0;
}
int writeCSV(Matrix matrix) {
    ofstream outputFile("results.csv");
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file 'results.csv'." << endl;
        return 1;
    }
    if(matrix.getR() == matrix.getC()) {
        Fraction trace = matrix.trace();
        outputFile << "Results, " << endl;
        if(trace.getD() == 1) {
            outputFile << "Trace," << trace.getN() << endl;
        } else {
            outputFile << "Trace," << trace.getN() << "/" << trace.getD() << endl;
        }
        Fraction determinant = matrix.determinant();
        if(determinant.getD() == 1) {
            outputFile << "Determinant," << determinant.getN() << endl;
        } else {
        outputFile << "Determinant," << determinant.getN() << "/" << determinant.getD() << endl;
        }
    }
    Matrix transposeMatrix = matrix.transpose();
    outputFile << "Transpose, " << endl;
    writeMatrixToCSV(transposeMatrix, outputFile);
    if(matrix.getR() == matrix.getC()) {
        Matrix characteristicEquation = matrix.characteristicPolynomial();
        outputFile << "Characteristic Equation, " << endl;
        writeMatrixToCSV(characteristicEquation, outputFile);
    }
    outputFile.close();
    cout << "Results written to 'results.csv'." << endl;
    return 0;
}