#include <gtest/gtest.h>

#include "../stream.h"

TEST(MakeStream, Iterators) {

    std::vector<int> v = {1, 2, 3};
    auto s = MakeStream(v.begin(), v.end());
    ASSERT_EQ(v, s.to_vector());
}

TEST(MakeStream, Container_Lvalue) {

    const std::vector<int> v = {1, 2, 3};
    auto s = MakeStream(v);
    ASSERT_EQ(v, s.to_vector());
}

TEST(MakeStream, Container_Rvalue) {

    auto s = MakeStream(std::vector<int> {1, 2, 3});
    ASSERT_EQ((std::vector<int> {1, 2, 3}), s.to_vector());
}

TEST(MakeStream, InitializerList) {

    auto s = MakeStream({1, 2, 3});
    ASSERT_EQ((std::vector<int> {1, 2, 3}), s.to_vector());
}

TEST(MakeStream, Generator) {

    auto g = makeGenerator(1, [] (int x) {return ++x;}, [] (int x) {return (x < 4);});
    auto s = MakeStream(g);
    ASSERT_EQ((std::vector<int> {1, 2, 3}), s.to_vector());
}

TEST(MakeStream, Values) {

    auto s = MakeStream(1, 2, 3);
    ASSERT_EQ((std::vector<int> {1, 2, 3}), s.to_vector());
}

TEST(Operators, map) {

    auto s = MakeStream(1, 2, 3) | map([] (auto i) {return i * i;});
    ASSERT_EQ((std::vector<int> {1, 4, 9}), s.to_vector());
}

TEST(Pipe, Rvalue_Rvalue) {

    ASSERT_EQ((std::vector<int> {1, 4, 9}),
              (MakeStream(1, 2, 3) | map([] (int i) {return i * i;})).to_vector());
}

TEST(Pipe, Rvalue_Lvalue) {

    auto m = map([] (int i) {return i * i;});
    ASSERT_EQ((std::vector<int> {1, 4, 9}),
              (MakeStream(1, 2, 3) | m).to_vector());
}

TEST(Pipe, Lvalue_Rvalue) {

    auto s = MakeStream(1, 2, 3);
    ASSERT_EQ((std::vector<int> {1, 4, 9}),
              (s | map([] (int i) {return i * i;})).to_vector());
}

TEST(Pipe, Lvalue_Lvalue) {

    auto s = MakeStream(1, 2, 3);
    auto m = map([] (int i) {return i * i;});

    ASSERT_EQ((std::vector<int> {1, 4, 9}),
              (s | m).to_vector());
}

TEST(Compose, compose) {

    auto comp = map([] (int i) {return i + 1;}) | map([] (int i) {return i * i;});
    auto s = MakeStream(1, 2, 3) | comp;
    ASSERT_EQ((std::vector<int> {4, 9, 16}), s.to_vector());
}

TEST(Operators, reduce) {

    auto id = [] (auto x) {return x;};
    auto sum = [] (auto x, auto y) {return (x + y);};

    auto r = MakeStream(1, 2, 3) | reduce(id, sum);
    ASSERT_EQ(6, r);

    r = MakeStream(1, 2, 3) | reduce(sum);
    ASSERT_EQ(6, r);
}

TEST(Operators, sum) {

    auto r = MakeStream(1, 2, 3) | sum();
    ASSERT_EQ(6, r);
}

TEST(Operators, filter) {

    auto s = MakeStream(1, 2, 3, 4, 5, 6, 7) | filter([] (int i) {return ((i % 2) == 1);});
    ASSERT_EQ((std::vector<int> {1, 3, 5, 7}), s.to_vector());
}

TEST(Operators, skip) {

    auto s = MakeStream(1, 2, 3, 4, 5, 6, 7) | skip(4);
    ASSERT_EQ((std::vector<int> {5, 6, 7}), s.to_vector());
}

TEST(Operators, group) {

    auto s = MakeStream(1, 2, 3, 4, 5, 6, 7) | group(2);

    ASSERT_EQ((std::vector<std::vector<int>> {
                   std::vector<int> {1, 2},
                   std::vector<int> {3, 4},
                   std::vector<int> {5, 6}}),
              s.to_vector());
}

TEST(Operators, to_vector) {

    auto v = MakeStream(1, 2, 3) | to_vector();
    ASSERT_EQ((std::vector<int> {1, 2, 3}), v);
}

TEST(Operators, nth) {

    ASSERT_EQ(1, MakeStream(1, 2, 3) | nth(0));
    ASSERT_EQ(2, MakeStream(1, 2, 3) | nth(1));
    ASSERT_EQ(3, MakeStream(1, 2, 3) | nth(2));
}

int main(int argc, char* argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
