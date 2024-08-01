#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <cstdio> // Biblioteca para a função remove
#include <unordered_map>
#include <iomanip>

// Estrutura para armazenar as coordenadas
struct Coordenada {
    int centerNumber;
    int atomicNumber;
    double x, y, z;
};

// Estrutura para armazenar as cargas
struct Carga {
    int atomNumber;
    std::string atomType;
    double charge;
};

// Função para importar coordenadas do arquivo
std::vector<Coordenada> importarCoordenadas(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<Coordenada> coordenadas;

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return coordenadas; // Retorna um vetor vazio em caso de erro
    }

    std::string linha;
    bool coordenadasIniciadas = false;
    // Ler o arquivo linha por linha
    while (std::getline(arquivo, linha)) {
        if (linha.find("                         Standard orientation:                         ") != std::string::npos) {
            coordenadasIniciadas = true;
            // Pular a linha de cabeçalho e a linha de separador
            std::getline(arquivo, linha);
            std::getline(arquivo, linha);
            std::getline(arquivo, linha);
            std::getline(arquivo, linha);
            continue;
        }

        if (coordenadasIniciadas) {
            if (linha.find("-----") != std::string::npos) {
                coordenadasIniciadas = false;
                continue;
            }

            Coordenada coord;
            std::istringstream iss(linha);
            iss >> coord.centerNumber >> coord.atomicNumber >> coord.atomicNumber >> coord.x >> coord.y >> coord.z;
            coordenadas.push_back(coord);
        }
    }

    // Fechar o arquivo
    arquivo.close();

    return coordenadas; // Retorna o vetor com as coordenadas
}


// Função para importar cargas do arquivo
std::vector<Carga> importarCargas(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<Carga> cargas;

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro: " << nomeArquivo << std::endl;
        return cargas; // Retorna um vetor vazio em caso de erro
    }

    std::string linha;
    bool cargasIniciadas = false;
    // Ler o arquivo linha por linha
    while (std::getline(arquivo, linha)) {
        if (linha.find("ESP charges:") != std::string::npos) {
            cargasIniciadas = true;
            // Pular a linha de cabeçalho
            std::getline(arquivo, linha);
            continue;
        }

        if (cargasIniciadas) {
            if (linha.find("Sum of ESP charges") != std::string::npos) {
                cargasIniciadas = false;
                break;
            }

            Carga carga;
            std::istringstream iss(linha);
            if (iss >> carga.atomNumber >> carga.atomType >> carga.charge) {
                cargas.push_back(carga);
            }
        }
    }

    // Fechar o arquivo
    arquivo.close();

    return cargas; // Retorna o vetor com as cargas
}

// Função para salvar coordenadas em um arquivo
void salvarCoordenadas(const std::vector<Coordenada>& coordenadas, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro: " << nomeArquivo << std::endl;
        return;
    }

    // Escrever as coordenadas no arquivo
    for (const auto& coord : coordenadas) {
        arquivo << coord.centerNumber << " " << coord.atomicNumber << " " << coord.x << " " << coord.y << " " << coord.z << std::endl;
    }

    // Fechar o arquivo
    arquivo.close();
}


// Função para salvar cargas em um arquivo
void salvarCargas(const std::vector<Carga>& cargas, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro: " << nomeArquivo << std::endl;
        return;
    }

    // Escrever as cargas no arquivo
    for (const auto& carga : cargas) {
        arquivo << carga.atomNumber << " " << carga.atomType << " " << carga.charge << std::endl;
    }

    // Fechar o arquivo
    arquivo.close();
}

void removeFirstColumn(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile.is_open()) {
        std::cerr << "Erro.\n";
        return;
    }
    if (!outFile.is_open()) {
        std::cerr << "Erro.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> columns;

        // Ler todas as colunas na linha
        while (iss >> token) {
            columns.push_back(token);
        }

        // Escrever as colunas, exceto a primeira
        for (size_t i = 1; i < columns.size(); ++i) {
            outFile << columns[i];
            if (i < columns.size() - 1) {
                outFile << " "; // Adicionar espaço entre colunas
            }
        }
        outFile << "\n"; // Adicionar nova linha
    }

    inFile.close();
    outFile.close();
}

//montar output.pqr
struct Atom {
    int index;
    std::string type;
    double x, y, z, charge, volume;
};

