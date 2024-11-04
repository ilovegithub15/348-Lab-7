#include <iostream>
#include <fstream>
#include <vector>

class Matrix {
public:
    Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows, std::vector<int>(cols)) {}

    Matrix operator+(const Matrix& other) {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[i][j] = this->data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) {
        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                result.data_[i][j] = 0;
                for (int k = 0; k < cols_; ++k) {
                    result.data_[i][j] += this->data_[i][k] * other.data_[k][j];
                }
            }
        }
        return result;
    }

    void displayDiagonalSums() const {
        int mainDiagonalSum = 0;
        int secondaryDiagonalSum = 0;
        for (int i = 0; i < rows_; ++i) {
            mainDiagonalSum += data_[i][i];
            secondaryDiagonalSum += data_[i][cols_ - 1 - i];
        }
        std::cout << "Main diagonal sum: " << mainDiagonalSum << std::endl;
        std::cout << "Secondary diagonal sum: " << secondaryDiagonalSum << std::endl;
    }
    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= rows_ || row2 < 0 || row2 >= rows_) {
            std::cerr << "Invalid row indices!" << std::endl;
            return;
        }
        std::swap(data_[row1], data_[row2]);
    }

    void display() const {
        for (const auto& row : data_) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    void load(std::istream& input) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                input >> data_[i][j];
            }
        }
    }

private:
    int rows_;
    int cols_;
    std::vector<std::vector<int> > data_;
};

int main() {
    std::ifstream file("input.txt");
    Matrix matrix1(4, 4);
    Matrix matrix2(4, 4);
    matrix1.load(file);
    matrix2.load(file);
    std::cout << "Matrix 1:" << std::endl;
    matrix1.display();
    std::cout << "Matrix 2:" << std::endl;
    matrix2.display();
    Matrix sum = matrix1 + matrix2;
    std::cout << "Sum of Matrices:" << std::endl;
    sum.display();
    Matrix product = matrix1 * matrix2;
    std::cout << "Product of Matrices:" << std::endl;
    product.display();
    std::cout << "Diagonal Sums:" << std::endl;
    sum.displayDiagonalSums();
    int row1, row2;
    std::cout << "Enter two row indices to swap (0 to 3): ";
    std::cin >> row1 >> row2;
    sum.swapRows(row1, row2);
    std::cout << "Matrix after swapping rows " << row1 << " and " << row2 << ":" << std::endl;
    sum.display();
}