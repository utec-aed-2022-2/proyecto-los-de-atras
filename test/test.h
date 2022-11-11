/*
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

void read()
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
}

#include <iostream>
#include <chrono>
 
int main()
{
    const auto p1 = std::chrono::system_clock::now();
 
    std::cout << "seconds since epoch: "
              << std::chrono::duration_cast<std::chrono::seconds>(
                   p1.time_since_epoch()).count() << '\n';
}

#include "class/BPlusTree.h"
#include "Transaction.h"

int main(int argc, char const *argv[])
{

    transaction tx1("Skyndu", "Puce", 8822.42, "1643003849");
    transaction tx2("Bigtax", "Granite", 1822.57, "1643003856");

    std::cout << &tx1 << std::endl;
    std::cout << tx1 << std::endl;
    std::cout << &tx2 << std::endl;
    std::cout << tx2 << std::endl;

    transactionOverload<transaction, float> x1(tx1);
    transactionOverload<transaction, float> y1(tx2);

    std::cout << (x1 < y1) << std::endl;

    transactionOverload<transaction, std::string> x2(tx1);
    transactionOverload<transaction, std::string> y2(tx2);

    std::cout << (x2 < y2) << std::endl;

    std::cout << x1.pointer << std::endl;
    std::cout << x2.pointer << std::endl;
    std::cout << y1.pointer << std::endl;
    std::cout << y2.pointer << std::endl;

    return 0;
}
*/

