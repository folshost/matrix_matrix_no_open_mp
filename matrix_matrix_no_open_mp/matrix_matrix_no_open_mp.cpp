// matrix_matrix_no_open_mp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"




#include <list>
#include <set>

#include <iostream>
#include <istream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <cstddef>
#include <numeric>
#include <string>
#include <utility>
#include <vector>



///////////////////////////////////////////////////////////////////////////////





int debug = 0;

std::vector<double> get_col(const std::vector< std::vector<double> >& data,
	int col);

double dot_product(const std::vector<double> row,
	const std::vector<double> columns);

void usage(char* func_name) {
	std::cout << "usage: " << func_name << " double1 double2 double3 double4 [0..2]"
		<< std::endl;
}

void rules() {
	std::cout << "For matrix multiplication to be possible, with matrices" <<
		" X(x_1,x_2) and Y(y_1,y_2), for X*Y x_2 MUST equal y_1, and" <<
		" vice versa" << std::endl;
}


double dot_product(const std::vector<double> row,
	const std::vector<double> columns) {
	double sum = 0;
	for (int i = 0; i < row.size(); i++) {
		sum += row.at(i) * columns.at(i);
	}
	return sum;
}


std::vector< std::vector<double> > matrix_gen(int dim_on, int dim_tw) {
	//hpx::cout << dim_on << " " << dim_tw << hpx::endl;
	std::vector< std::vector<double > > data;
	data.reserve(dim_on);
	//hpx::cout << data.capacity() << hpx::endl;
	for (int i = 0; i < dim_on; i++) {
		std::vector<double > k;
		data.push_back(k);
		data.at(i).reserve(dim_tw);
	}
	return data;
}

std::vector< std::vector < double > >
rand_filler(int dim_one, int dim_two) {
	std::vector< std::vector< double > > data =
		matrix_gen(dim_one, dim_two);
	for (int i = 0; i < data.capacity(); i++) {
		data.at(0);
		data.at(i).clear();
		for (int j = 0; j < data.at(0).capacity(); j++) {
			data.at(i).push_back(j);
			//data.at(i).push_back((double)(rand() % 100));
		}

	}
	if (debug > 1) {
		for (int i = 0; i < data.capacity(); i++) {
			std::cout << "[";
			for (int j = 0; j < data.at(0).capacity(); j++) {
				std::cout << data.at(i).at(j) << " ";
			}
			std::cout << "]" << std::endl;
		}
	}
	return data;
}


std::vector< std::vector < double > >
first_filler(int dim_one, int dim_two) {
	std::vector< std::vector< double > > data =
		matrix_gen(dim_one, dim_two);
	for (int i = 0; i < data.capacity(); i++) {
		data.at(0);
		data.at(i).clear();
		for (int j = 0; j < data.at(0).capacity(); j++) {
			data.at(i).push_back(j);
			//data.at(i).push_back((double)(rand() % 100));
		}

	}
	if (debug > 1) {
		for (int i = 0; i < data.capacity(); i++) {
			std::cout << "[";
			for (int j = 0; j < data.at(0).capacity(); j++) {
				std::cout << data.at(i).at(j) << " ";
			}
			std::cout << "]" << std::endl;
		}
	}
	return data;
}


std::vector< std::vector < double > >
second_filler(int dim_one, int dim_two) {
	std::vector< std::vector< double > > data =
		matrix_gen(dim_one, dim_two);
	for (int i = 0; i < data.capacity(); i++) {
		data.at(0);
		data.at(i).clear();
		for (int j = 0; j < data.at(0).capacity(); j++) {
			data.at(i).push_back(j);
			//data.at(i).push_back((double)(rand() % 100));
		}

	}
	if (debug > 1) {
		for (int i = 0; i < data.capacity(); i++) {
			std::cout << "[";
			for (int j = 0; j < data.at(0).capacity(); j++) {
				std::cout << data.at(i).at(j) << " ";
			}
			std::cout << "]" << std::endl;
		}
	}
	return data;
}




std::vector< double > get_col(const std::vector< std::vector< double > >& data,
	int col)
{
	std::vector< double > column;
	column.reserve(data.capacity());
	for (int i = 0; i < data.capacity(); i++)
	{
		column.push_back(data.at(i).at(col));
	}
	return column;
}



std::vector< std::vector < double > > matrix_foreman_serial(
	std::vector< std::vector< double > >& one,
	std::vector< std::vector< double > >& two)
{
	bool twenty_five = false, fifty = false, seventy_five = false;

	std::vector< std::vector< double > > data;
	data.reserve(one.capacity());
	std::vector< std::vector< double > > futuresParent;
	std::vector<int> futuresIndex(one.size());
	futuresParent.reserve(one.size());

	for (int i = 0; i < one.size(); i++) {
		std::vector<double> temp;
		temp.reserve(two.at(0).size());
		futuresParent.push_back(temp);
	}

	std::cout << "Matrix Foreman Loading:" << std::endl;

	int size_one = one.size(), size_two = two.at(0).size();
	//#pragma omp parallel for
	for (int j = 0; j<size_one; j++) {

		for (int i = 0; i < size_two; i++) {
			futuresParent.at(j).push_back(dot_product(one.at(j), two.at(i)));
		}

	}

	std::cout << "Finshed loading the async calls!" << std::endl;
	return futuresParent;
}
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

	if (argc != 5 && argc != 6) {
		usage(argv[0]);
		std::string input;
		std::getline(std::cin, input);
		return 0;
	}
	if (argc == 5) {
		std::cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3]
			<< " " << argv[4] << std::endl;
	}
	if (argc == 6) {
		std::cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3]
			<< " " << argv[4] << " " << argv[5] << std::endl;
	}



	srand(time(NULL));
	char* end;

	const int first_matrix_dim_one = strtol(argv[1], &end, 10);
	const int first_matrix_dim_two = strtol(argv[2], &end, 10);

	const int second_matrix_dim_one = strtol(argv[3], &end, 10);
	const int second_matrix_dim_two = strtol(argv[4], &end, 10);

	if (argc == 6) {
		debug = strtol(argv[5], &end, 10);
	}

	if (first_matrix_dim_two != second_matrix_dim_one) {
		rules();
		std::string input;
		std::getline(std::cin, input);
		return 0;
	}

	if (debug > 0)
		std::cout << first_matrix_dim_one << " " << first_matrix_dim_two <<
		std::endl;
	std::vector< std::vector< double > > first_matrix =
		first_filler(first_matrix_dim_one, first_matrix_dim_two);

	if (debug > -1)
		std::cout << "After first rand_filler" << std::endl;


	std::vector< std::vector< double > > second_matrix =
		second_filler(second_matrix_dim_one, second_matrix_dim_two);

	if (debug > -1)
		std::cout << "After second rand_filler" << std::endl;


	std::vector< std::vector< double > > new_matrix = matrix_foreman_serial(
		first_matrix, second_matrix);
	std::cout << "Outside new_matrix creation" << std::endl;

	if (debug > 1) {
		for (int i = 0; i < new_matrix.size(); i++) {
			std::cout << "[ ";

			for (int j = 0; j < new_matrix.at(0).size(); j++) {
				std::cout << new_matrix.at(i).at(j) << " ";
			}
			std::cout << "]" << std::endl;
		}
	}

	std::cout << "Finished!" << std::endl;

	std::string input;
	std::getline(std::cin, input);
	return 0;
}

