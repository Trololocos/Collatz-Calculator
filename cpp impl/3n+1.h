#pragma once
#include <thread>   
#include <cstring>
#include <stdlib.h>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include "data structures.h"
extern uint64_t maxCalc;
extern bool calculating; //a switch for the printing functions.
void print(); //every tick of the function prints where the calculation is at.
void timer(int n); //prints how long (roughly) it takes to do n calculations.
void repr_blocks(mem_blocks& list); //prints a visual representation of the blocks

void naive_approach(uint64_t x);
void less_redundant_approach(uint64_t x);
void dynamic_approach(uint64_t x);
