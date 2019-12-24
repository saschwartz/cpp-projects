#include <string>
#include <unordered_map> 
#include "block.hpp"

class Chain {
  public:

    // chain constructor - takes in the initial 
    // difficulty that we start mining at as well as
    // how often to increase our difficulty
    Chain(int init_difficulty, int increase_per_nblocks=5);

    // getter for current block
    Block* getCurrentBlock();

    // add a new with this data
    void addBlock();

  private:

    // current chain index
    uint32_t _cur_index;
    
    // current mining difficulty
    int _difficulty;

    // difficulty increase - escalates every increase_per_nblocks blocks
    int _increase_per_nblocks;

    // map of the entire chain - index => Block*
    std::unordered_map<int, Block*> _chainMap;

};
