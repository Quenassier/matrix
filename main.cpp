#include "matrix.hpp"
#include <iostream>

Matrix::Matrix(){
    collumn_ = 0;
    line_ = 0;
    matrix_ = nullptr;
}

double** Matrix::allocate_matrix(int line, int collumn){
    double** new_matrix = new double*[line];
    for(size_t i = 0; i < line; i++) new_matrix[i] = new double[collumn];
    return new_matrix;
}

void Matrix::fill(){
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            matrix_[i][j] = 0;
        }
    }
}

Matrix::Matrix(int line, int collumn){
    if(line <= 0 || collumn <= 0) throw std::invalid_argument("значения не могут быть <= 0!");
    collumn_ = collumn;
    line_ = line;
    matrix_ = allocate_matrix(line, collumn);
    fill();
}

int Matrix::get_collumn(){
    return collumn_;
}

int Matrix::get_line(){
    return line_;
}

int Matrix::get_element(int line, int collumn){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    else if(line < 0 || line >= line_)
        throw std::invalid_argument("недопустимый аргумент строки! Вы забыли индекс - 1??");
    else if(collumn < 0 || collumn >= collumn_)
        throw std::invalid_argument("недопустимый аргумент столбца! Вы забыли 'индекс - 1'?");
    else
        return matrix_[line][collumn];
}

void Matrix::set_collumn(int collumn){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    else if(collumn <= 0) 
        throw std::invalid_argument("значение не может быть <= 0!");
    double** old_matrix = matrix_;
    matrix_ = allocate_matrix(line_, collumn);
    fill();
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn; j++){
            matrix_[i][j] = old_matrix[i][j];
        }
    }
}

void Matrix::set_line(int line){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    else if(line <= 0) 
        throw std::invalid_argument("значение не может быть <= 0!");
    double** old_matrix = matrix_;
    matrix_ = allocate_matrix(line, collumn_);
    fill();
    for(size_t i = 0; i < line; i++){
        for(size_t j = 0; j < collumn_; j++){
            matrix_[i][j] = old_matrix[i][j];
        }
    }
}

void Matrix::set_element(int line, int collumn, double new_value){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    else if(line < 0 || line >= line_)
        throw std::invalid_argument("недопустимый аргумент строки! Вы забыли 'индекс - 1'?");
    else if(collumn < 0 || collumn >= collumn_)
        throw std::invalid_argument("недопустимый аргумент столбца! Вы забыли 'индекс - 1'?");
    else
        matrix_[line][collumn] = new_value;
}

bool Matrix::Eq_matrix(const Matrix &other){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    else if(other.matrix_ == nullptr)
        throw std::invalid_argument("матрица из аргумента не создана!");
    if(line_ != other.line_ || collumn_ != other.collumn_)
        return false;
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            if(other.matrix_[i][j] != matrix_[i][j]){
                return false;
            }
        }
    }
    return true;
}

void Matrix::Sum_matrix(const Matrix &other){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    else if(other.matrix_ == nullptr)
        throw std::invalid_argument("матрица из аргумента не создана!");
    else if(other.collumn_ != collumn_)
        throw std::invalid_argument("количество столбцов матрицы НЕ РАВНО количеству столбцов другой матрицы!");
    else if(other.line_ != line_)
        throw std::invalid_argument("количество строк матрицы НЕ РАВНО количеству строк другой матрицы!");
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void Matrix::Sub_matrix(const Matrix &other){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    else if(other.matrix_ == nullptr)
        throw std::invalid_argument("матрица из аргумента не создана!");
    else if(other.collumn_ != collumn_)
        throw std::invalid_argument("количество столбцов матрицы НЕ РАВНО количеству столбцов другой матрицы!");
    else if(other.line_ != line_)
        throw std::invalid_argument("количество строк матрицы НЕ РАВНО количеству строк другой матрицы!");
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void Matrix::Mul_number(double num){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана");
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            matrix_[i][j] *= num;
        }
    }
}

void Matrix::Mul_matrix(const Matrix &other){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана");
    else if(other.matrix_ == nullptr)
        throw std::invalid_argument("матрица из аргумента не создана!");
    else if(line_ != other.collumn_)
        throw std::invalid_argument("количество строк матрицы НЕ РАВНО количеству столбцов другой матрицы!");
    else if(collumn_ != other.line_)
        throw std::invalid_argument("количество столбцов матрицы НЕ РАВНО количеству строк другой матрицы!");
    Matrix new_matrix = Matrix(line_, other.collumn_);
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < other.collumn_; j++){
            for(int k = 0; k < collumn_; k++){
                new_matrix.matrix_[i][j] = matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
}

Matrix Matrix::Transpose(){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    Matrix new_matrix = Matrix(collumn_, line_);
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            new_matrix.set_element(j, i, matrix_[i][j]);
        }
    }
    return new_matrix;
}

int main() {
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);

    matrix1.set_element(0, 0, 1);
    matrix1.set_element(0, 1, 2);
    matrix1.set_element(0, 2, 2);

    matrix2.set_element(0, 0, 1);
    matrix2.set_element(2, 1, 1);
    matrix2.set_element(0, 2, 2);
 
     std::cout << "Matrix 1:" << std::endl;
    for (int i = 0; i < matrix1.get_line(); ++i) {
        for (int j = 0; j < matrix1.get_collumn(); ++j) {
            std::cout << matrix1.get_element(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Matrix 2:" << std::endl;
for (int i = 0; i < matrix2.get_line(); ++i) {
    for (int j = 0; j < matrix2.get_collumn(); ++j) {
        std::cout << matrix2.get_element(i, j) << " ";
    }
    std::cout << std::endl;
}
 
    matrix1.Sum_matrix(matrix2);
    matrix2.Sub_matrix(matrix1);
    matrix1.Mul_number(2);

    return 0;
}
