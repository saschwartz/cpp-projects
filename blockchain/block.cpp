#include <ctime>
#include <string>
#include <iostream>
#include "sha256.hpp"
#include "block.hpp"

// block constructor
Block::Block(uint32_t index): prev_hash(""), _block_index(index), _hash("") {};

// calculate a hash using sha256
// hash input comprises of current block index, system time, 
// block data, the hash incremement, and the previous hash
std::string Block::_calculateHash() const {
    return sha256(
      std::to_string(_block_index) +
      std::to_string(time(nullptr)) +
      std::to_string(_hash_increment) +
      prev_hash
    );
}

// getters for private variables _hash and _block_index
std::string Block::getHash() const {
  return _hash;
}
uint32_t Block::getIndex() const {
  return _block_index;
}

// find a hash with at least <difficulty> first 
// digits set to 0
// see https://github.com/saschwartz/schoolwork/blob/master/fall19/cs121/hw6/hw6.pdf
// for an anologous problem
// should require roughly 2^{hashlength} / (hashlength - difficulty) random samples
// before we mine a satisfying hash
void Block::mineBlock(int difficulty) {
  std::string s = "";
  for (int i = 0; i < difficulty; i++) {
    s += "0";
  }

  while (true) {
    std::string hash = _calculateHash();
    if (hash.substr(0, difficulty).compare(s) == 0) {
      _hash = hash;
      return;
    } else {
      _hash_increment += 1;
    }
  }
}