#include <iostream>
#include "matrix.hpp"


Matrix::Matrix(){
    collumn_ = 0;
    line_ = 0;
    matrix_ = nullptr;
}


Matrix::Matrix(Matrix& other) {
  matrix_ = std::move(other.matrix_);
  line_ = std::move(other.line_);
  collumn_ = std::move(other.collumn_);
  other.matrix_ = nullptr;
  other.line_ = 0;
  other.collumn_ = 0;
}


Matrix::Matrix(const Matrix& other) {
  matrix_ = allocate_matrix(std::move(other.line_), std::move(other.collumn_));
  line_ = std::move(other.line_);
  collumn_ = std::move(other.collumn_);
  
  for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
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
    
    collumn_ = std::move(collumn);
    line_ = std::move(line);
    matrix_ = allocate_matrix(std::move(line), std::move(collumn));
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
    delete old_matrix;
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
    delete old_matrix;
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
    
    double** new_matrix = allocate_matrix(line_, other.collumn_);
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < other.collumn_; j++){
            for(int k = 0; k < collumn_; k++){
                new_matrix[i][j] = matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    collumn_ = other.collumn_;
    matrix_ = new_matrix;
    delete new_matrix;
}

Matrix Matrix::Transpose(){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
        
    Matrix new_matrix(collumn_, line_);
    
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            new_matrix.set_element(j, i, matrix_[i][j]);
        }
    }
    return new_matrix;
}

void Matrix::Output(){
    if(matrix_ == nullptr)
        throw std::invalid_argument("матрица не создана!");
    
    for(size_t i = 0; i < line_; i++){
        for(size_t j = 0; j < collumn_; j++){
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << "\n";
    }
}


double Matrix::Determinant() {
    if (line_ != collumn_)
        throw std::invalid_argument("Матрица не квадратная, определитель вычислить невозможно!");
    return determinantRecursive(*this);
}


double Matrix::determinantRecursive(Matrix& m) {
    if (m.matrix_ == nullptr) throw std::invalid_argument("Матрица не создана!");
    if (m.line_ != m.collumn_) throw std::invalid_argument("Матрица должна быть квадратной!");
    if (m.line_ <= 1) return m.matrix_[0][0];
    if (m.line_ == 2) return m.matrix_[0][0] * m.matrix_[1][1] - m.matrix_[0][1] * m.matrix_[1][0];
    
    Matrix little(m.line_ - 1, m.line_ - 1);
    double sum = 0.0;
    
    for (int column = 0; column < m.line_; column++) {
        getLittleMatrix(m, little, 0, column);
        sum += m.matrix_[0][column] * sign(0, column) * determinantRecursive(little);
    }
    return sum;
}


void Matrix::getLittleMatrix(const Matrix& big,
    Matrix& little,
    int rowToExclude,
    int columnToExclude){

    int rowLittle = 0;
    for(size_t rowBig = 0; rowBig < big.line_; rowBig++){
        if (rowBig == rowToExclude) continue;

        int columnLittle = 0;
        for(size_t columnBig = 0; columnBig < big.collumn_; columnBig++){
            if(columnBig == columnToExclude) continue;
    
            little.matrix_[rowLittle][columnLittle] = big.matrix_[rowBig][columnBig];
            columnLittle++;
        }
        rowLittle++;
    }
}


double Matrix::sign(int line, int collumn){
    if ((line + collumn) % 2 != 0) {
        return -1.0;
    } else {
        return 1.0;
    }
}



Matrix Matrix::CalcComplements() {
    if (line_ != collumn_)
        throw std::range_error("Матрица не квадратная для вычисления алгебраических дополнений!");

    Matrix result(line_, line_);
    Matrix little(line_ - 1, line_ - 1);
  
    for(size_t line = 0; line < line_; line++){
        for(size_t collumn = 0; collumn < collumn_; collumn++){
            getLittleMatrix(*this, little, line, collumn);
            result.matrix_[line][collumn] = sign(line, collumn) * little.Determinant();
        }
    }
    return result;
}


static bool are_equal(double a, double b, double epsilon = 1e-6) {
   if (a > b) {
    return (a - b < epsilon);
} else {
    return (b - a < epsilon);
}
}


Matrix Matrix::InverseMatrix() {
    if (line_ != collumn_)
        throw std::range_error("Матрица не квадратная для расчета обратной матрицы!");

    const double determinant = Determinant();

    if (are_equal(determinant, 0.0, 1e-12))
        throw std::invalid_argument(
            "Определитель равен нулю, обратную матрицу вычислить невозможно!");

    Matrix result = CalcComplements();
    Matrix res = result.Transpose();
    res.Mul_number(1.0 / determinant);
    return res;
}


Matrix::~Matrix() {
    delete matrix_;
}
