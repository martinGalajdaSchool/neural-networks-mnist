// Created by Martin Galajda on 20/10/2018.
//

#include <iostream>

#ifndef PV021_MATRIX_IMPL_MatrixV4_H
#define PV021_MATRIX_IMPL_MatrixV4_H

template <typename T>
class MatrixV4 {
public:
    class RowVector {
    public:
        RowVector(T *rowData);
        ~RowVector();

        T& operator[](const int& index);

    private:
        T *rowData;
    };

    MatrixV4(int rows, int cols);
    MatrixV4(T* array, int rows, int cols);
    ~MatrixV4();

    MatrixV4::RowVector& operator[](const int& index);
    MatrixV4* operator*(MatrixV4&);

    int getNumOfRows();
    int getNumOfCols();
    void printValues();
    std::string &toString();


protected:
    RowVector** rows;
    T *rawData;

    int numOfRows;
    int numOfCols;
};



/*********** CONSTRUCTORS ********************************************************/

template <typename T>
MatrixV4<T>::MatrixV4(int rows, int cols) {
    this->numOfRows = rows;
    this->numOfCols = cols;
    this->rows = (RowVector**) malloc(sizeof(RowVector*) * rows);

    this->rawData = (T*) malloc(sizeof(T) * rows * cols);
    for (auto i = 0; i < rows; i++) {
        RowVector *row = new MatrixV4::RowVector(rawData + (cols * i));
        this->rows[i] = row;
    }
}

template <typename T>
MatrixV4<T>::MatrixV4(T *data, int rows, int cols): MatrixV4(rows, cols) {
    this->numOfRows = rows;
    this->numOfCols = cols;

    for (auto i = 0; i < numOfRows; i++) {
        for (auto j = 0; j < numOfCols; j++) {
            T arrayValue = *(data + (i * numOfCols) + j);
            RowVector& row = *(*(this->rows + i));

            T& value = row[j];
            value = arrayValue;
        }
    }
}

template <typename T>
MatrixV4<T>::RowVector::RowVector(T *rowData) {
    this->rowData = rowData;
}

/*********** DESTRUCTORS ********************************************************/

template <typename T>
MatrixV4<T>::~MatrixV4() {
    for (auto i = 0; i < numOfRows; i++) {
        RowVector* vectorPtr = *(this->rows + i);

        free(vectorPtr);
    }
    free(rows);
    free(rawData);
}

/*********** OPERATORS ********************************************************/

template <typename T>
T& MatrixV4<T>::RowVector::operator[](const int& index) {
    T& elementRef = *(this->rowData + index);
    return elementRef;
}


template <typename T>
typename MatrixV4<T>::RowVector &MatrixV4<T>::operator[](const int& index) {
    return *(*(this->rows + index));
}

template <typename T>
MatrixV4<T>* MatrixV4<T>::operator*(MatrixV4& other) {
    if (this->getNumOfCols() != other.getNumOfRows()) {
        throw std::invalid_argument("Matrices with incompatible dimension passed for multiplication.");
    }

    auto thisNumOfRows = this->getNumOfRows();
    auto thisNumOfCols = this->getNumOfCols();
    auto otherNumOfCols = other.getNumOfCols();

    auto resultMatrix = new MatrixV4(thisNumOfRows, otherNumOfCols);

    // A = (m,n)
    // B = (n,j)
    // C = A * B
    // C = (m,j)
    //
    //      A        *      B        =                                  C
    // |a11 ... a1n| * |b11 ... b1j| = | a11 * b11 + ... + a1n * bn1 | ... | a11 * b1j + ... + a1n * bnj |
    // [... ... ...|   [... ... ...|   |             ...             | ... |             ...             |
    // |am1 ... amn|   |bn1 ... bnj|   | am1 * b11 + ... + amn * bn1 | ... | am1 * b1j + ... + amn * bnj |

    // Iterate over every row from Matrix A
    for (auto resultRow = 0; resultRow < thisNumOfRows; resultRow++) {
        // Iterate over every column from Matrix B
        for (auto resultCol = 0; resultCol < otherNumOfCols; resultCol++) {
            T result = 0;
            // Perform sum of the dot product between two matching vectors from A and B
            for (auto sumIndex = 0; sumIndex < thisNumOfCols; sumIndex++) {
                // From A we take a row vector and from B we take a column vector
                result += (*this)[resultRow][sumIndex] * other[sumIndex][resultCol];
            }

            (*resultMatrix)[resultRow][resultCol] = result;
        }
    }

    return resultMatrix;
}

/*********** METHODS ********************************************************/

template <typename T>
void MatrixV4<T>::printValues() {
    for (auto i = 0; i < numOfRows; i++) {
        for (auto j = 0; j < numOfCols; j++) {
            std::cout << this->operator[](i)[j] << " ";
        }
        std::cout << std::endl;
    }
}


template <typename T>
int MatrixV4<T>::getNumOfRows() {
    return this->numOfRows;
}

template <typename T>
int MatrixV4<T>::getNumOfCols() {
    return this->numOfCols;
}

template <typename T>
std::string& MatrixV4<T>::toString(){
    std::string result = "";

    for (auto i = 0; i < numOfRows(); i++) {
        for(auto j = 0; j < numOfCols(); j++) {
            result += (*this)[i][j] + " ";
        }
        result += '\n';
    }
    return result;
}


#endif //PV021_MATRIX_IMPL_MatrixV4_H
