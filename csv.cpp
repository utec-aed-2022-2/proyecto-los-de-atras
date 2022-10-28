#include "blockchain.h"
#include <fstream>

int main(int argc, char const *argv[])
{
    std::ifstream archivo("MOCK_DATA_DEMO.csv");
    std::string linea;
    char delimitador = ',';
    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        std::stringstream stream(linea);
        std::string string1, string2, numberstr, date;

        getline(stream, string1, delimitador);
        getline(stream, string2, delimitador);
        getline(stream, numberstr, delimitador);
        getline(stream, date, delimitador);

        uint64_t number = stoi(numberstr);

        transaction tx(string1, string2, number, date);

        std::cout << tx << std::endl;
    }

    archivo.close();

    return 0;
}