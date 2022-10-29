#include "../classes/blockchain.h"
#include "../functions/unixtodate.h"
#include "../functions/stoli.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    srand(time(nullptr));
    int inicio = 1; int fin = 5;

    std::ifstream archivo("MOCK_DATA_DEMO.csv");
    std::string linea;
    char delimitador = ',';
    getline(archivo, linea);

    blockchain xd;
    xd.addBlock();
    xd.addBlock();
    xd.addBlock();
    xd.addBlock();
    xd.addBlock();

    while (getline(archivo, linea))
    {
        std::stringstream stream(linea);
        std::string string1, string2, numberstr, dateunix;

        getline(stream, string1, delimitador);
        getline(stream, string2, delimitador);
        getline(stream, numberstr, delimitador);
        getline(stream, dateunix, delimitador);

        float number = stof(numberstr);
        long int date = stoli(dateunix.substr(0, 10));

        transaction tx(string1, string2, number, unixTimeToHumanReadable(date));
        xd.setData(inicio + rand() % (fin - inicio + 1), tx);
    }

    archivo.close();

    std::cout << xd;

    return 0;
}