
#include "Profiler.h"

namespace Profiler {

	instance::instance(const string &name) :
		m_name(name)
	{
		m_start_time = std::chrono::high_resolution_clock::now();
	}

	instance::instance() :
		m_name("unnamed profile")
	{
		m_start_time = std::chrono::high_resolution_clock::now();
	}

	instance::~instance() {
		if (!m_has_stopped) {
			stop();
		}
	}

	void instance::enable() {
		m_enabled = true;
	}

	double instance::get() const {
		if (!m_enabled) return 0;
		auto timer_elapsed = chrono::high_resolution_clock::now() - m_start_time;
		auto microseconds = chrono::duration_cast<std::chrono::microseconds>(timer_elapsed).count();

		return (double)microseconds/1000;
	}

	double instance::get_micro() const {
		if (!m_enabled) return 0;
		auto timer_elapsed = chrono::high_resolution_clock::now() - m_start_time;
		auto microseconds = chrono::duration_cast<std::chrono::microseconds>(timer_elapsed).count();

		return (double)microseconds;
	}

	void instance::stop() {
		if (!m_enabled) return;
		m_has_stopped = true;
		cout << "Profiler [" << m_name << "] took " << get() << "ms" << endl;
	}

	void instance::print() {
		if (!m_enabled) return;
		cout << "Profiler [" << m_name << "] took " << get() << "ms" << endl;
	}

	void print_memory_status() {
		ifstream infile("/proc/" + to_string(getpid()) + "/status");
		if (infile.is_open()) {
			string line;
			while (getline(infile, line)) {
				cout << line << endl;
			}
		}
	}

	uint64_t get_cycles() {
		#if PROFILE_CPU_CYCLES
		return __rdtsc();
		#endif
		return 0ull;
	}

}

