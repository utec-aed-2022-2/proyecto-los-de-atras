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
    bplustree<int> bpt(3);
    bpt.insert(9);
    bpt.insert(5);
    bpt.insert(1);
    bpt.insert(7);
    bpt.insert(4);
    bpt.insert(6);

    print(bpt.GetRoot());

    return 0;
}