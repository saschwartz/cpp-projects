#include <string>

class Block{
  public:

    // block constructor - takes block index
    Block(uint32_t index);

    // hash of previous block
    std::string prev_hash;

    // getters for private variables _hash and _block_index
    // const keyword means it cannot modify any vars in the class
    std::string getHash() const;
    uint32_t getIndex() const;

    // method to mine this block (calculate a correct
    // block hash satisfying the required difficulty level)
    void mineBlock(int difficulty);

  private:

    // steadily incremement to calculate a new hash
    // until we mine the block
    uint32_t _hash_increment;

    // index of the block within the chain
    uint32_t _block_index;

    // calculate a hash using sha256
    // const keyword means it cannot modify any vars in the class
    std::string _calculateHash() const;

    // this block's hash
    std::string _hash;
};
