#include "3n+1.h"

void naive_calculation(uint64_t x) {
	uint64_t first = x;
	while (x > 1) {
		uint64_t prev = x;
		if (x % 2)
			x = x * 3 + 1;
		if (x < prev) {
			printf("overflow detected when x = %llu in iteration number %llu", prev, first);
			exit(EXIT_FAILURE);
		}
		else
			x /= 2;
	}

	maxCalc++;
}

void naive_approach(uint64_t max) {

	calculating = true;
	std::thread printer(timer, 100000);
	for (int i = 0; i < max; i++)
		naive_calculation(i);
	calculating = false;
	printer.join();
}

void less_redundant_calculation(uint64_t x) {
	uint64_t first = x;
	while (x >= first) { //Instead of calculating until x = 1 calculate until x > the starting value
		uint64_t prev = x;
		if (x % 2)
			x = x * 3 + 1;
		if (x < prev)[[unlikely]] {
			printf("overflow detected when x = %llu in iteration number %llu", prev, x);
			exit(EXIT_FAILURE);
		}
		else
			x /= 2;
	}
	maxCalc++;
}
void less_redundant_approach(uint64_t max) { //Between 60 - 90 times faster for small numbers

	calculating = true;
	std::thread printer(timer,100000);
	for (int i = 2; i < max; i++)
		less_redundant_calculation(i);
	calculating = false;
	printer.join();
}