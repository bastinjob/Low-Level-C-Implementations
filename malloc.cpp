//Design a heap
//Keep track of allocated and free memory using a free list
//Enusre allocations respect memory alignment requirements
//Free: allow releasing memory for reuse


//Heap: using a large static array
//Linked List to manage free and allocated blocks

#include <iostream>
#include <cstddef>
#include <cstring>

//simulated heap size
constexpr size_t HEAP_SIZE = 1024*1024; // 1 MB

//heap represented as a static array
static char heap[HEAP_SIZE];


//Free list node

struct Block{

    size_t size;
    bool is_free;
    Block* next;

};

//head of the free list
static Block* free_list = nullptr;

void initialize_heap(){

    if (!free_list){
        free_list = reinterpret_cast<Block*>(heap);
        free_list->size = HEAP_SIZE - sizeof(Block);
        free_list->is_free = true;
        free_list->next = nullptr;
    }
}


void* my_malloc(size_t size){
    //Traverse the freelist to find a free block
    //split the block if necessary
    //mark the block as allocated and return a pointer to the usable memory


    Block* current = free_list;
    Block* previous = nullptr;

    while(current){
        if(current->is_free && current->size >= size){
             //split the block if it's larger than needed

             if (current->size > size + sizeof(Block)){
                Block* new_block = reinterpret_cast<Block*>(reinterpret_cast<char*>(current) + sizeof(Block) + size);
                
                new_block->size = current->size - size - sizeof(Block);
                new_block->is_free = true;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;

             }
        current->is_free = false;
        return reinterpret_cast<void*>(reinterpret_cast<char*>(current)+sizeof(Block));

        }

     previous = current;
     current = current->next;
    }

    return nullptr;


}