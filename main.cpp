#include "Blockchain.h"
#include "gui.h"

void test()
{
    Blockchain bch;

    bch.createUser("fernando", "meiniet");
    bch.createUser("carlos", "mono0winrate");
    bch.createUser("alexis", "trolleolasrankeds");
    bch.createUser("juan", "salesucambiodemalla");
    bch.createUser("nicolas", "yaacaboelciclo");
    bch.createUser("aaron", "soyunaautomata");
    bch.createUser("luis", "abajoloshaitianos");

    bch.setTx("nicolas", "yaacaboelciclo", "alexis", 2200, "1656620821");
    bch.setTx("nicolas", "yaacaboelciclo", "luis", 870, "1651343075");
    bch.setTx("nicolas", "yaacaboelciclo", "fernando", 2200, "1642303044");
    bch.setTx("nicolas", "yaacaboelciclo", "juan", 3000, "1668809947");
    bch.setTx("nicolas", "yaacaboelciclo", "juan", 223, "1668815885");
    bch.setTx("nicolas", "yaacaboelciclo", "luis", 10000, "1668817671");
    bch.setTx("nicolas", "yaacaboelciclo", "fernando", 6400, "1668817968");

    bch.mineCascade("nicolas", "yaacaboelciclo");
    bch.myTxsDateRange("nicolas", "yaacaboelciclo", "1651324210", "1668799671");
//    bch.myTxsDateRange("nicolas", "yaacaboelciclo", "1656600000", "1668754242", "papa.txt");
//    for (int i = 0; i < txs1.SIZE(); i++) { std::cout << *txs1[i] << std::endl; }
//    for (int i = 0; i < txs2.SIZE(); i++) { std::cout << *txs2[i] << std::endl; }
}

int main(int argc, char const *argv[]) {
    auto* blockchain = new Blockchain("./assets/users/users.txt", "./assets/users/transactions.txt");
    auto* gui = new Gui;
    if (gui->initialize(blockchain)) {
        gui->runLoop();
    }
    delete gui;
    return 0;
}
