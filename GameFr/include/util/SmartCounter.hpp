#pragma once
namespace GameFr::Util{
	template<typename T, T min, T max, T step>
	class SmartCounter{
		T current;
	public:
		SmartCounter();
		void Increment();
		void operator++();
		T operator-(const T other);
		T Subtract(const T other);
		T operator+(const T other);
		T Add(const T other);
		T Value() const;
	};
}

#include "SmartCounter.tpp"
