#include <iostream>
#include <vector>
#include <algorithm>
#include "HeapManager.h"
using namespace std;



int main() {
    // Allocate a buffer to use as the heap.
    cout << "Enter Buffer Size: ";
    int buffersize; cin >> buffersize;
    char buffer[buffersize];
    HeapManager heap(buffer, buffersize);
    
    int sum = 0;
    
    cout << "---------------------------------- Controls----------------------------------" << '\n';
    cout << " Exit : -1 , Allocate : 1 , DeAllocate : 0 , Storage Description : 2 " << '\n';
    cout << "-----------------------------------------------------------------------------" << '\n';
    
    vector<int*> storage;
    vector<int> blocksizes;
    
	while(1){
		int choice; cin >> choice;
		if(choice == -1){
			break;
		}else if(choice == 1){
			cout <<'\n' <<  "------------------------------Memory Allocation------------------------------" << '\n';
			cout << "Enter Block size : ";
			
			int size; cin >> size;
			int* ptr = static_cast<int*>(heap.allocate(size));
		    if (ptr != nullptr) {
		    	sum += size;
		        std::cout << "Allocated block of size " << size << " at address " << ptr << std::endl;
		        cout << "BUFFER MEMORY LEFT : " << buffersize -sum << "\n\n";
		        storage.push_back(ptr);
		        blocksizes.push_back(size);
		    }else{
		    	std::cout << "Failed to allocate block of size "<< size << std::endl;
		    	cout << "BUFFER MEMORY LEFT : " << buffersize -sum << "\n\n";
			}
			cout <<'\n' << "------------------------------------------------------------------------------" << '\n';	
		}else if(choice == 0){
			cout <<'\n' <<  "-----------------------------Memory De-Allocation----------------------------" << '\n';
			cout << "Enter Block Number to De-Allocate : ";
			int blocknum; cin >> blocknum;
			if(blocknum > storage.size()){
				cout << "ERROR!! Wrong Block Number GIVEN" << '\n';
			}else{
				sum -= blocksizes[blocknum - 1];
				heap.deallocate(storage[blocknum - 1] , blocksizes[blocknum - 1] );
				cout << "Block " << blocknum << " Removed Successfully" << '\n';
				storage.erase(storage.begin()+ blocknum - 1);
				blocksizes.erase(blocksizes.begin()+ blocknum - 1);
			}
			cout <<'\n' << "------------------------------------------------------------------------------" << '\n';	
		}else{
			cout <<'\n' <<  "------------------------------Memory Description-----------------------------" << '\n';
			cout << "Storage Description" << '\n';
			cout << "Storage Capacity : " << buffersize << '\n';
			cout << "Occupied Storage : " << sum << '\n';
			cout << "Available Memory : " << buffersize - sum << '\n';
			
			if(storage.size() > 0){
				for(int i = 0 ; i < storage.size() ; i ++){
					cout << "Block " << i+1 << " of Size " <<blocksizes[i] <<  " Allocated at : " << storage[i] << '\n';
				}
			}else{
				cout << "!! Storage is EMPTY !!" << '\n';
			}
			cout <<'\n' << "------------------------------------------------------------------------------" << '\n';
		}
	}

     heap.deallocate(buffer,buffersize);

    return 0;
}
