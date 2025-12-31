#pragma once
#include "util/SmartCounter.hpp"

using namespace GameFr::Util;

template<typename T, T min, T max, T step>
SmartCounter<T, min, max, step>::SmartCounter() : current(min){}

template<typename T, T min, T max, T step>
void SmartCounter<T, min, max, step>::Increment(){
	current += step;
	if (current > max) current = min;
}

template<typename T, T min, T max, T step>
void SmartCounter<T, min, max, step>::operator++(){
	Increment();
}

template<typename T, T min, T max, T step>
T SmartCounter<T, min, max, step>::Subtract(const T other){
	return (current - other >= min) ? current - other : max - (other - (current - min)) + 1;
}

template<typename T, T min, T max, T step>
T SmartCounter<T, min, max, step>::Add(const T other){
	return (current + other <= max) ? current + other : min + (other - (max - current)) - 1;
}

template<typename T, T min, T max, T step>
T SmartCounter<T, min, max, step>::operator-(const T other){
	return Subtract(other); 
}

template<typename T, T min, T max, T step>
T SmartCounter<T, min, max, step>::operator+(const T other){
	return Add(other);
}

template<typename T, T min, T max, T step>
T SmartCounter<T, min, max, step>::Value() const{
	return current;
}
