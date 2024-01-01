#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// class prototyping
class Fraction;
class Matrix;

class Fraction {
    private:
        pair<int, int> frac;
        friend class Matrix;
    public:
    // Constructors
        Fraction() {
            frac.first = 0;
            frac.second = 1;
        }
        Fraction(int numerator, int denominator = 1) {
            try {
                if(denominator==0){
                    throw("Denominator cannot be 0"); 
                }
                frac.first = numerator;
                frac.second = denominator;
                simplestForm();
            } catch(const char* e) {
                cout << e;
                exit(1);
            }
            
        }
    // Setter Functions
        int setN(int num) {
            frac.first = num;
            simplestForm();
            return frac.first;
        }
        int setD(int den) {
            try {
                if(den == 0) {
                    throw("Denominator cannot be 0");
                    frac.second = den;
                    simplestForm();
                    return frac.second;
                }
            } catch(const char* e) {
                cout << e;
                exit(1);
            }
            return 0;
        }
        pair<int, int> setF(int n1, int n2) {
            try{
                if(n2==0) {
                    throw("Denominator cannot be 0");
                }
                frac.first = n1;
                frac.second = n2;
                simplestForm();
                return frac;
            } catch(const char* e){
                cout << e;
                exit(1);
            }
        }
    // Getter Functions
        int getN() {
            return frac.first;
        }
        int getD() {
            return frac.second;
        }
        pair<int, int> getF() {
            return frac;
        }
    // Utility Function
        int gcd(int a, int b) {
            if(b == 0) {
                return a;
            }
            return gcd(b, a%b);
        }
        int simplestForm() {
            int div = gcd(abs(frac.first), abs(frac.second));
            frac.first = frac.first/div;
            frac.second = frac.second/div;
            return div;
        }
    // Display Function
        int display() {
            cout << frac.first << "/" << frac.second << " ";
            return 0;
        }
    // Operations
        Fraction inverse() {
            Fraction f;
            f.frac.first = frac.second;
            f.frac.second = frac.first;
            f.simplestForm();
            return f;
        }
    // Whole Number Handling
        // type conversion (non-primitive to primitive)
        operator int() {
            return frac.second == 1 ? frac.first : frac.first/frac.second;
        }
    // Operator Overloading
        Fraction operator +(int);
        Fraction operator -(int);
        Fraction operator *(int);
        Fraction operator /(int);
        friend Fraction operator -(Fraction&);
        friend Fraction operator +(Fraction&, Fraction&);
        friend Fraction operator -(Fraction&, Fraction&);
        friend Fraction operator *(Fraction&, Fraction&);
        friend Fraction operator /(Fraction&, Fraction&);
        friend void operator >> (istream & cin, Fraction& f) {
            int num = 0;
            int den = 1;
            cin >> num;
            cin >> den;
            try {
                if(den==0){
                    throw("Denominator cannot be 0");
                }
                f.frac.first = num;
                f.frac.second = den;
                f.simplestForm();
            } catch(const char* e) {
                cout << e;
                exit(1);
            }
        }
        friend void operator << (ostream & cout, Fraction& f) {
            cout << f.frac.first << "/" << f.frac.second << " ";
        }
};

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

Fraction Fraction::operator +(int num) {
    Fraction f;
    f.frac.first = frac.first + frac.second*num;
    f.frac.second = frac.second;
    f.simplestForm();
    return f;
}
Fraction Fraction::operator -(int num) {
    Fraction f;
    f.frac.first = frac.first - frac.second*num;
    f.frac.second = frac.second;
    f.simplestForm();
    return f;
}
Fraction Fraction::operator *(int num) {
    Fraction f;
    f.frac.first = frac.first*num;
    f.frac.second = frac.second;
    f.simplestForm();
    return f;
}
Fraction Fraction::operator /(int num) {
    Fraction f;
    f.frac.first = frac.first;
    f.frac.second = frac.second*num;
    f.simplestForm();
    return f;
}
Fraction operator -(Fraction& f) {
    Fraction fAns;
    fAns.frac.first = -f.frac.first;
    fAns.frac.second = f.frac.second;
    return f;
}
Fraction operator +(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = (f1.frac.first * f2.frac.second) + (f2.frac.first * f1.frac.second);
    f3.frac.second = f1.frac.second * f2.frac.second;
    f3.simplestForm();
    return f3;
}
Fraction operator -(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = (f1.frac.first * f2.frac.second) - (f2.frac.first * f1.frac.second);
    f3.frac.second = f1.frac.second * f2.frac.second;
    f3.simplestForm();
    return f3;
}
Fraction operator *(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = f1.frac.first * f2.frac.first;
    f3.frac.second = f1.frac.second * f2.frac.second;
    f3.simplestForm();
    return f3;
}
Fraction operator /(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = f1.frac.first * f2.frac.second;
    f3.frac.second = f1.frac.second * f2.frac.first;
    f3.simplestForm();
    return f3;
}
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

