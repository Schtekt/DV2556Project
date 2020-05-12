#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include <chrono>
#include <fstream>

class Profiler {
private:
	std::chrono::high_resolution_clock::time_point begin;
	double time;

public:
	Profiler();

	void start();
	double end();

	double getDuration();
	void print(std::string file, std::string text);
};

#endif
