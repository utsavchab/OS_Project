#include <iostream>
#include <vector>
#include <algorithm>
#include "HeapManager.h"
using namespace std;



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
