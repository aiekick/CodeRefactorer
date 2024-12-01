#pragma once

#include <interfaces/IRefactorer.h>

class VirtualToOverride : public IRefactorer {
public:
	bool refactor(const FilesSet& vFiles) override;
};
