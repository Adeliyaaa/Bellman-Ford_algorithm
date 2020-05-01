#pragma once
#include <fstream>
#include "outer_list.h"

struct edge {
	int first_vertex, scnd_vertex, price;
};

class BellmanFord
{
private:
	int num_of_cities, num_of_edges;
	outer_list<List<char>> city;
	List<edge> list_of_edges;
	const int INF = 1000000000;
public:
	BellmanFord() {
		num_of_cities = 0;
		num_of_edges = 0;
	}

	//getting data from the file
	void set_data(string filename)
	{
		if (!city.isEmpty()) {
			city.clear();
			list_of_edges.clear();
		}
		ifstream f(filename);
		if (!f.is_open())
			throw runtime_error("File is not found");
		List<char> temp_city;
		edge temp_edge;
		char symbol;
		bool second_city = false;
		while (!f.eof()) {
			f >> noskipws >> symbol;
			if (f.eof())
				break;
			if (symbol == ';')
			{
				f >> symbol;
				if (!city.contains(temp_city))
				{
					num_of_cities++;
					city.push_back(temp_city);
					if (!second_city)
						temp_edge.first_vertex = city.get_index(temp_city);
					else
						temp_edge.scnd_vertex = city.get_index(temp_city);
					temp_city.reset();
				}
				else {
					if (!second_city)
						temp_edge.first_vertex = city.get_index(temp_city);
					else
						temp_edge.scnd_vertex = city.get_index(temp_city);
					temp_city.clear();
				}
				if (!second_city) {
					second_city = true;
				}
				else {
					if (symbol == 'N') {
						temp_edge.price = INF;
						while (symbol != '\n' && !f.eof() && symbol != ';')
							f >> symbol;
					}
					else {
						f.unget();
						f >> temp_edge.price;
						f >> symbol;
					}
					list_of_edges.push_back(temp_edge);
					int temporary = temp_edge.first_vertex;
					temp_edge.first_vertex = temp_edge.scnd_vertex;
					temp_edge.scnd_vertex = temporary;
					f >> symbol;
					if (symbol == 'N') {
						temp_edge.price = INF;
						while (symbol != '\n' && !f.eof() && symbol != ';')
							f >> symbol;
					}
					else {
						f.unget();
						f >> temp_edge.price;
					}
					list_of_edges.push_back(temp_edge);
					while (symbol != '\n' && !f.eof())
						f >> symbol;
					second_city = false;
					continue;
				}
			}
			temp_city.push_back(symbol);
		}
		num_of_edges = list_of_edges.get_size();
		f.close();
	}
		
	void find_way(size_t start, size_t destination) {
		if (city.isEmpty())
			throw runtime_error("Data is not set");
		if (start < 0 || destination < 0 || start > num_of_cities - 1 || destination > num_of_cities - 1)
			throw invalid_argument("Number of city is incorrect");
		List<int> distance(num_of_cities, INF);
		List<int> predecessor(num_of_cities, -1);
		distance.set(start, 0);
		bool any;
		for (;;) {
			any = false;
			for (size_t j = 0; j < num_of_edges; ++j) {
				if (distance.at(list_of_edges.at(j).first_vertex) < INF) {
					if (distance.at(list_of_edges.at(j).scnd_vertex) > distance.at(list_of_edges.at(j).first_vertex) + list_of_edges.at(j).price)
					{
						distance.set(list_of_edges.at(j).scnd_vertex, distance.at(list_of_edges.at(j).first_vertex) + list_of_edges.at(j).price);
						predecessor.set(list_of_edges.at(j).scnd_vertex, list_of_edges.at(j).first_vertex);
						any = true;
					}
				}
			}
			if (!any)  break;
		}
		if (distance.at(destination) == INF) {
			cout << "There's no way from ";
			city.at(start).print_to_console();
			cout << " to ";
			city.at(destination).print_to_console();
			cout << endl;
			return;
		}
		List<int> way;
		int price = 0;
		for (int cur = destination; cur != -1; cur = predecessor.at(cur))
		{
			way.push_back(cur);
		}
		way.reverse();
		for (size_t i = 1; i < way.get_size(); i++) {
			price += list_of_edges.get_price(way.at(i - 1), way.at(i));
		}
		cout << "The way from ";
		city.at(start).print_to_console();
		cout << " to ";
		city.at(destination).print_to_console();
		cout << ":\n";
		for (size_t i = 0; i < way.get_size(); ++i)
		{
			city.at(way.at(i)).print_to_console();
			if (i + 1 != way.get_size())
				cout << " --> ";
		}
		cout << endl << "Total cost: " << price << endl;
	}

	List<int> get_way(size_t start, size_t destination) {
		if (city.isEmpty())
			throw runtime_error("Data is not set");
		if (start < 0 || destination < 0 || start > num_of_cities - 1 || destination > num_of_cities - 1)
			throw invalid_argument("Number of city is incorrect");
		List<int> distance(num_of_cities, INF);
		List<int> predecessor(num_of_cities, -1);
		distance.set(start, 0);
		bool any;
		for (;;) {
			any = false;
			for (size_t j = 0; j < num_of_edges; ++j) {
				if (distance.at(list_of_edges.at(j).first_vertex) < INF) {
					if (distance.at(list_of_edges.at(j).scnd_vertex) > distance.at(list_of_edges.at(j).first_vertex) + list_of_edges.at(j).price)
					{
						distance.set(list_of_edges.at(j).scnd_vertex, distance.at(list_of_edges.at(j).first_vertex) + list_of_edges.at(j).price);
						predecessor.set(list_of_edges.at(j).scnd_vertex, list_of_edges.at(j).first_vertex);
						any = true;
					}
				}
			}
			if (!any)  break;
		}
		List<int> way;
		if (distance.at(destination) == INF) {
			cout << "There's no way from ";
			city.at(start).print_to_console();
			cout << " to ";
			city.at(destination).print_to_console();
			cout << '.' << endl;
			return way;
		}
		for (int cur = destination; cur != -1; cur = predecessor.at(cur))
		{
			way.push_back(cur);
		}
		way.reverse();
		return way;
	}
};