#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
    std::ifstream archivo("MOCK_DATA_DEMO2.csv");
    std::string linea;
    char delimitador = ',';
    getline(archivo, linea);
    while (getline(archivo, linea))
    {
        std::stringstream stream(linea);
        std::string username, password;

        getline(stream, username, delimitador);
        getline(stream, password, delimitador);

        std::cout << "username: " << username << ", password: " << password << std::endl;
    }
    archivo.close();

    return 0;
}