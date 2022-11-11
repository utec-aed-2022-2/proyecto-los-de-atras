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