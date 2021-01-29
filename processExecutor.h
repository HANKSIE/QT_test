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
				my::Process<T>* proc = it.second;
				proc->run(arg);
			}
		}

		void insert(std::string name, my::Process<T>* proc) {
			queue[name] = proc;
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
				my::Process<T>* proc = it.second;
				proc->reset();
			}
		}
	};
}

#endif