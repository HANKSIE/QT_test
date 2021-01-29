#ifndef PROCESS_H
#define PROCESS_H

namespace my {
	template <class T>
	class Process {
	protected:
		bool _isEnable = false;
	public:
		void run(const T arg) {
			if (isEnable()) {
				define(arg);
			}
		};
		virtual void define(T) = 0;
		virtual void reset() { disable(); };
		void enable() { _isEnable = true; };
		void disable() { _isEnable = false; };
		void turn() { _isEnable = !_isEnable; }
		bool isEnable() { return _isEnable; };
	};
}

#endif