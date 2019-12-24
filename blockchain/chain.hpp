#include <string>
#include <unordered_map> 
#include "block.hpp"

class Chain {
  public:

    // chain constructor - takes in the initial 
    // difficulty that we start mining at
    Chain(int init_difficulty);

    // getter for current block
    Block* getCurrentBlock();

    // add a new with this data
    void addBlock();

  private:

    // current chain index
    uint32_t _cur_index;
    
    // current mining difficulty
    int _difficulty;

    // map of the entire chain - index => Block*
    std::unordered_map<int, Block*> _chainMap;

};
