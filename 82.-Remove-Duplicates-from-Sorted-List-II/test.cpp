// ポインタと参照の違い

#include <iostream>
void func(int& x) {
    x += 10;
    printf("%p\n", &x);
}
int main() {
    int b = 10;
    int& c = b;
    std::cout << c << std::endl;  // 10
    printf("%p\n", &b);
    func(b);  // bは20になる
    std::cout << b << std::endl;
}
