#include "BlockChain.h"

using namespace std;

int main(int argc, char* argv[]) {
	BlockChain bChain = BlockChain();

	cout << "Genesis..." << endl;
	bChain.AddGenesis();

	cout << "block 1..." << endl;
	bChain.AddBlock(Block(1, ""));

	cout << "block 2..." << endl;
	bChain.AddBlock(Block(2, ""));

	cout << "block 3..." << endl;
	bChain.AddBlock(Block(3, ""));

	cout << "block 4..." << endl;
	bChain.AddBlock(Block(4, ""));
	
	cout << "block 5..." << endl;
	bChain.AddBlock(Block(5, ""));

	cout << "block 6..." << endl;
	bChain.AddBlock(Block(6, ""));

	cout << "block 7..." << endl;
	bChain.AddBlock(Block(7, ""));

	cout << "block 8..." << endl;
	bChain.AddBlock(Block(8, ""));
	
	cout << "block 9..." << endl;
	bChain.AddBlock(Block(9, ""));

	cout << "block 10..." << endl;
	bChain.AddBlock(Block(10, ""));

	bChain.PrintBlocks();


	bChain.Datablock();
	
	bChain.Mineblock();


	bChain.Datablock();
	
	bChain.Mineblock();
	return 0;
}
