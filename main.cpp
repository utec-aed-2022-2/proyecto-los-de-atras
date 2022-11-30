#include "Test/test.h"
//#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <ctime>
unsigned t0, t1;

int main(int argc, char const *argv[])
{
    Blockchain blockchain;

    // traigo la data
    std::vector<std::string> users;
    std::vector<std::string> passwords;
    std::ifstream iput("input.csv");
    std::string linea;
    char delimitador = ',';
    getline(iput, linea);
    t0 = clock();
    while (getline(iput, linea))
    {
        std::stringstream stream(linea);
        std::string user, password;

        getline(stream, user, delimitador);
        getline(stream, password, delimitador);

        // creo los usuarios
        blockchain.createUser(user, password);

        users.push_back(user);
        passwords.push_back(password);
    }
    t1 = clock();
    iput.close();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    std::cout << "Execution Time: " << (double(time)/CLOCKS_PER_SEC);

    std::ofstream oput("output.txt");
    oput<<blockchain;

    return 0;
}
