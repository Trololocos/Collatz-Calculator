#pragma once
class mem_blocks { 
public:
	//linked list implementation .
	//Each node contains a binary array. I use an array of bytes instead of bits
	//because it is more efficient time-wise. If memory is a limiting factor an
	//std::vector<bool> could be used.
	
	struct node {
		uint8_t* value = nullptr;
		node* next = nullptr;
		~node() {
			delete[] value;
		}
	};
	// block_size =  2^n
	static const int n = 15;
	static const size_t block_size = 1<<n;


	mem_blocks() {
		head = new node;
		head->value = new uint8_t[block_size](); //0-initialized
		tail = head;
		}
	//mem_blocks(size_t size, uint8_t* value) {
	//	block_size = size;
	//	head = new node;
	//	head->value = value;
	//	tail = head;
	//}

	void add() { //Creates and links a new block of memory
		node* x = new node;
		x->value = new uint8_t[block_size]();
		tail->next = x;
		tail = x;
		block_count++;
	}
	node* operator[](size_t index) {
		if (index >= block_count) {
			std::string  error = "a";
			throw std::out_of_range("argument was {index} and block count was {block_count}");
		}
		
		node* ptr = head;
		for (size_t count = 0; ptr; ptr = ptr->next) {
			if (index == count++)
				return ptr;
		}


		if (block_count == 1) 
			return ptr;
		throw std::invalid_argument("Invalid index");	
	}
	~mem_blocks() {
		node* current = head;
		node* next = current;
		do {
			next = current->next;
			delete current;
			current = next;
		} while (next);
	}

	bool lookup(uint64_t x) { //Checks if a number has been set to true.
		return (fetch(x) == 1);
	}
	void set_mem(uint64_t x) {
		uint8_t& number = fetch(x);
		if (number == 0)[[likely]]
			number = 1;
		else if (number == (uint8_t)-1) {//create new block
			add();
			tail->value[x % block_size] = 1;
		}

	}
	//This swaps the first and last node
	void swap() { 
		tail->next = head;
		head = head->next;
		tail = tail->next;
		tail->next = nullptr;
		memset(tail->value,0,block_size);
		offset++;
	}

	uint8_t& fetch(uint64_t x) {
		size_t block = x>>n; // x/n should be the same as x>>n for the compiler.
        size_t dest = block - offset;
        if (block_count > dest) [[likely]] { 
            size_t index = x % block_size;
			uint8_t& dbg = (*this)[dest]->value[index];
			return dbg;
            return (*this)[dest]->value[index];
        }
		else {
			static uint8_t fail = -1;
			return fail;
	}		
	}
	node* head = nullptr;
	node* tail = nullptr;
	size_t block_count = 1;
	size_t offset = 0; //A count of how many times swap() has been called.

};