#include<minimat/Matrix.h>
#include<iostream>
#include<fstream>
#include<stdexcept>

int main()
{
    std::cout << "Live Matrix Count (before): " << minimat::Matrix::liveCount() << std::endl;

    // FR-1, FR-4, FR-5, FR-9, FR-10: construct, query, access, print, count
    {
        minimat::Matrix mat(3, 4);
        std::cout << "Rows: " << mat.rows() << ", Cols: " << mat.cols() << std::endl;

        mat.at(1, 2) = 5.0;
        std::cout << "Element at (1, 2): " << mat.at(1, 2) << std::endl;

        std::ofstream outputfile("matrix_output.txt");
        mat.print(outputfile);
        outputfile.close();

        std::cout << "Live Matrix Count (inside): " << minimat::Matrix::liveCount() << std::endl;
    }

    std::cout << "Live Matrix Count (after): " << minimat::Matrix::liveCount() << std::endl;

    // FR-6: bounds checking
    {
        minimat::Matrix mat(3, 4);
        try {
            mat.at(5, 0);
        } catch (const std::out_of_range& e) {
            std::cout << "Out of range caught: " << e.what() << std::endl;
        }
    }

    // FR-8: fill
    {
        minimat::Matrix ones(2, 3);
        ones.fill(1.0);
        std::cout << "Filled with ones:" << std::endl;
        ones.print(std::cout);
    }

    // FR-11, FR-12, FR-13: shape check, addition, multiplication
    {
        minimat::Matrix a(2, 3);
        minimat::Matrix b(3, 2);
        minimat::Matrix ones(2, 3);
        ones.fill(1.0);

        // a = [[1,2,3],[4,5,6]]
        a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3;
        a.at(1, 0) = 4; a.at(1, 1) = 5; a.at(1, 2) = 6;

        // b = [[7,8],[9,10],[11,12]]
        b.at(0, 0) = 7;  b.at(0, 1) = 8;
        b.at(1, 0) = 9;  b.at(1, 1) = 10;
        b.at(2, 0) = 11; b.at(2, 1) = 12;

        std::cout << std::boolalpha;
        std::cout << "sameShape(a, b): " << minimat::sameShape(a, b) << std::endl;
        std::cout << "sameShape(a, ones): " << minimat::sameShape(a, ones) << std::endl;

        minimat::Matrix sum(2, 3);
        minimat::add(a, ones, sum);
        std::cout << "a + ones:" << std::endl;
        sum.print(std::cout);

        minimat::Matrix product(2, 2);
        minimat::multiply(a, b, product);
        std::cout << "a * b (expected 58 64 / 139 154):" << std::endl;
        product.print(std::cout);

        // Invalid shapes throw before anything is written
        try {
            minimat::Matrix bad(2, 2);
            minimat::multiply(a, a, bad);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid multiply caught: " << e.what() << std::endl;
        }
    }

    std::cout << "Live Matrix Count (end): " << minimat::Matrix::liveCount() << std::endl;

    return 0;
}