std::unordered_map<std::string, double> atomVolumes = {
    {"H", 1.2},
    {"C", 1.7},
    {"N", 1.55},
    {"O", 1.47},
    {"Li", 1.82},
    {"Be", 1.53},
    {"Na", 2.27},
    {"Mg", 1.73},
    {"K", 2.75},
    {"Ca", 2.31},
    {"Rb", 3.03},
    {"Cs", 3.43},
    {"Sr", 2.49},
    {"Ba", 2.68},
    {"Sc", 2.11},
    {"Ni", 1.63},
    {"Cu", 1.40},
    {"Zn", 1.39},
    {"Pd", 1.63},
    {"Ag", 1.72},
    {"Cd", 1.58},
    {"Pt", 1.75},
    {"Au", 1.66},
    {"Hg", 1.55},
    {"He", 1.4},
    {"Ne", 1.54},
    {"Ar", 1.88},
    {"Kr", 2.02},
    {"Xe", 2.16},
    {"Rn", 2.83},
    {"B", 1.92},
    {"F", 1.47},
    {"Al", 1.84},
    {"Si", 2.1},
    {"P", 1.8},
    {"S", 1.8},
    {"Cl", 1.75},
    {"Ga", 1.87},
    {"Ge", 2.11},
    {"As", 1.85},
    {"Se", 1.9},
    {"Br", 1.85},
    {"In", 1.93},
    {"Sn", 2.17},
    {"Sb", 2.06},
    {"Te", 2.06},
    {"I", 1.98},
    {"Tl", 1.96},
    {"Pb", 2.02},
    {"Bi", 2.2},
    {"Po", 3.48},
    {"Rn", 2.83},
    {"U", 1.86},
};

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char* argv[]) {

std::cout << "-----Wellcome to converter!-----" << std::endl;
std::cout << "--------By Lucca Lommez--------" << std::endl;

    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.log>" << std::endl;
        return 1;
    }

    std::string nomeArquivoEntrada = argv[1];
    std::filesystem::path caminhoEntrada = nomeArquivoEntrada;
    std::filesystem::path diretorio = caminhoEntrada.parent_path();

    std::string nomeArquivoCoordenadasSaida = (diretorio / "coordenadas.log").string();
    std::string nomeArquivoCargasSaida = (diretorio / "cargas.log").string();

    // Importar cargas e coordenadas do arquivo de entrada
    std::vector<Coordenada> coordenadas = importarCoordenadas(nomeArquivoEntrada);
    std::vector<Carga> cargas = importarCargas(nomeArquivoEntrada);

    // Salvar cargas e coordenadas em arquivos separados
    salvarCoordenadas(coordenadas, nomeArquivoCoordenadasSaida);
    salvarCargas(cargas, nomeArquivoCargasSaida);

    // Confirmar a operação
    std::cout << "Coords import to " << nomeArquivoEntrada << " and save in xyz" << std::endl;
    std::cout << "Charges import to " << nomeArquivoEntrada << " and save in charges_atoms" << std::endl;

    //remover colunas de 0 das cargas 
    std::string inputFile = "cargas.log";
    std::string outputFile = "charges_atoms.log";
    std::string inputFile2 = "coordenadas.log";
    std::string outputFile2 = "temporary.log";
    std::string inputFile3 = "temporary.log";
    std::string outputFile3 = "xyz.log";

    removeFirstColumn(inputFile, outputFile);
    removeFirstColumn(inputFile2, outputFile2);
    removeFirstColumn(inputFile3, outputFile3);
    //apaga o arquivo cargas

  if (std::remove(inputFile.c_str()) != 0) {
        std::cerr << "Erro.\n";
    } 

if (std::remove(inputFile2.c_str()) != 0) {
        std::cerr << "Erro.\n";
    } 

    if (std::remove(inputFile3.c_str()) != 0) {
        std::cerr << "Erro.\n";
    } 

    
    //criar pqr
    std::ifstream xyzFile("xyz.log");
    std::ifstream cargaFile("charges_atoms.log");
    std::ofstream outputFile4("output.pqr");

    if (!xyzFile.is_open() || !cargaFile.is_open() || !outputFile4.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Atom> atoms;

    // Read carga_e_atomos.log to get atom types and charges
    while (std::getline(cargaFile, line)) {
        std::vector<std::string> tokens = split(line, ' ');
        Atom atom;
        atom.type = tokens[0];
        atom.charge = std::stod(tokens[1]);
        atoms.push_back(atom);
    }

    // Read xyz.log to get coordinates
    size_t index = 0;
    while (std::getline(xyzFile, line)) {
        std::vector<std::string> tokens = split(line, ' ');
        atoms[index].x = std::stod(tokens[0]);
        atoms[index].y = std::stod(tokens[1]);
        atoms[index].z = std::stod(tokens[2]);
        atoms[index].index = index + 1;
        atoms[index].volume = atomVolumes[atoms[index].type];
        index++;
    }

   // Write to output.pqr with formatted output
    for (const auto &atom : atoms) {
        outputFile4 << "ATOM\t"
                   << std::setw(4) << atom.index << "\t"
                   << std::setw(2) << atom.type << "\t"
                   << "LIG\t1\t"
                   << std::setw(10) << std::fixed << std::setprecision(6) << atom.x << "\t"
                   << std::setw(10) << std::fixed << std::setprecision(6) << atom.y << "\t"
                   << std::setw(10) << std::fixed << std::setprecision(6) << atom.z << "\t"
                   << std::setw(10) << std::fixed << std::setprecision(6) << atom.charge << "\t"
                   << std::setw(4) << std::fixed << std::setprecision(2) << atom.volume << std::endl;
    }

    xyzFile.close();
    cargaFile.close();
    outputFile4.close();

    std::cout << "output.pqr done! :)" << std::endl;

    return 0;
}
