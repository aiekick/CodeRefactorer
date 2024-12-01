#include <refactorers/virtual_to_override.h>

#include <regex>
#include <cassert>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <ezlibs/ezStr.hpp>
#include <ezlibs/ezFile.hpp>

/*
this fonction will replace 'virtual' keyword in methods by 'override' at end
1) will check if class derive from other class
2) will locate method with 'virtual' keyword
3) will rewrite these method by delete 'virtual' and add 'override' keyword at end
*/

bool VirtualToOverride::refactor(const FilesSet& vFiles) {
    assert(!vFiles.empty()); // internal
    std::cout << "Modifications : " << std::endl;
    for (const auto& file : vFiles) {
        m_refactorFile(file);
    }
	return false;
}

bool VirtualToOverride::m_refactorFile(const std::string& vFile) {
    std::ifstream fichier_entree(vFile);
    if (!fichier_entree.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier en lecture." << std::endl;
        return false;
    }

    std::string nom_fichier_temp = vFile + ".tmp";
    std::ofstream fichier_sortie(nom_fichier_temp);
    if (!fichier_sortie.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier en écriture." << std::endl;
        return false;
    }

    std::string ligne;
    bool dans_classe_derivee = false;
    int niveau_accolade = 0;

    std::regex regex_classe_derivee(R"(\s*class\s+\w+\s*:\s*public\s+\w+\s*\{)");
    std::regex regex_virtual(R"((.*)virtual\s+(.*);(.*))");
    std::smatch match;

    while (std::getline(fichier_entree, ligne)) {
        std::string ligne_trim = ligne;
        ligne_trim.erase(0, ligne_trim.find_first_not_of(" \t"));

        if (std::regex_match(ligne_trim, match, regex_classe_derivee)) {
            dans_classe_derivee = true;
        }

        niveau_accolade += std::count(ligne.begin(), ligne.end(), '{');
        niveau_accolade -= std::count(ligne.begin(), ligne.end(), '}');
        if (niveau_accolade == 0) {
            dans_classe_derivee = false;
        }

        if (dans_classe_derivee) {
            if (std::regex_match(ligne, match, regex_virtual)) {
                std::string block0 = match[1];
                std::string block1 = match[2];
                std::string block2 = match[3];
                std::string new_function = block0 + block1;
                if (new_function.find("override") == std::string::npos) {
                    new_function += " override;";
                    new_function += block2;
                }
                fichier_sortie << new_function << std::endl;
            } else {
                fichier_sortie << ligne << std::endl;
            }
        } else {
            fichier_sortie << ligne << std::endl;
        }
    }

    fichier_entree.close();
    fichier_sortie.close();

    return true;
}
