// DynamicProg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int f() 
{
	static int i = 0;

	std::cout << i << " -> ";

	++i;

	std::cout << i << "\n";

	return i;

}

/*int main()
{
	std::vector<std::thread> v_t(10);

	for (auto& t: v_t)
	{
		t = std::thread([] {
			for (auto n = 0; n < 10; n++)
				f();
		});
	}

	for (auto& t : v_t)
		t.join();

	std::cin.get();
}*/


void manually_iterate_bits(int arg)
{
	std::string s;
	auto val = arg;
	while (val > 0)
	{
		auto newval = val % 2;

		if (newval > 0)
		{
			s = "1" + s;
		}
		else
		{
			s = "0" + s;
		}

		if (val == 0)
			break;

		val = val >> 1;
	}

	std::cout << " ==> " << s;

}

void write_bitset_stream(int val) {
	
	std::bitset<16> b(val);

	std::cout << val << "\t => " << b;
	manually_iterate_bits(val);

	std::cout << std::endl;
}

void bitIterator() {

	std::vector<int> v(10);
	std::srand(1);
	std::generate(v.begin(), v.end(), std::rand);

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl;

	for (auto e : v) { write_bitset_stream(e); }

	std::cin.get();
	
}

bool is_unique_char(char * arg) {

	std::cout << "\nargument is : " << arg << std::endl;

	char* it = arg;
	size_t arglen = strlen(arg);

	char* end = arg + arglen;

	std::cout << "arg address: " 
				<< static_cast<void *>(arg) 
				<< " \titerator address: " 
				<< static_cast<void *>(it) 
				<< "\tchar ending address: " 
				<< static_cast<void *>(end) << std::endl;

	int store = 0;
	while (it < end) {
		int intval = *it;
		std::cout << *it << " integer representation is: " << intval;

		if (store & (1 << intval))
		{
			std::cout << "store already contains: " << intval << std::endl;
			return false;
		}
		else {
			std::cout << "adding " << intval << " to store" << std::endl;;
			store |= (1 << intval);
		}

		++it;
	}

	std::cout << std::endl;
	return true;



}

void reverse_char(char* arg)
{
	char* front = const_cast<char *>(arg);
	char* end = arg + strlen(arg) - 1;

	/*while (*end) {
		++end;
	}*/

	std::cout << "char before swap: " << arg << " starting char: " << *front << " ending char: " << *end << "\t";
	while (front < end)
	{
		/*char temp = *front;
		*front = *end;
		*end = temp;
		++front; --end;*/
		std::swap(*(front++), *(end--));
	}

	std::cout << "char after swap: " << arg << std::endl;;
}

void remove_duplicate(char* arg)
{
	if (!arg)
		return;
	std::cout << std::endl << "arg " << arg;

	int tail = 0;
	int arglen = strlen(arg);

	char* front = arg;
	char* end = arg + arglen;
	int store = 0;

	while (*front) {
		int val = *front;

		if ((store & (1 << val)) > 0) {
			int distance = end - front;
			memcpy(front, front + 1, distance) ;
			*(front + distance) = '\0';
			front--;
			end = arg + strlen(arg);
			std::cout << "\n\tmemcopy: " << arg;
		}
		else
		{
			store |= (1 << val);
		}
		++front;
	}


}

void run_removedup() {
char arg1[] = "abcdd";
	char arg2[] = "ababaa";
	char arg3[] = "aaaaaaaa";
	char arg4[] = "agagagagagagag";
	remove_duplicate(arg1);
	remove_duplicate(arg2);
	remove_duplicate(arg3);
	remove_duplicate(arg4);
	remove_duplicate(nullptr);
}

unsigned get_largest_prime_btwn(unsigned start, unsigned end)
{
	unsigned max = 0;
	for (unsigned i = start; i < end; i++) {

		unsigned iovr_two = i / 2;
		for (unsigned y = 2; y <= iovr_two; y++)
		{
			
			if (i % y == 0)
			{
				break;
			}

			if (y == iovr_two)
			{
				max = i;
			}
		}
	}
	std::cout << "\nPrime: " << max << std::endl;
	return max;
}

void rabin_karp_match(char* text, char* pattern, unsigned d_ary, unsigned prime)
{
	std::cout << "\n Inside Algo";
	std::vector<int> match_location;
	size_t n = strlen(text) - 1 ;
	size_t m = strlen(pattern) - 1;
	
	int pw = std::pow(d_ary, static_cast<int>(m - 1)) ;

	int h =  pw % prime;

	for (int i = 0; i < m - 1; i++)
	{
		h = (h * d_ary) % prime;
	}

	int p = 0;
	int t = 0;

	for (int i = 0; i <= m; i++)
	{
		p = (d_ary * p + pattern[i]) % prime;
		t = (d_ary * t + text[i]) % prime;
	}

	for (int s = 0 ; s <= n - m; s++)
	{
		if (p == t )
		{
			std::cout << "\npotential match found:: " << t << "  at location " << s << "\t " << (text + s) << std::endl;
			match_location.push_back(s);
		}

		if (s < n - m) {
			t = (d_ary * (t - text[s] * h) + text[s + m]) % prime;

			//if (t < 0) t = t + prime;
		}
	}
}
void run_rabin_karp()
{
	char* text = " this is a very ary long drowsy day in the beautiful land of Africa. Browsy common!";
	char* pattern = "owsy";

	std::cout << "Rabin Karp Algorithm.";
	
	rabin_karp_match(text, pattern, 256,  get_largest_prime_btwn(10, 103));

}

void main1()
{
	/*std::cout << "app starting\n";
	char arg1[] = "fiuh;nwknl;ga";
	reverse_char(arg1);
	char arg2[] = "poilkjewmhuqs";
	reverse_char(arg2);*/
	
	//run_rabin_karp();
	int v = 1U;
	int n = (v << 6);
	auto v1 = (n - 1);

	printf("v is %d , n  : %d \nv1 : %d", v, n, v1);

	std::cin.get();
}

void * create_malloc(size_t size_byte, size_t alignment) {

	void * p1;
	void ** p2;

	int offset = alignment - 1 + sizeof(void *);

	if ((p1 = (void *)malloc(size_byte + offset)) == nullptr) return nullptr;

	p2 = (void **)(((size_t)(p1) + offset) & ~(alignment - 1));
	p2[-1] = p1;
	return p2;
}

void free_malloc(void * pt) {
	free(((void **)pt)[-1]);
}


void mainold()
{
	std::cout << "custom malloc" << std::endl;

	void * var = (void *)create_malloc(1000, 128);

	struct {
		char * title;
		int age;
	} currentNode = {};

	std::cout << "Address:\t" << &var << "\nPointer:\t" << var << "\nValue:\t" << var << std::endl;

	currentNode.title = "tout le monde boss";
	currentNode.age = 986;

	std::cout << "Address:\t" << &var << "\nPointer:\t" << var << "\nValue:\t" << var << std::endl;

	memccpy(var, &currentNode, 0, sizeof currentNode);

	free_malloc(var);

	std::cout << "Address:\t" << &var << "\nPointer:\t" << var << "\nValue:\t" << var << std::endl;
}