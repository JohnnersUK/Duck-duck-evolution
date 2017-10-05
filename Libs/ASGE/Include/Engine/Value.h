#pragma once
template <typename T>
class Value
{
public:
	Value(T) data(T) {};
	T get() { return data; }

private:
	T data;
};