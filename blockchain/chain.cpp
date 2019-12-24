#include <string>
#include <iostream>
#include "chain.hpp"

// constructor creates an initial block on startup
Chain::Chain(int init_difficulty): _cur_index(0), _difficulty(init_difficulty)  {
  Block* init_block = new Block(_cur_index);
  init_block->mineBlock(_difficulty);
  _chainMap[_cur_index] = init_block;
}

// to add a block, create a new block, mine it, and increment the index.
// the block is added to the chainMap that tracks the whole chain.
void Chain::addBlock() {
  _cur_index += 1;

  Block* new_block = new Block(_cur_index);
  new_block->prev_hash = _chainMap[_cur_index - 1]->getHash();
  new_block->mineBlock(_difficulty);
  _chainMap[_cur_index] = new_block;
}

// return pointer to current block from _chainMap
Block* Chain::getCurrentBlock() {
  return _chainMap[_cur_index];
}