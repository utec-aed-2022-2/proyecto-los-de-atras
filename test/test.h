#include "../class/hashMap.h"
#include "../class/BPlusTree.h"
//#include "../class/Partial/BlockChain.h"
//#include "../class/Final/BlockChain.h"
#include "../function/BoyerMoore.h"

/*
void bpt_print(){
    print(this->root);
}

void print(nodeBPlus<T>* cursor)
{
    if (cursor != nullptr)
    {
        for (int i = 0; i < cursor->size; ++i)
        {
            std::cout << *cursor->data[i] << " ";
        }
        std::cout << "\n";

        if (!cursor->is_leaf)
        {
            for (int i = 0; i < cursor->size + 1; ++i)
            {
                print(cursor->children[i]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    double_list<int> a;
    a.push_back(1);
    a.push_back(2);

    double_list<int> b = a;

    for (int i = 0; i < b.size(); i++) { std::cout << b[i] << std::endl; }
    return 0;
}

int main(int argc, char const *argv[])
{
    hashMap<int, std::string> hm;
    std:: cout << hm[3];

    return 0;
}

int main(int argc, char const *argv[])
{
    hashMap<std::string, int>* h = new hashMap<std::string, int>;

    h->set("aaaa", 4);
    h->set("xd", 4);
    h->set("elpepe", 4);

    std::cout << h->get("xd");

    return 0;
}

int main(int argc, char const *argv[])
{
    BPlusTree<int> bpt1(3);
    bpt1.insert(9);
    bpt1.insert(5);
    bpt1.insert(1);
    bpt1.insert(7);
    bpt1.insert(4);
    bpt1.insert(6);
    print(bpt1.GetRoot());

    std::cout << std::endl;
    
    BPlusTree<std::string> bpt2(3);
    bpt2.insert("i");
    bpt2.insert("e");
    bpt2.insert("a");
    bpt2.insert("g");
    bpt2.insert("d");
    bpt2.insert("f");
    print(bpt2.GetRoot());

    return 0;
}

int main(int argc, char const *argv[])
{
    blockchain xd;

    xd.addBlock();
    xd.addBlock();
    xd.addBlock();
    xd.addBlock();

    xd.setData(1, {"a", "b", 100, "1633227430000"});
    xd.setData(3, {"a", "c", 200, "1633227430000"});
    xd.setData(3, {"w", "a", 300, "1633227430000"});
    xd.setData(4, {"z", "g", 5500, "1633227430000"});
    xd.setData(1, {"a", "h", 200, "1633227430000"});
    xd.setData(1, {"q", "j", 1200, "1633227430000"});

    xd.minechain(3);

    xd.setData(3, {"w", "a", 3022220, "1633227430000"});

    xd.addBlock();

    std::cout << xd;
}

int main(int argc, char const *argv[])
{
    hashMap<string, nodeList<int>*> hm;
    
    doubleList<int> dl;


    dl.push_back(3);

    for (int i = 0; i < dl.size(); i++)
    {
        cout << dl[i] << endl;
    }

    hm.set("begin", dl.begin());

    cout << &hm.get("begin")->data << endl;
    cout << &dl[0] << endl;
    
    return 0;
}

int main(int argc, char const *argv[])
{
    blockchain xd;

    xd.addBlock();
    xd.addBlock();
    xd.addBlock();

    xd.setData(1, {"fernando", "carlos", 100, "1633227430000"});
    xd.setData(2, {"alexis", "aaron", 200, "1633227430000"});
    xd.setData(2, {"alexis", "fernando", 300, "1633227430000"});
    xd.setData(3, {"carlos", "aaron", 5500, "1633227430000"});
    xd.setData(3, {"carlos", "fernando", 200, "1633227430000"});
    xd.setData(3, {"carlos", "juan", 1200, "1633227430000"});

    hashMap<string, nodeList<block*>*> hm;

    // poner chain publico solo para prueba
    
    hm.set("fernando", xd.chain.begin());
    hm.set("alexis", xd.chain.begin()->next);
    hm.set("carlos", xd.chain.begin()->next->next);

    xd.setData(2, {"alexis", "juan", 1000, "1633227430000"});

    for (int i = 0; i < hm.get("alexis")->data->data.size(); i++)
    {
        cout << hm.get("alexis")->data->data[i] << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    std::string texto = "hola mi amor, hola como estashola";
    std::string patron = " ";
    std::cout << boolBoyerMoore(texto, patron) << std::boolalpha;

    return 0;
}

int main(int argc, char const *argv[])
{
    transaction xd1{"cr7", "messi", 233.3, "c"};
    transaction xd2{"messi", "cr7", 233.3, "b"};
    // si tienen el mismo valor de monto, será mayor la que se haya hecho antes(fecha)
    std::cout << (xd1 < xd2);
    
    return 0;
}

int main(int argc, char const *argv[])
{

    transaction tx1("Skyndu", "Puce", 8822.42, "1643003849");
    transaction tx2("Bigtax", "Granite", 1822.57, "1655979226");

    std::cout << tx1 << std::endl;
    std::cout << tx2 << std::endl;

    std::cout << (tx1.operator< <float>(tx2)) << std::endl;
    std::cout << (tx1.operator< <string>(tx2)) << std::endl;
    std::cout << (tx2< (tx1)) << std::endl;

    return 0;
}

int main(int argc, char const *argv[])
{

    transaction* tx1 = new transaction("Skyndu", "Puce", 8822.42, "1643003849");
    transaction* tx2 = new transaction("Bigtax", "Granite", 1822.57, "1655979226");
    transaction* tx3 = new transaction("Realcube", "Goldenrod", 4323.1, "1636873090");

    BPlusTree<transaction*> orderbyAmount(3);

    orderbyAmount.insert(tx1);
    orderbyAmount.insert(tx2);
    orderbyAmount.insert(tx3);

    orderbyAmount.bpt_print();

    tx2->string1 = "fernando";
    std::cout << std::endl;

    orderbyAmount.bpt_print();

    return 0;
}
*/