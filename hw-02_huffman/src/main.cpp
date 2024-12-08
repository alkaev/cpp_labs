#include "HuffmanTreeArchiver.hpp"

#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>

int main(int argc, const char** argv) {

    bool have_inp = 0, have_outp = 0;
    std::string arg, path_in, path_out;
    HuffmanArchiver::TypeWork t = HuffmanArchiver::TypeWork::NoType;

    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "-c"))
            t = HuffmanArchiver::TypeWork::Archivate;
        
        if (!strcmp(argv[i], "-u"))
            t = HuffmanArchiver::TypeWork::UnArchivate;
        
        if (!strcmp(argv[i], "-f")) {
            assert(i + 1 < argc); // "No name of inputs file"
            assert(!have_inp); // "Already have input file"
            have_inp = 1;
            path_in = argv[i + 1];
        }
        if (!strcmp(argv[i], "-o")) {
            assert(i + 1 < argc); // "No name of output file"
            assert(!have_outp); // Twice give output file"
            have_outp = 1;
            path_out = argv[i + 1];
        }
    }

    assert(t != HuffmanArchiver::TypeWork::NoType); // "No type for work"
    assert(have_inp); // "No input file"
    assert(have_outp); // "No output file"

    std::ifstream in(path_in, std::ios_base::binary); 
    std::ofstream out(path_out, std::ios_base::binary); 

    HuffmanArchiver::HuffmanTreeArchiver archiver;

    archiver.fit(in, t);
    archiver.transform(in, out);

    std::cout << archiver.get_mem_inp() << "\n" << archiver.get_mem_out() << "\n" << archiver.get_mem_add() << std::endl;
}