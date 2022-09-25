// g++ benchmark.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

#include <benchmark/benchmark.h>

struct Person {
	float weight = 60; // kg
	int height = 160; // cm
	
	Person() = default;
	Person(float w, int h)
		: weight(w)
		, height(h)
	{}
};

Person p_arr[4] = {{40,140},
		{50,150},
		{60,160},
		{70,170}};

struct People {
	std::vector<float> weights = {40,50,60,70};
	std::vector<float> heights = {140,150,160,170};
} p_vec;



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
	std::string x = "hello";
	for(auto _ : state) {
		for(int i = 0; i < 4; i++) {
			p_vec.weights[i];
			p_vec.heights[i];
		}
	}
}

BENCHMARK(BM_Access_Vec);

BENCHMARK_MAIN();

/*
--------------------------------------------------------
Benchmark              Time             CPU   Iterations
--------------------------------------------------------
BM_Access_Arr       2.55 ns         2.55 ns    262341968
BM_Access_Vec       10.8 ns         10.8 ns     64599849
*
