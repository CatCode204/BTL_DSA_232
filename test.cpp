#include <iostream>

using namespace std;

int main() {
    int a = 10;
    void* p = &a;
    *(int*)p = 5;
    std::cout << a << std::endl;
}