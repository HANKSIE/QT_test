#ifndef PROCESSEXECUTOR_H
#define PROCESSEXECUTOR_H

#include <map>
#include "process.h";

namespace my {
	template<class T>
	class ProcessExecutor {

		typedef std::map<std::string, Process<T>*> Queue;
	private:
		Queue queue;

	public:
		
		void run(T arg) {
			
			for (auto const& it : queue) {
				my::Process<T>* task = it.second;
				task->run(arg);
			}
		}

		void insert(std::string name, my::Process<T>* task) {
			queue[name] = task;
		}

		void remove(std::string name) {
			Queue::iterator it = queue.find(name);
			if (it != queue.end()) {
				queue.erase(it);
			}
		}

		void clear() {
			queue.clear();
		}

		my::Process<T>* process(std::string name) {
			Queue::iterator it = queue.find(name);
			return it == queue.end() ? nullptr : it->second ;
		}

		void resetProcesses() {
			for (auto const& it : queue) {
				my::Process<T>* task = it.second;
				task->reset();
			}
		}
	};
}

#endif