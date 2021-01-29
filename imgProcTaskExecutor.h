#ifndef IMGPROCTASKEXECUTOR_H
#define IMGPROCTASKEXECUTOR_H

#include <map>
#include <opencv2/core/core.hpp>
#include "imgProcTask.h";

namespace my {
	typedef std::map<std::string, ImgProcTask*> ImgProcTaskQueue;
	class ImgProcTaskExecutor {
	private:
		ImgProcTaskQueue queue;

	public:
		
		void run(cv::Mat m) {
			
			for (auto const& it : queue) {
				my::ImgProcTask *task = it.second;
				if (task->isEnable()) {
					task->handle(m);
				}
			}
		}

		void insert(std::string name, my::ImgProcTask* task) {
			queue[name] = task;
		}

		void remove(std::string name) {
			ImgProcTaskQueue::iterator it = queue.find(name);
			if (it != queue.end()) {
				queue.erase(it);
			}
		}

		void clear() {
			queue.clear();
		}

		void runTask(std::string name, cv::Mat m) {
			ImgProcTaskQueue::iterator it = queue.find(name);

			if (it != queue.end()) {
				ImgProcTask* task = it->second;
				if (task->isEnable()) {
					task->handle(m);
				}
			}
		}

		ImgProcTask* find(std::string name) {
			ImgProcTaskQueue::iterator it = queue.find(name);
			return it == queue.end() ? nullptr : it->second ;
		}

		void resetTask() {
			for (auto const& it : queue) {
				my::ImgProcTask* task = it.second;
				task->reset();
			}
		}
	};
}

#endif