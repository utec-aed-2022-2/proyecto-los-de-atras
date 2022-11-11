#include "ui/Gui.h"

int main(int argc, char const *argv[]) {
    BlockChain bch("./MOCK_DATA_DEMO2.csv");
    auto* gui = new Gui();
    if (gui->initialize(&bch)) {
        gui->runLoop();
    }
    // bch->save() // TODO: que guarde la nueva information en los archivos correspondientes
    delete gui;

//    bch.setTx("fernando", "6077", "carlos", 200, "1657748880");
//    bch.setTx("fernando", "6077", "alexis", 2200, "1656620824");
//    bch.setTx("fernando", "6077", "juan", 500, "1645827356");
//    bch.setTx("fernando", "6077", "luis", 870, "1645827359");
//
//    bch.viewMyBlock("fernando", "6077");
//    std::cout << std::endl;
//    bch.viewMyBlock("carlos", "1919");
//    std::cout << std::endl;
//    bch.viewMyBlock("alexis", "2020");
//    std::cout << std::endl;
//
//    std::cout << std::endl;
//    bch.viewMyBlockAmount("fernando", "6077");
//
//    std::cout << std::endl;
//    bch.viewMyBlockDate("fernando", "6077");

    return 0;
}
