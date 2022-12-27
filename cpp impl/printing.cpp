#include "3n+1.h"

//std::cout is extremely slow so I'm using printf
void print() {
	while (calculating) { // no mutexes needed because I don't need any sync
		printf("Calculated up to: %llu\n", maxCalc);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
void timer(int time) {
	auto epoch = std::chrono::steady_clock::now();

	while (calculating) {
		uint64_t prev = maxCalc;
		auto first = std::chrono::steady_clock::now();
		while ((maxCalc - prev) < time && calculating)
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		
		//it's done like this because I don't want to affect the calculation process.
		//if however I wanted to use multiple threads I could optimize this function.
		//It will always overshoot but it doesn't really matter.
		auto later = std::chrono::steady_clock::now();
		auto duration = later - first;
		std::cout << duration.count()/ 1000000 <<" ms. Iteration number: " <<maxCalc <<
			". Total time: " << (later-epoch).count() / 1000000000 << "s" << std::endl;
	}
}
void repr_blocks(mem_blocks& list) {
	auto epoch = std::chrono::steady_clock::now();
	char* const output = new char[1 << 14](); //Output string, 16k
	const int maxprint = 100; //prints n first blocks
	int delta = 0;
	while (calculating) {
		size_t size = list.block_count;
		std::vector<int> count(maxprint,0); //counts how many elements have been found in each block

		const char* separator = "###################################\n";
		////multiple calls to puts are expensive 
		// I make a big string that I print all at once:
		size_t i = 0;
		for (mem_blocks::node* current = list.head; current && i < maxprint ; current = current->next, i++) {
			if (i >= maxprint)
				break;
			for (size_t j = 0; j <= count.size(); j++)
				if (current->value[j]) {
					count[i]++;
				}
		}
		
		char buffer[132]; 
		for (int index = 0; (index < size) && (index < maxprint); index++)
		{
			sprintf(buffer, "%d block: %u\n", index, count[index]);
			strcat(output, buffer);
		}
		strcat(output, separator);
		puts(output);

		*output = {0}; //this should do the trick


		auto later = std::chrono::steady_clock::now();
		delta = maxCalc - delta;
		std::cout << "Iteration number: " << maxCalc << ". Total time: " << (later - epoch).count() / 1000000000 
			<< "s. Speed: " << delta << " calculations/s" << std::endl;
		delta = maxCalc;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	delete[] output;
 }