#include <iostream>

int add(int a, int b);

int main() 
{
    std::cout << add(5, 6);
    std::cout << '\n';
    std::cout << add(65536, 655536);
}

int add(int a, int b)
{
    return a + b;
}
