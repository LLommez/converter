#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib> // Para usar o system()
#include <fstream> // Adiciona suporte para manipulação de arquivos

void executeConverter(const std::string &converter, const std::string &file) {
    std::string command = "./" + converter + " " + file;
    system(command.c_str());
}

void listFiles() {
    std::cout << "Files available in the folder:\n";
    system("ls *.log *.molden.input"); // Lista apenas os arquivos com extensões específicas
}

std::vector<std::string> splitFiles(const std::string &input) {
    std::vector<std::string> files;
    std::istringstream iss(input);
    std::string file;
    while (iss >> file) {
        files.push_back(file);
    }
    return files;
}

void processFiles(const std::vector<std::string> &files) {
    std::string converterPath = "./converter_files/";

    for (const auto &file : files) {
        if (file.find(".log") != std::string::npos) {
            executeConverter(converterPath + "converter_gaussian", file);
        } else if (file.find(".molden.input") != std::string::npos) {
            executeConverter(converterPath + "executormtf", file);
        } else {
            std::cout << "Unsupported file extension for file: " << file << std::endl;
        }
    }
}

int main() {
    std::cout << "-----Welcome to converter!-----" << std::endl;
    std::cout << "--------By Lucca Lommez--------" << std::endl;

    std::string filenamesInput;
    char processAll;

    // Passo 1: Listar os arquivos disponíveis
    listFiles();

    // Perguntar se o usuário deseja processar todos os arquivos automaticamente
    std::cout << "Do you want to execute all files listed? (y/n): ";
    std::cin >> processAll;
    std::cin.ignore(); // Limpar o caractere de nova linha após a entrada

    std::vector<std::string> files;

    if (processAll == 'y' || processAll == 'Y') {
        // Caso o usuário opte por processar todos os arquivos, coletar os nomes com extensão específica
        system("ls *.log *.molden.input > temp_files.txt");
        std::ifstream infile("temp_files.txt");
        std::string file;
        while (infile >> file) {
            files.push_back(file);
        }
        infile.close();
        system("rm temp_files.txt"); // Remover o arquivo temporário
    } else {
        // Caso contrário, solicitar os nomes dos arquivos ao usuário
        std::cout << "Type the names of the files to be loaded (separated by space): ";
        std::getline(std::cin, filenamesInput);
        files = splitFiles(filenamesInput);
    }

    // Confirmar os arquivos carregados
    std::cout << "Files loaded successfully:\n";
    for (const auto &file : files) {
        std::cout << "- " << file << std::endl;
    }

    // Processar os arquivos com base em sua extensão
    processFiles(files);

    return 0;
}


