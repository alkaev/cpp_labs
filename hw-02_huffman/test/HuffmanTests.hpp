#include "HuffmanTreeNode.hpp"
#include "HuffmanTree.hpp"
#include "HuffmanTreeArchiver.hpp"
#include "FileWorker.hpp"


namespace HuffmanArchiver {
namespace HuffmanTest {
class NodeTester{
public:

    bool test_left();
    bool test_right();
    bool test_head();
    bool test_freq();
    bool test_sym();
};

class TreeTester{
public:
    bool test_create_tree();    
};

class ArchiverTester{
public:

    bool test_archivate1();
    bool test_unarchivate1();
    bool test_archivate2();
    bool test_unarchivate2();
};

class BufferTester{
public:
    bool test_Buffer();
};

class TestAll {
public:
    bool test();
};

}
}