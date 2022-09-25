// g++ benchmark.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

#include <vector>
#include <array>

#include <benchmark/benchmark.h>

const int iter = 4;

struct Person {
	float weight = 60; // kg
	int height = 160; // cm
	
	Person() = default;
	Person(float w, int h)
		: weight(w)
		, height(h)
	{}
};

Person p_arr[iter] = {{40,140},
		{50,150},
		{60,160},
		{70,170}};

struct People {
	std::vector<float> weights = {40,50,60,70};
	std::vector<int> heights = {140,150,160,170};
} p_vec;


struct PeopleArr {
	std::array<float, iter> weights = {40,50,60,70};
	std::array<int, iter> heights = {140,150,160,170};
} p_arr_struct;

static void BM_Access_Arr(benchmark::State& state) {
	for(auto _ : state) {
		for(int i = 0; i < 4; i++) {
			p_arr[i].weight;
			p_arr[i].height;
		}
	}
}

BENCHMARK(BM_Access_Arr);

static void BM_Access_Vec(benchmark::State& state) {
	for(auto _ : state) {
		for(int i = 0; i < 4; i++) {
			p_vec.weights[i];
			p_vec.heights[i];
		}
	}
}

BENCHMARK(BM_Access_Vec);

static void BM_Access_Arr_Struct(benchmark::State& state) {
	for(auto _ : state) {
		for(int i = 0; i < 4; i++) {
			p_arr_struct.weights[i];
			p_arr_struct.heights[i];
		}
	}
}

BENCHMARK(BM_Access_Arr_Struct);

BENCHMARK_MAIN();

/*
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
BM_Access_Arr              2.52 ns         2.52 ns    278007511
BM_Access_Vec              9.22 ns         9.22 ns     75243907
BM_Access_Arr_Struct       15.7 ns         15.7 ns     44572819
*/
