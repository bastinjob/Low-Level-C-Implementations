#include <iostream>
#include <cstring>
#include <cassert>

class MemPool{

private:
    static const int POOL_SIZE = 1024;
    static constexpr int  BLOCK_SIZE = 32;
    static constexpr int BLOCK_COUNT = POOL_SIZE/BLOCK_SIZE;

    char memory[POOL_SIZE];
    bool allocated[BLOCK_COUNT];

    MemPool(){
        std::memset(allocated, false, sizeof(allocated));
    }

    ~MemPool() = default;



public:
    static MemPool& getInstance(){
        static MemPool instance;
        return instance;
    }

    MemPool(const MemPool&) = delete;
    MemPool& operator=(const MemPool&) = delete;

    void* allocate(){

        for(int i =0; i<BLOCK_COUNT; i++){
            if(!allocated[i]){
                allocated[i] = true;
                return memory + (i*BLOCK_SIZE);

            }
        }
        return nullptr;
    }

    void deallocate(void* ptr){
        int offset = static_cast<char*>(ptr) - memory;

        assert(offset%BLOCK_SIZE==0 && offset<POOL_SIZE);

        int index = offset/BLOCK_SIZE;
        assert(allocated[index]);

        allocated[index] = false;
    }

    void debug() const {
        std::cout << "Memory Pool State:\n";
        for (int i = 0; i < BLOCK_COUNT; i++) {
            std::cout << (allocated[i] ? "[X]" : "[ ]");
        }
        std::cout << std::endl;
    }

};

int main(){
    MemPool& pool = MemPool::getInstance();

    void* ptr1 = pool.allocate();
    void* ptr2 = pool.allocate();
    void* ptr3 = pool.allocate();


    pool.debug();


    pool.deallocate(ptr2);
    pool.debug();

    return 0;


}