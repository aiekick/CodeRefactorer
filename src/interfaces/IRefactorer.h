#pragma once

#include <set>
#include <string>
#include <unordered_map>

typedef std::set<std::string> FilesSet;

class IRefactorer {
public:

public:
	virtual bool refactor(const FilesSet& vFiles) = 0;
};
