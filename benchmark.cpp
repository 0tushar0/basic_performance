// g++ benchmark.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

#include <vector>
#include <array>

#include <benchmark/benchmark.h>

constexpr int iter = 4;

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

struct PeopleCArr {
	int weights[iter] = {40,50,60,70};
	int heights[iter] = {140,150,160,170};
} p_c_arr;

void arr_iter() {
	for(int i = 0; i < iter; i++) {
		p_arr[i].weight;
		p_arr[i].height;
	}
}

static void BM_Access_Arr(benchmark::State& state) {
	for(auto _ : state) {
		arr_iter();
	}
}

BENCHMARK(BM_Access_Arr);

void vec_iter() {
	for(int i = 0; i < iter; i++) {
		p_vec.weights[i];
		p_vec.heights[i];
	}
}

static void BM_Access_Vec(benchmark::State& state) {
	for(auto _ : state) {
		vec_iter();
	}
}

BENCHMARK(BM_Access_Vec);

void p_arr_struct_iter() {
	for(int i = 0; i < iter; i++) {
		p_arr_struct.weights[i];
		p_arr_struct.heights[i];
	}
}

static void BM_Access_Arr_Struct(benchmark::State& state) {
	for(auto _ : state) {
		p_arr_struct_iter();
	}
}

BENCHMARK(BM_Access_Arr_Struct);

void c_arr_iter() {
	for(int i = 0; i < iter; i++) {
		p_c_arr.weights[i];
		p_c_arr.heights[i];
	}
}

static void BM_Access_Arr_C_Struct(benchmark::State& state) {
	for(auto _ : state) {
		c_arr_iter();
	}
}

BENCHMARK(BM_Access_Arr_C_Struct);

BENCHMARK_MAIN();

/*

---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
BM_Access_Arr                2.49 ns         2.49 ns    281609849
BM_Access_Vec                9.00 ns         9.00 ns     75583430
BM_Access_Arr_Struct         16.4 ns         16.4 ns     43667149
BM_Access_Arr_C_Struct       2.56 ns         2.56 ns    272567524

After separating into individual functions
BM_Access_Arr                4.02 ns         4.02 ns    174494693
BM_Access_Vec                9.78 ns         9.78 ns     68895976
BM_Access_Arr_Struct         17.1 ns         17.1 ns     41317196
BM_Access_Arr_C_Struct       3.57 ns         3.57 ns    195973965

*/
