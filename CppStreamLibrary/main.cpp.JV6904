#include <iostream>
#include <vector>

#include "stream.h"

struct A {
public:
    A() {
        std::cout << "A ctor\n";
    }

    A (const A& other) = delete;

    A (A&& ) {
        std::cout << "A move ctor\n";
    }

    ~A () {
        std::cout << "A d tor\n";
    }
};

int main() {

//    (MakeStream(1, 2, 3) | print_to(std::cout)) << "more text";

    std::vector<A> v;
    v.emplace_back(A());

    auto s = MakeStream(std::move(v)) | map([] (auto x) {return x;});
    s | nth(0);

    std::cout << std::endl << "hello" << std::endl;
}

