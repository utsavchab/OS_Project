#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class HeapManager {
	private:
    struct Block {
        void* ptr;
        size_t size; // size of  each block

        bool operator<(const Block& other) const { // operator overloading
            return ptr < other.ptr;
        }
    };

    void* m_buffer; // buffer storage
    size_t m_size; // buffer size
    std::vector<Block> m_free_blocks; // totals blocks allocated

    static bool compare_blocks(const Block& a, const Block& b) {
        return a.ptr < b.ptr;
    }
    
public:
    HeapManager(void* buffer, size_t size){
        m_buffer = buffer;
        m_size = size;
        m_free_blocks.push_back(Block{buffer, size});
    }

    void* allocate(size_t size) {


        // Search the list of free blocks for a block of sufficient size.
        for (size_t i = 0; i < m_free_blocks.size(); ++i) {
            Block& block = m_free_blocks[i];
            if (block.size >= size) { 
                // If the block is larger than the requested size, split it.
                if (block.size > size) { // breaking the extra block
                    void* new_block_ptr = static_cast<char*>(block.ptr) + size;
                    size_t new_block_size = block.size - size;
                    Block new_block{new_block_ptr, new_block_size};
                    m_free_blocks.insert(m_free_blocks.begin() + i + 1, new_block);
                }

                // Allocate the block and remove it from the free list.
                void* allocated_block_ptr = block.ptr;
                m_free_blocks.erase(m_free_blocks.begin() + i); 
                return allocated_block_ptr;
            }
        }

        // If we didn't find a free block, return nullptr.
        return nullptr;
    }

    void deallocate(void* ptr) {
        // Add the block to the free list.
        Block block{ptr, 0};
        auto it = std::lower_bound(m_free_blocks.begin(), m_free_blocks.end(), block, compare_blocks);
        m_free_blocks.insert(it, block);

        // Merge adjacent free blocks.
        for (size_t i = 0; i < m_free_blocks.size() - 1; ++i) {
            Block& curr = m_free_blocks[i];
            Block& next = m_free_blocks[i + 1];
            if (static_cast<char*>(curr.ptr) + curr.size == next.ptr) {
                curr.size += next.size;
                m_free_blocks.erase(m_free_blocks.begin() + i + 1);
            }
        }
    }


};

int main() {
    // Allocate a buffer to use as the heap.
    cout << "Enter Buffer Size: ";
    int buffersize; cin >> buffersize;

	cout << "Enter Total Number of Entries: " << '\n';
    
    char buffer[buffersize];
    int num; cin >> num;
    HeapManager heap(buffer, buffersize);
    int sum = 0;
    for(int i = 1; i <= num; i ++){
    	cout << "Enter Block " << i << " size : ";
//    	int size;
    	int size; cin >> size;

		
    // Create a heap manager with the buffer.
	  
	
	    // Allocate a block of 100 bytes.
	    int* ptr = static_cast<int*>(heap.allocate(size));
	    if (ptr != nullptr) {
	    	sum += size;
	        std::cout << "Allocated block of size " << size << " at address " << ptr << std::endl;
	        cout << "BUFFER MEMORY LEFT : " << buffersize -sum << "\n\n";
	    }else{
	    	std::cout << "Failed to allocate block of size "<< size << std::endl;
	    	cout << "BUFFER MEMORY LEFT : " << buffersize -sum << "\n\n";
		}
	
	    // Attempt to allocate a block of 1KB, which should fail.
		
	}
    // Deallocate the block of memory.
     heap.deallocate(buffer);

    return 0;
}
