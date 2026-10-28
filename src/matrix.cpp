#include<minimat/Matrix.h>
#include<stdexcept>
#include<ostream>

namespace {
    int index(int row, int col, int cols) {
        return row * cols + col;
    }
}

minimat::Matrix::Matrix(int rows, int cols) {

    m_rows = rows;
    m_cols = cols;
    m_data = new double[rows * cols];
    count++;
}

int minimat::Matrix::rows() const {
    return m_rows;
}

int minimat::Matrix::cols() const {
    return m_cols;
}

double& minimat::Matrix::at(int row, int col) {
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        throw std::out_of_range("Index out of bounds");
    }
    return m_data[index(row, col, m_cols)];
}

const double& minimat::Matrix::at(int row, int col) const {
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        throw std::out_of_range("Index out of bounds");
    }
    return m_data[index(row, col, m_cols)];
}

void minimat::Matrix::print(std::ostream& os) const {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            os << at(i, j) << " ";
        }
        os << std::endl;
    }
}

int minimat::Matrix::count = 0;

int minimat::Matrix::liveCount() {
    return count;
}
void minimat::Matrix::fill(double value) {
    for (int i = 0; i < m_rows * m_cols; ++i) {
        m_data[i] = value;
    }
}

minimat::Matrix::~Matrix() {
    delete[] m_data;
    count--;
}

bool minimat::sameShape(const Matrix& a, const Matrix& b) {
    return a.rows() == b.rows() && a.cols() == b.cols();
}

void minimat::add(const Matrix& a, const Matrix& b, Matrix& out) {
    if (!sameShape(a, b) || !sameShape(a, out)) {
        throw std::invalid_argument("Shape mismatch in add");
    }
    for (int i = 0; i < a.rows(); ++i) {
        for (int j = 0; j < a.cols(); ++j) {
            out.at(i, j) = a.at(i, j) + b.at(i, j);
        }
    }
}

void minimat::multiply(const Matrix& a, const Matrix& b, Matrix& out) {
    if (a.cols() != b.rows()) {
        throw std::invalid_argument("Inner dimensions do not match in multiply");
    }
    if (out.rows() != a.rows() || out.cols() != b.cols()) {
        throw std::invalid_argument("Output has the wrong shape in multiply");
    }
    for (int i = 0; i < a.rows(); ++i) {
        for (int j = 0; j < b.cols(); ++j) {
            double sum = 0.0;
            for (int k = 0; k < a.cols(); ++k) {
                sum += a.at(i, k) * b.at(k, j);
            }
            out.at(i, j) = sum;
        }
    }
}
