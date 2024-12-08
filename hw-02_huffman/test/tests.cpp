#include "HuffmanTests.hpp"

#include <cassert>
int main() {
    HuffmanArchiver::HuffmanTest::TestAll tester;
    assert(tester.test());
}