#include "Profiler.h"

Profiler::Profiler()
{

}

void Profiler::start()
{
	begin = std::chrono::high_resolution_clock::now();
}

double Profiler::end()
{
	time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin).count();

	return time;
}

double Profiler::getDuration()
{
	return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin).count();
}

void Profiler::print(std::string file, std::string text)
{
	std::ofstream stream;
	
	stream.open(file);
	stream << text << " " << time << std::endl;
	stream.close();
}
