//Question 1 - basic STL

//Task 1: improve fill_vector and vecOfVec.push_back performance - execution time can be reduced significantly, please explain the changes you made and how they improve
// the application performance.

//Task 2: Implement count_total_elements without using a "visible" for loop

//Task 3: Implement merge_vec_of_vec 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify ELEMENT_COUNT and ITERATIONS and functions fill_vector,count_total_elements and merge_vec_of_vec function signatures  

#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>

constexpr size_t ELEMENT_COUNT = 1000 * 10000;
constexpr size_t ITERATIONS = 10;

std::vector<uint64_t> fill_vector(size_t elementCount) {
	//TODO: improve function performance
	std::vector<uint64_t> vec(elementCount);//I added initialisation of the size to be ELEMENT_COUNT and it sets the capacity of the vector >= ELEMENT_COUNT. The advantage is that i can access an element directly by its index v[i] instead of using vec.pushback which is more efficient and the allocation only takes place once.
	for (size_t i = 0; i < elementCount; i++) {
		vec[i] = i;//directly accessing element with index is more efficiant than pushback because it doesnt check bounds or changes the size of the vector.
	}
	return vec;
}

/// This function should return the total elements in all of the vectors
size_t count_total_elements(const std::vector<std::vector<uint64_t>>& vecOfVec) {
	return std::accumulate(vecOfVec.begin(), vecOfVec.end(), 0, 
		[](int init, const std::vector<uint64_t>& insideVec) { // binaryOp that sums a single vector<uint64_t>
			return init+insideVec.size();
		});
}

/// This function should return a single vector that contain all of the elements of the vectors in vecOfVec
std::vector<uint64_t> merge_vec_of_vec(std::vector<std::vector<uint64_t>>& vecOfVec) {
	int index = 0;
	size_t mergedVecSize = count_total_elements(vecOfVec);
	std::vector<uint64_t> mergedVec(mergedVecSize);
	for (size_t i = 0; i < vecOfVec.size(); i++) {
		for (size_t j = 0; j < vecOfVec[i].size(); j++) {
			mergedVec[index] = vecOfVec[i][j];//directly accessing element with index is more efficiant than pushback because it doesnt check bounds or changes the size of the vector.
			index++;
		}
	}
	return mergedVec;
}

int main(int argc, char** argv)
{
	//Create vector of vectors
	std::vector<std::vector<uint64_t>> vecOfVec(ITERATIONS);//I added initialisation of the size to be ITERATIONS and the capacity of the vector >= ITERATIONS. The advantage is that i can access an element directly by its index v[i] instead of using vec.pushback which is more efficient and the allocation only takes place once.
	auto start = std::chrono::steady_clock::now();
	for (size_t i = 0; i < ITERATIONS; i++) {
		std::vector<uint64_t> vec = fill_vector(ELEMENT_COUNT);
		//TODO: improve inserting performance
		vecOfVec[i]=vec;//directly accessing element with index is more efficiant than pushback because it doesnt check bounds or changes the size of the vector.
	}
	auto end = std::chrono::steady_clock::now();
	size_t averageIterationTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / ITERATIONS;
	std::cout << "Average iteration duration in microseconds: " << averageIterationTimeUs << std::endl;

	//Count elements
	size_t totalElements = count_total_elements(vecOfVec);
	std::cout << "Total elements in vecOfVec: " << totalElements << " " << std::endl;

	//Merge vector of vectors
	std::vector<uint64_t> mergedVec = merge_vec_of_vec(vecOfVec);
	std::cout << "Total elements in merged mergedVec: " << mergedVec.size() << std::endl;

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}


