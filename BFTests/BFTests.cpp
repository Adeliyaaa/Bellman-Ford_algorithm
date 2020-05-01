#include "pch.h"
#include "CppUnitTest.h"
#include "../Bellman-Ford/Bellman–Ford_algorithm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BFTests
{
	TEST_CLASS(BFTests)
	{
	public:
		
		TEST_METHOD(empty_file_exception)
		{
			BellmanFord test;
			try {
				test.find_way(3, 5);
			}
			catch (runtime_error x) {
				Assert::AreEqual(x.what(), "Data is not set");
			}
		}

		TEST_METHOD(incorrect_cities_exception)
		{
			BellmanFord test;
			test.set_data("C:\\Users\\adelya\\source\\repos\\BFTests\\forthetest.txt");
			try {
				test.find_way(6, 13);
			}
			catch (invalid_argument x) {
				Assert::AreEqual(x.what(), "Number of city is incorrect");
			}
			
		}

		TEST_METHOD(correct_algorithm_test)
		{
			BellmanFord test;
			test.set_data("C:\\Users\\adelya\\source\\repos\\BFTests\\forthetest.txt");
			List<int> way = test.get_way(1, 3);
			Assert::AreEqual(way.at(0), 1);
			Assert::AreEqual(way.at(1), 0);
			Assert::AreEqual(way.at(2), 3);

		}
	};
}
