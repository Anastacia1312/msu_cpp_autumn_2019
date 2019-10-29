#include "matrix.h"

int main(int argc, char const *argv[]) 
{
    try
    {
        if (argc < 2) 
            throw std::invalid_argument("No argument!");
        
        const size_t rows = 5;
        const size_t cols = 3;
        Matrix m(rows, cols);
        assert(m.getRows() == 5);
        assert(m.getColumns() == 3);
        for (int i=0; i<rows; i++)
            for (int j=0; j<cols; j++)
                m[i][j] = 1;
        
        Matrix m1(rows, cols);
        for (int i=0; i<rows; i++)
            for (int j=0; j<cols; j++)
                m1[i][j] = 1;
        
        assert (m1 == m);
        
        m1*=3;
        
        assert (m1 != m);
        
        switch (argv[1][0])
        {
            case 'e': //element
                if (argc < 4)
                    throw std::invalid_argument("More arguments expected (rows, colomns)!");
                else 
                    std::cout << m[atoi(argv[2])][atoi(argv[3])] << std::endl;
                break;
            case 'c': //columns
                std::cout << m.getColumns() << std::endl;
                break;
            case 'r': //rows
                std::cout << m.getRows() << std::endl;
                break;
            case 'm': //multiplication
                if (argc < 3)
                    throw std::invalid_argument("More arguments expected (multiplier)!");
                else
                    std::cout << (m*=atoi(argv[2]))[0][0] << std::endl;
                break;
            case '=': //comparison ==
                std::cout << (m == m1) << std::endl;
                break;
            case '!': //comparison !=
                std::cout << (m != m1) << std::endl;
                break;
            default:
                throw std::invalid_argument("Wrong command!");
        }
        return 0;
    }

    catch (std::exception&exception) 
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }
    
}