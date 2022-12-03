#include "Test/test.h"
#include <stdlib.h>
#include <time.h>
#include <vector> // para el test

const int X = 500;

int main(int argc, char const *argv[])
{
    // PARTE 1

    srand(time(nullptr));

    std::vector<std::string> users(X);
    std::vector<std::string> passwords(X);
    std::vector<std::string> dates(X);

    std::ifstream archivo("data.csv");
    std::string linea;
    char delimitador = ',';
    getline(archivo, linea);

    int i = 0;
    while (getline(archivo, linea))
    {
        std::stringstream stream(linea);
        std::string user, password, date;
        getline(stream, user, delimitador);
        getline(stream, password, delimitador);
        getline(stream, date, delimitador);
        users[i] = user;
        passwords[i] = password;
        dates[i] = date;
        i++;
    }

    /*
        Lo que se hizo fue poner toda la data en los vectores:
            users;
            passwords;
            dates;

        luego, generaremos transacciones aleatorias y las insertaremos en la blockchain
    */

    archivo.close();

    Blockchain bch;

    for (int i = 0; i < X; i++)
    {   
        std::cout << "creando bloque de: " << users[i] << std::endl;
        bch.createUser(users[i], passwords[i]);
        std::cout << "con sus transacciones: " << std::endl;
        for (int j = 0; j < 4 + rand() % (7 - 4 + 1); j++)
        {
            int k = 0 + rand() % (X-1 - 0 + 1);
            int d = 0 + rand() % (X-1 - 0 + 1);
            float f = float(100 + rand() % (1500 - 100 + 1)) / 7.0;
            std::cout << users[i] << ", " << users[k] << ", " << f << ", " << dates[d] << std::endl;
            bch.setTx(users[i], passwords[i], users[k], f, dates[d]);
        }
        bch.mineCascade(users[i], passwords[i]);
        std::cout << std::endl;
    }

    /*
        como vemos, con el primero for crearemos 500 bloques (usuarios)
        con el segundo for, crearemos transacciones aleatorias entre el usuario creado y otros usuarios (cada bloque tendra como minimo 4 transacciones y como maximo 7)
        luego de esto, "sellamos" minando el bloque

        entonces, nuestra blockchain como minimo tendra 2000 (500*4) transacciones en total
    */

    std::ofstream blockchain("blockchain.txt");
    blockchain << bch; // exportamos en un txt
    blockchain.close();

    std::ofstream modified("modified.txt");
    bch.setTx(users[279], passwords[279], "Noni", 244, "1633870724");
    modified << bch;
    modified.close();

    /*
        Agregamos una transaccion en en el bloque 279 del blockchain, como estamos vulnerando
        la estructura, lo que ocurrira es que se modificaran los hashes desde el bloque 279
        en adelante

        exportamos en un txt
    */

    std::ofstream mine("mine.txt");
    bch.mineCascade(users[484], passwords[484]);
    mine << bch;
    mine.close();
    
    /*
        Aqui lo que hago es minar el bloque 484, cuando mine este bloque se cambiara su nonce
        para asi poder tener el prefijo de 4 0's en su hash (PofW)

        este metodo minecascade lo que hace es mina el bloque que le digo, luego recalcula los hashes del bloque en adelante.

        simulo lo mismo que en la pagina demo de la rubrica (https://andersbrownworth.com/blockchain/tokens)

        exportamos en un txt
    */

    // PARTE 2

    std::ofstream adminDate("adminDate.txt");
    auto a1 = bch.admiTxDate();
    for (int i = 0; i < a1.SIZE(); i++) { adminDate << *(a1[i]) << "\n"; }
    adminDate.close();
    
    std::ofstream adminAmount("adminAmount.txt");
    auto a2 = bch.admiTxAmount();
    for (int i = 0; i < a2.SIZE(); i++) { adminAmount << *(a2[i]) << "\n"; }
    adminAmount.close();

    /*
        aqui solo estamos probando que el super admi funciona

        exportamos en dos txt
    */

    return 0;
}
