#include <iostream>
#include "chain.hpp"

int main() {

  // instantiate chain
  Chain* c = new Chain(5);
  std::cout << "Initial block mined. Hash: " << c->getCurrentBlock()->getHash().substr(0, 10) << "\n";

  // mine a few blocks
  for (int i = 0; i < 5; i++) {
    c->addBlock();
    std::cout << "Block " << c->getCurrentBlock()->getIndex() << " mined. Hash: " << c->getCurrentBlock()->getHash().substr(0, 10) << "\n";
  }
  return 0;
}