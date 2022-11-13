#include "../base/BlockChain.h"

void test1()
{
    block B1(1);
    
    B1.insert({"a","b",9650.3,"1653617607"});
    B1.insert({"a","i",9657.3,"1653617696"});
    B1.insert({"a","j",9650.8,"1653617777"});

    std::cout << B1.search({"a","i",9657.3,"1653617696"}) << std::endl;

    B1.coutOrderByDate();
    B1.coutOrderByNumber();

    B1.coutMaxTxDate();
    B1.coutMinTxDate();
    B1.coutMaxTxNumber();
    B1.coutMinTxNumber();
}

void test2()
{
    Blockchain bch;

    bch.createUser("fernando", "meiniet");
    bch.createUser("carlos", "mono0winrate");
    bch.createUser("alexis", "trolleolasrankeds");
    bch.createUser("juan", "salesucambiodemalla");
    bch.createUser("juandiego", "unmilkable");
    bch.createUser("nicolas", "yaacaboelciclo");
    bch.createUser("aaron", "soyunaautomata");
    bch.createUser("luis", "abajoloshaitianos");

    bch.setTx("fernando", "meiniet", "carlos", 200);
    bch.setTx("fernando", "meiniet", "alexis", 2200, "1656620824");
    bch.setTx("fernando", "meiniet", "juan", 500, "1645827356");
    bch.setTx("fernando", "meiniet", "luis", 870, "1645827359");

    bch.setTx("carlos", "mono0winrate", "aaron", 568);
    bch.setTx("carlos", "mono0winrate", "luis", 98, "1656620824");
    bch.setTx("carlos", "mono0winrate", "alexis", 12, "1656620424");

    bch.setTx("luis", "abajoloshaitianos", "carlos", 200);
    bch.setTx("luis", "abajoloshaitianos", "aaron", 2200, "1638720040");

    bch.setTx("nicolas", "yaacaboelciclo", "carlos", 200);
    bch.setTx("nicolas", "yaacaboelciclo", "alexis", 2200, "1656620821");
    bch.setTx("nicolas", "yaacaboelciclo", "juandiego", 500, "1645827396");
    bch.setTx("nicolas", "yaacaboelciclo", "luis", 870, "1651343075");
    bch.setTx("nicolas", "yaacaboelciclo", "aaron", 568);
    bch.setTx("nicolas", "yaacaboelciclo", "carlos", 200);
    bch.setTx("nicolas", "yaacaboelciclo", "fernando", 2200, "1642303044");

    bch.setTx("aaron", "soyunaautomata", "nicolas", 938, "1657604037");

    bch.setTx("juandiego", "unmilkable", "luis", 908, "1657604937");
    bch.setTx("juandiego", "unmilkable", "carlos", 12, "1642303030");

    bch.setTx("juan", "salesucambiodemalla", "luis", 128, "1657604937");

    bch.setTx("luis", "abajoloshaitianos", "fernando", 9, "1642303030");

    bch.mineCascade("nicolas", "yaacaboelciclo");

    bch.viewAll();
}