#include <refactorer.h>

#include <memory>
#include <string>
#include <cassert>
#include <iostream>
#include <filesystem>
#include <ezlibs/ezStr.hpp>

#include <refactorers/virtual_to_override.h>

bool Refactorer::refactor(const std::filesystem::path& vRootPath, RefactorerType vRefactorerType, bool vRecursive) {
    bool ret = false;
    auto files = m_scanDirForFiles(vRootPath, vRecursive, ".h,.hpp");
    if (!files.empty()) {
        std::unique_ptr<IRefactorer> pRefactorer = nullptr;
        switch (vRefactorerType) {
            case RefactorerType::VirtualToOverride: {
                pRefactorer = std::make_unique<VirtualToOverride>();
            } break;
            case RefactorerType::None:
            case RefactorerType::Count:
            default: break;
        }
        if (pRefactorer != nullptr) {
            ret = pRefactorer->refactor(files);
        }
    } else {
        std::cerr << "No files found in " << vRootPath.string() << std::endl;
    }
    return ret;
}

void Refactorer::m_addFile(const std::filesystem::directory_entry& vEntry, const std::vector<std::string>& vExts, FilesSet& vInOutFiles) {
    if (std::filesystem::is_regular_file(vEntry)) { // Vérifie si c'est un fichier
        const auto& filePath = vEntry.path();
        if (std::find(vExts.begin(), vExts.end(), filePath.extension().string()) != vExts.end()) {
            vInOutFiles.emplace(filePath.string());
        }
    }
}

FilesSet Refactorer::m_scanDirForFiles(const std::filesystem::path& vRootPath, bool vRecursive, const std::string& vExts) {
    FilesSet ret;

    if (vExts.empty()) {
        assert(nullptr);  // internal
        return ret;
    }

    auto exts_array = ez::str::splitStringToVector(vExts, ',');
    if (exts_array.empty()) {
        assert(nullptr); // internal
        return ret;
    }

    if (std::filesystem::exists(vRootPath) && std::filesystem::is_directory(vRootPath)) {
        if (vRecursive) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(vRootPath)) {
                m_addFile(entry, exts_array, ret);
            }
        }
        else {
            for (const auto& entry : std::filesystem::directory_iterator(vRootPath)) {
                m_addFile(entry, exts_array, ret);
            }
        }
    } else {
        std::cerr << "The root path " << vRootPath.string() << " is not existing or is not a directory" << std::endl;
    }

    return ret;
}
