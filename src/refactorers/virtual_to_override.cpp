#include <refactorers/virtual_to_override.h>
#include <cassert>
#include <iostream>
#include <filesystem>

/*
this fonction will repalce 'virtual' keyword in methods by 'override' at end
1) will check if class derive from other class
2) will locate method with 'virtual' keyword
3) will rewrite these method by delete 'virtual' and add 'override' keyword at end
*/
bool VirtualToOverride::refactor(const FilesSet& vFiles) {
    assert(!vFiles.empty()); // internal
    std::cout << "Modifications : " << std::endl;
    for (const auto& file : vFiles) {
        std::cout << file << " : 0/N refactored methods" << std::endl;
    }
	return false;
}


