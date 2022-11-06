#include "../class/hashMap.h"
#include "../class/BPlusTree.h"
#include "../class/Partial/BlockChain.h"

/*
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
*/