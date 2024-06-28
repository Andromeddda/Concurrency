#include <iostream>
#include <atomic>

using namespace std;

int main(void) {
	atomic<int> ticket = atomic<int>(0);
	int my_ticket = ticket.fetch_add(1);

	cout << my_ticket << '\n';
	cout << ticket.load() << '\n';
	return 0;
}