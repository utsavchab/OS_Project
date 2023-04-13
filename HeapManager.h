

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
