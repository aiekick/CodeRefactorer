#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <interfaces/IRefactorer.h>

enum class RefactorerType {
	None = 0,
	VirtualToOverride,
	Count
};

class Refactorer {
public:
	bool refactor(const std::filesystem::path& vRootPath, RefactorerType vRefactorerType, bool vRecursive);

private:
	void m_addFile(const std::filesystem::directory_entry& vEntry, const std::vector<std::string>& vExts, FilesSet& vInOutFiles);
	FilesSet m_scanDirForFiles(const std::filesystem::path& vRootPath, bool vRecursive, const std::string& vExts);
};
