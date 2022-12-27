#include "3n+1.h"

// It's extremely disappointing that after all of the effort I went through 
// to make this one happen it's so much slower than the naive approach. You live you learn.
void dynamic_approach(uint64_t x) { 
	mem_blocks list;

	calculating = true;
	//std::thread printer(repr_blocks, std::ref(list));
	std::thread printer(timer, 100000);
	//std::thread printer(print);
	for (uint64_t count = 2; count < x; count++)
	{
		uint64_t curr = count;
		uint64_t first = curr;
		while (curr >= first) {
			if (list.lookup(curr)) {
				break;
			}
			list.set_mem(curr);
			if (curr % 2)
				curr = curr * 3 + 1;
			else
				curr /= 2;
		}
		if ((first % mem_blocks::block_size) == 0) [[unlikely]] {

			list.swap();
		}

		maxCalc++;
	}
	calculating = false;
	printer.join();
}




