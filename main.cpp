#include "tests/test.h"
#include "classes/bplustree.h"

template <typename T>
void print(nfbpt::node<T>* cursor)
{
    // You must NOT edit this function.
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; ++i) {
            std::cout << cursor->data[i] << " ";
        }
        std::cout << "\n";

        if (!cursor->is_leaf) {
            for (int i = 0; i < cursor->size + 1; ++i) {
                print(cursor->children[i]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    bplustree<int> bpt1(3);
    bpt1.insert(9);
    bpt1.insert(5);
    bpt1.insert(1);
    bpt1.insert(7);
    bpt1.insert(4);
    bpt1.insert(6);
    print(bpt1.GetRoot());

    std::cout << std::endl;
    
    bplustree<std::string> bpt2(3);
    bpt2.insert("i");
    bpt2.insert("e");
    bpt2.insert("a");
    bpt2.insert("g");
    bpt2.insert("d");
    bpt2.insert("f");
    print(bpt2.GetRoot());

    return 0;
}