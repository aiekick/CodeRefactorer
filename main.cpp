#include <cstdlib>
#include <cstdint>
#include <ezlibs/ezApp.hpp>
#include <ezlibs/ezArgs.hpp>

#include <refactorer.h>
#include <interfaces/IRefactorer.h>

#include <filesystem>
namespace fs = std::filesystem;

int main(int32_t vArgc, char** vArgv) {
	ez::App app(vArgc, vArgv);
	ez::Args args("CodeRefactorer");
	args.addDescription("CodeRefactorer is a tool for refactor cpp code");
	args.addOptional("-p").help("root path").def(app.getCurDirectory());
	args.addOptional("-r").help("recursive");
	args.addOptional("--virtualToOverride").help("replace 'virtual' by 'override' in classes for methods");
	if (args.parse(vArgc, vArgv)) {
		Refactorer refactorer;
		auto rootPath = fs::path(args.getValue<std::string>("-p"));
		bool recursive = args.isPresent("-r");;
		RefactorerType type = RefactorerType::None;
		if (args.isPresent("--virtualToOverride")) {
			type = RefactorerType::VirtualToOverride;
		}
        if (type != RefactorerType::None) {
            if (refactorer.refactor(rootPath, type, recursive)) {
                return EXIT_SUCCESS;
            }
		}
	}
	return EXIT_FAILURE;
}
