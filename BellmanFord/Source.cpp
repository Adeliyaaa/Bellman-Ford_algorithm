#include "Bellman–Ford_algorithm.h"

int main() {
	BellmanFord algorithm;
	algorithm.set_data("input.txt");
	algorithm.find_way(5, 9);
	system("pause");
	return 0;
}
/*
*/