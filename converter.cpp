#include <iostream>
#include <string>
#include <cstdlib> // Para usar o system()

void executeConverter(const std::string &converter, const std::string &file) {
    // O comando será executado no formato "./converter_gaussian nome_do_arquivo"
    std::string command = "./" + converter + " " + file;
    system(command.c_str());
}

void listFiles() {
    std::cout << "Files available in the folder:\n";
    system("ls"); // Comando para listar os arquivos
}

int main() {

std::cout << "-----Wellcome to converter!-----" << std::endl;
std::cout << "--------By Lucca Lommez--------" << std::endl;

    std::string filename;
    int choice;

    // Passo 1: Listar os arquivos disponíveis
    listFiles();

    // Passo 2: Solicitar que o usuário insira o nome do arquivo (que estará na mesma pasta do programa)
    std::cout << "Type the name of the file to be loaded: ";
    std::getline(std::cin, filename);

    // Simular carregamento do arquivo
    std::cout << "File loaded successfully: " << filename << std::endl;

    // Passo 2: Oferecer opções para o usuário
    std::cout << "Choose an option:\n";
    std::cout << "1 - Input Gaussian\n";
    std::cout << "2 - Input Orca\n";
    std::cout << "Type your choice: ";
    std::cin >> choice;

    // Passo 3: Executar o programa com base na escolha do usuário
std::string converterPath = "./converter_files/"; // Caminho para a pasta onde estão os executáveis
switch (choice) {
    case 1:
        //std::cout << "Executando " << converterPath << "converter_gaussian com o arquivo " << filename << std::endl;
        executeConverter(converterPath + "converter_gaussian", filename);
        break;
    case 2:
        //std::cout << "Executando " << converterPath << "executormtf com o arquivo " << filename << std::endl;
        executeConverter(converterPath + "executormtf", filename);
        break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
}


    return 0;
}