/*
#include "class/BPlusTree.h"
#include "Transaction.h"

int main(int argc, char const *argv[])
{
    transaction tx1("Realcube", "Goldenrod", 300.3, "1643003853");
    std::cout << &tx1 << std::endl;
    transaction tx2("Skyndu", "Puce", 100, "1643003870");
    std::cout << &tx2 << std::endl;
    transaction tx3("Bigtax", "Granite", 200, "1643003856");
    std::cout << &tx3 << std::endl;
    transaction tx4("Bigtax", "Granite", 1322.57, "1643003849");
    std::cout << &tx4 << std::endl;
    transaction tx5("Skyndu", "Puce", 882.42, "1643003851");
    std::cout << &tx5 << std::endl;

    BPlusTree<transactionOverload<transaction, std::string>> orderByDate(3);
    BPlusTree<transactionOverload<transaction, float>> orderByNumber(3);
    std::cout << std::endl;


    transactionOverload<transaction, std::string> ptx1(tx1);
    std::cout << ptx1.pointer << std::endl;
    transactionOverload<transaction, std::string> ptx2(tx2);
    std::cout << ptx2.pointer << std::endl;
    transactionOverload<transaction, std::string> ptx3(tx3);
    std::cout << ptx3.pointer << std::endl;
    transactionOverload<transaction, std::string> ptx4(tx4);
    std::cout << ptx4.pointer << std::endl;
    transactionOverload<transaction, std::string> ptx5(tx5);
    std::cout << ptx5.pointer << std::endl;

    orderByDate.insert(ptx1);
    orderByDate.insert(ptx2);
    orderByDate.insert(ptx3);
    orderByDate.insert(ptx4);
    orderByDate.insert(ptx5);

    coutOrder(orderByDate.GetRoot());

    return 0;
}

#include "class/BPlusTree.h"
#include "Transaction.h"

int main(int argc, char const *argv[])
{
    transaction tx1("Realcube", "Goldenrod", 300.3, "1643003853");
    transaction tx2("Skyndu", "Puce", 100, "1643003870");
    transaction tx3("Bigtax", "Granite", 200, "1643003856");
    transaction tx4("Bigtax", "Granite", 1322.57, "1643003849");
    transaction tx5("Skyndu", "Puce", 882.42, "1643003851");

    transaction tx6("Realpoint", "Diamante", 1233.482, "1643003851");
    transaction tx7("Diamante", "Realpoint", 2882.2, "1643003851");

    BPlusTree<transactionOverload<transaction, std::string>> orderByDate(3);
    BPlusTree<transactionOverload<transaction, float>> orderByNumber(3);

    orderByDate.insert(&tx1);
    orderByDate.insert(&tx2);
    orderByDate.insert(&tx3);
    orderByDate.insert(&tx4);
    orderByDate.insert(&tx5);

    orderByNumber.insert(&tx1);
    orderByNumber.insert(&tx2);
    orderByNumber.insert(&tx3);
    orderByNumber.insert(&tx4);
    orderByNumber.insert(&tx5);

    coutOrder(orderByDate.GetRoot());
    std::cout << orderByNumber.search(&tx2) << std::endl;
    std::cout << orderByNumber.search(&tx7) << std::endl;
    coutOrder(orderByNumber.GetRoot());

    return 0;
}

#include "class/BPlusTree.h"
#include "BlockChain.h"

int main(int argc, char const *argv[])
{   
    HashMap<std::string, transaction*> dataHash;

    transaction tx1("Skyndu", "Puce", 8822.42, "1643003849");
    transaction tx2("Bigtax", "Granite", 1822.57, "1655979226");

    dataHash.set("tx1", &tx1);
    dataHash.set("tx2", &tx2);

    std::cout << &tx1 << std::endl;
    std::cout << dataHash.get("tx2") << std::endl;

    return 0;
}

#include "Block.h"

int main(int argc, char const *argv[])
{
    block B(1, "0000000000000000000000000000000000000000000000000000000000000000");

    transaction tx1("Realcube", "Goldenrod", 300.43, "1643003853");
    transaction tx2("Skyndu", "Puce", 100, "1643003870");
    transaction tx3("Bigtax", "Granite", 200, "1643003856");
    transaction tx4("Bigtax", "Granite", 1322.57, "1643003849");
    transaction tx5("Skyndu", "Puce", 882.42, "1643003851");
    transaction tx6("Realpoint", "Diamante", 1233.482, "1643003812");
    transaction tx7("Diamante", "Realpoint", 2882.2, "1643003865");

    B.insert(tx1);
    B.insert(tx2);
    B.insert(tx3);
    B.insert(tx4);
    B.insert(tx5);
    B.insert(tx6);
    B.insert(tx7);

    std::cout << std::endl;
    std::cout << B;

    std::cout << std::endl;
    B.coutOrderByDate();

    std::cout << std::endl;
    B.coutOrderByNumber();

    std::cout << std::endl;
    B.mine();
    std::cout << B;

    return 0;
}

#include "Block.h"

int main(int argc, char const *argv[])
{
    transaction tx1("Realcube", "Goldenrod", 300.43, "1643003853");
    transaction tx2("Skyndu", "Puce", 100, "1643003870");
    transaction tx3("Bigtax", "Granite", 200, "1643003856");
    transaction tx4("Bigtax", "Granite", 1322.57, "1643003849");
    transaction tx5("Skyndu", "Puce", 882.42, "1643003851");
    transaction tx6("Realpoint", "Diamante", 1233.482, "1643003812");
    transaction tx7("Diamante", "Realpoint", 2882.2, "1643003865");

    block B1(1, "0000000000000000000000000000000000000000000000000000000000000000");
    block B2(2, B1.hash);

    B1.insert(tx1);
    B1.insert(tx2);
    B1.insert(tx3);

    B2.insert(tx4);
    B2.insert(tx5);
    B2.insert(tx6);
    B2.insert(tx7);

    DoubleList<block> chain;
    HashMap<std::string, nodeList<block>*> chainHash;

    chain.push_back(B1);
    chain.push_back(B2);

    chainHash.set("b1", chain.begin());
    chainHash.set("b2", chain.begin()->next);

    //std::cout << chainHash.get("b1")->data;
    std::cout << B1;

    return 0;
}

#include "BlockChain.h"

int main(int argc, char const *argv[])
{
    BlockChain bch;

    bch.createUser("fernando", "6077");
    bch.createUser("carlos", "1919");
    bch.createUser("alexis", "2020");

    bch.setTx("fernando", "6077", "carlos", 200);
    bch.setTx("fernando", "6077", "alexis", 2200);
    bch.setTx("fernando", "6077", "juan", 500);
    bch.setTx("fernando", "6077", "luis", 870);

    bch.viewMyBlock("fernando", "6077");
    std::cout << std::endl;
    bch.viewMyBlock("carlos", "1919");
    std::cout << std::endl;
    bch.viewMyBlock("alexis", "2020");
    std::cout << std::endl;

    std::cout << std::endl;
    bch.viewMyBlockAmount("fernando", "6077");

    std::cout << std::endl;
    bch.viewMyBlockDate("fernando", "6077");

    return 0;
}

#include "BlockChain.h"

int main(int argc, char const *argv[])
{
    BlockChain bch;

    bch.createUser("fernando", "6077");
    bch.createUser("carlos", "1919");
    bch.createUser("alexis", "2020");

    bch.setTx("fernando", "6077", "carlos", 200, "1657748880");
    bch.setTx("fernando", "6077", "alexis", 2200, "1656620824");
    bch.setTx("fernando", "6077", "juan", 500, "1645827356");
    bch.setTx("fernando", "6077", "luis", 870, "1645827359");

    bch.viewMyBlock("fernando", "6077");
    std::cout << std::endl;
    bch.viewMyBlock("carlos", "1919");
    std::cout << std::endl;
    bch.viewMyBlock("alexis", "2020");
    std::cout << std::endl;

    std::cout << std::endl;
    bch.viewMyBlockAmount("fernando", "6077");

    std::cout << std::endl;
    bch.viewMyBlockDate("fernando", "6077");

    return 0;
}
*/