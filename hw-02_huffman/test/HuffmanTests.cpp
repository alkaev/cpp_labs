#include "HuffmanTests.hpp"

#include <fstream>
#include <cassert>
#include <iostream>

namespace HuffmanArchiver {
namespace HuffmanTest {

bool NodeTester::test_left() {
    HuffmanTreeNode node;
    int32_t value = 1000;
    for (value = 0; value < 100; ++value) {
        node.set_left(value);
        if (node.get_left() != value) {
            return false;
        }
    }
    return true;
}
bool NodeTester::test_right() {
    HuffmanTreeNode node;
    int32_t value = 1000;
    for (value = 0; value < 100; ++value) {
        node.set_right(value);
        if (node.get_right() != value) {
            return false;
        }
    }
    return true;
}
bool NodeTester::test_head() {
    HuffmanTreeNode node;
    int32_t value = 1000;
    for (value = 0; value < 100; ++value) {
        node.set_head(value);
        if (node.get_head() != value) {
            return false;
        }
    }
    return true;
}

bool NodeTester::test_freq() {
    HuffmanTreeNode node;
    uint64_t value = 1000;
    for (value = 0; value < 100; ++value) {
        node.set_freq(value);
        if (node.get_freq() != value) {
            return false;
        }
    }
    return true;
}

bool NodeTester::test_sym() {
    HuffmanTreeNode node;
    char value = 'f';
    for (value = 0; value < 100; ++value) {
        node.set_sym(value);
        if (node.get_sym() != value) {
            return false;
        }
    }
    return true;
}


bool TreeTester::test_create_tree() {
    std::map <char, uint64_t> freq;

    freq['a'] = 10;
    freq['b'] = 3;
    freq['c'] = 2;
    freq['d'] = 14;

    HuffmanTree tree;
    tree.fit(freq);

    Buffer answer[4];
    answer[0] = Buffer(1, 1) + Buffer(1, 1);
    answer[1] = Buffer(1, 1) + Buffer(1, 0) + Buffer(1, 1);
    answer[2] = Buffer(1, 1) + Buffer(1, 0) + Buffer(1, 0);
    answer[3] = Buffer(1, 0);

    if (
        tree.get_code(0) != answer[0] || 
        tree.get_code(1) != answer[1] || 
        tree.get_code(2) != answer[2] || 
        tree.get_code(3) != answer[3]) 
    {
        return false;
    }
    return true;
}    


bool compareFiles(const std::string& p1, const std::string& p2) {
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail())
        return false; //file problem

    if (f1.tellg() != f2.tellg())
        return false; //size mismatch

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}


bool ArchiverTester::test_archivate1() {
    std::ifstream in("samples/sample1.txt", std::ios_base::binary);
    std::ofstream out("samples/test1", std::ios_base::binary);

    HuffmanTreeArchiver archivator;
    archivator.fit(in, TypeWork::Archivate);
    archivator.transform(in, out);

    in.close();
    out.close();
    return compareFiles("samples/answer1", "samples/test1");
}

bool ArchiverTester::test_archivate2() {
    std::ifstream in("samples/sample2.txt", std::ios_base::binary);
    std::ofstream out("samples/test2", std::ios_base::binary);

    HuffmanTreeArchiver archivator;
    archivator.fit(in, TypeWork::Archivate);
    archivator.transform(in, out);

    in.close();
    out.close();
    return compareFiles("samples/answer2", "samples/test2");
}

bool ArchiverTester::test_unarchivate1() {
    std::ifstream in("samples/answer1", std::ios_base::binary);
    std::ofstream out("samples/test1.txt");

    HuffmanTreeArchiver archivator;
    archivator.fit(in, TypeWork::UnArchivate);
    archivator.transform(in, out);

    in.close();
    out.close();
    return compareFiles("samples/test1.txt", "samples/sample1.txt");
}

bool ArchiverTester::test_unarchivate2() {
    std::ifstream in("samples/answer2", std::ios_base::binary);
    std::ofstream out("samples/test2.txt");

    HuffmanTreeArchiver archivator;
    archivator.fit(in, TypeWork::UnArchivate);
    archivator.transform(in, out);

    in.close();
    out.close();
    return compareFiles("samples/test2.txt", "samples/sample2.txt");
}

bool BufferTester::test_Buffer() {
    Buffer first, second, third;
    first += Buffer(1, 0);
    second += Buffer(2, 1);
    third += Buffer(1, 0) + Buffer(2, 1);
    return (first + second == third) && (first != second + third);
}

bool TestAll::test() {

    NodeTester nodeTester;
    TreeTester TreeTester;
    ArchiverTester archiverTester;
    BufferTester bufTester;

    assert(bufTester.test_Buffer());
    std::cout << "Buffer test passed" << std::endl;

    assert(nodeTester.test_freq());
    std::cout << "Frequency test passed" << std::endl;

    assert(nodeTester.test_head());
    std::cout << "Head test passed" << std::endl;

    assert(nodeTester.test_left());
    std::cout << "Left test passed" << std::endl;

    assert(nodeTester.test_right());
    std::cout << "Right test passed" << std::endl;    

    assert(nodeTester.test_sym());
    std::cout << "Symbol test passed" << std::endl;

    assert(TreeTester.test_create_tree());
    std::cout << "Tree test passed" << std::endl;

    assert(archiverTester.test_archivate1());
    std::cout << "Archivating test 1 passed" << std::endl;

    assert(archiverTester.test_archivate2());
    std::cout << "Archivating test 2 passed" << std::endl;

    assert(archiverTester.test_unarchivate1());
    std::cout << "Unarchivating test 1 passed" << std::endl;

    assert(archiverTester.test_unarchivate2());
    std::cout << "Unarchivating test 2 passed" << std::endl;

    std::cout << "All test passed" << std::endl;
    return true;
}
}
}