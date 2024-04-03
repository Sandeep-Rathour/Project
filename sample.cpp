#include <iostream>
#include <random>

int main(void)
{
    std::random_device rd;
    std::uniform_int_distribution <int> sandeep(-300, -10);

    // std::srand(12);

    for( int i = 0; i < 8; i++)
        std::cout << sandeep(rd) << std::endl;
    
        // std::cout << std::rand() % 6 + 1 << std::endl;

    return false;
}