int menuDriven() {
    std::cout << "MATRIX LIBRARY" << std::endl;
    std::cout << "A collaborative project by Himanshu Dania and Kanav Goyal" << std::endl;
    
    char ch1;
    std::cout << "Create/Import matrix [C/I]: ";
    std::cin >> ch1;
    if(ch1 == 'C' || ch1 == 'c') {
        char ch2;
        std::cout << "Unary/Binary matrix Operations [U/B]: ";
        std::cin >> ch2;
        if(ch2 == 'B' || ch2 == 'b') {
            int row1, col1;
            std::cout << "Enter matrix1 dimensions: ";
            std::cin >> row1;
            std::cin >> col1;
            Fraction *arr1;
            arr1 = new Fraction[row1*col1];
            std::cout << "Enter matrix1 elements: ";
            for(int i = 0; i < row1*col1; i++) {
                int fr;
                cin >> fr;
                arr1[i] = fr;
            }
            Matrix m1(row1, col1, arr1, row1*col1);
            cout << m1;
            
            int row2, col2;
            std::cout << "Enter matrix2 dimensions: ";
            std::cin >> row2;
            std::cin >> col2;
            Fraction *arr2;
            arr2 = new Fraction[row2*col2];
            std::cout << "Enter matrix2 elements: ";
            for(int i = 0; i < row2*col2; i++) {
                int fr;
                cin >> fr;
                arr2[i] = fr;
            }
            Matrix m2(row2, col2, arr2, row2*col2);
            cout << m2;
            bool isWritten = false;
            ofstream outputFile("results.csv");
            if (!outputFile.is_open()) {
                cerr << "Error: Unable to open file 'results.csv'." << endl;
                return 1;
            }
            if(m1.getR() == m2.getR() && m1.getC() == m2.getC()) {
                Matrix m3 = m1+m2;
                outputFile << "m1+m2, " << endl;
                Matrix m4 = m1-m2;
                writeMatrixToCSV(m3, outputFile);
                outputFile << "m1-m2, " << endl;
                writeMatrixToCSV(m4, outputFile);
                isWritten = true;
            }
            if(m1.getC() == m2.getR()) {
                Matrix m5(m1*m2);
                outputFile << "m1*m2, " << endl;
                writeMatrixToCSV(m5, outputFile);
                isWritten = true;
            }
            if(m1.getC() == m2.getC()) {
                bool ans;
                std::cout << "Perform column-wise concatenation [0/1]: ";
                std::cin >> ans;
                if(ans) {
                    Matrix m6 = m1.concatenate(m2, 0);
                    outputFile << "m1:m2 (row-wise augmented matrix), " << endl;
                    writeMatrixToCSV(m6, outputFile);
                    isWritten = true;
                }
            }
            if(m1.getR() == m2.getR()) {
                bool ans;
                std::cout << "Perform column-wise concatenation [0/1]: ";
                std::cin >> ans;
                if(ans) {
                    Matrix m7 = m1.concatenate(m2, 1);
                    outputFile << "m1:m2 (column-wise augmented matrix), " << endl;
                    writeMatrixToCSV(m7, outputFile);
                    isWritten = true;
                }
            }
            outputFile.close();
            if(isWritten) {
                cout << "Results written to 'results.csv'." << endl;
            }
            delete[] arr1;
            delete[] arr2;
            return 0;
        } else {
            int row, col;
            std::cout << "Enter matrix dimensions: ";
            std::cin >> row;
            std::cin >> col;
            Fraction *arr;
            arr = new Fraction[row*col];
            std::cout << "Enter matrix elements: ";
            for(int i = 0; i < row*col; i++) {
                int x;
                cin >> x;
                arr[i] = x;
            }
            Matrix m(row, col, arr, row*col);
            cout << m;
            delete[] arr;
            ofstream outputFile("results.csv");
            if (!outputFile.is_open()) {
                cerr << "Error: Unable to open file 'results.csv'." << endl;
                return 1;
            }
            int power;
            std::cout << "Enter power: ";
            std::cin >> power;
            Matrix mPower = m.power(power);
            outputFile << "m^(k), " << endl;
            writeMatrixToCSV(mPower, outputFile);
            int newRow, newCol;
            std::cout << "Enter updated matrix dimensions: ";
            std::cin >> newRow;
            std::cin >> newCol;
            Matrix mReshape = m.reshape(newRow, newCol);
            outputFile << "m (updated), " << endl;
            writeMatrixToCSV(mReshape, outputFile);
            outputFile.close();
            cout << "Results written to 'results.csv'." << endl;
        }
    } else {
        string address;
        cout << "Enter file path: ";
        cin >> address;
        Matrix matrix = readCSV(address);
        std::cout << "Dimensions: " << matrix.getR() << " x " << matrix.getC() << endl;
        cout << matrix;
        writeCSV(matrix);
        return 0;
    }
    return 0;
}

int main() {
    return menuDriven();
}