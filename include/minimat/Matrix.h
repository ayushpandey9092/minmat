#pragma once
#include <ostream>
namespace minimat {

class Matrix{
    private:
        int m_rows;
        int m_cols;
        double * m_data;
        static int count; // Static member to keep track of the number of Matrix instances
    public:
        Matrix(int rows, int cols);

        // Copying is disabled for now. Phase 2 implements it properly.
        Matrix(const Matrix&) = delete;
        Matrix& operator=(const Matrix&) = delete;
        // Other member functions and data members can be added here

        int rows() const;
        int cols() const;
        double& at(int row, int col);
        const double& at(int row, int col) const;
        static int liveCount();
        void print(std::ostream& os) const;
        void fill(double value);

        ~Matrix();
};

bool sameShape(const Matrix& a, const Matrix& b);
void add(const Matrix& a, const Matrix& b, Matrix& out);
void multiply(const Matrix& a, const Matrix& b, Matrix& out);

}