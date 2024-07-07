#include <iostream>
#include <fstream>
#include <sstream>

#include "fraction.cpp"
#include "matrix.cpp"

using namespace std;

// class prototyping
class Fraction;
class Matrix;

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