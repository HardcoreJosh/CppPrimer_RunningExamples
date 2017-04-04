#pragma once
#ifndef BLOB_H
#define BLOB_H

#include <vector>
#include <string>
#include <memory>

template<typename T>
class Blob {
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;

	Blob() :data(std::make_shared<std::vector<T>>()) {}
	Blob(std::initializer_list<T> il): data(std::make_shared<std::vector<T>>(il)) {}

	size_type size() const {
		return data->size();
	}

	void pop_back() {
		check(0, "index out of range");
		data->pop_back();
	}
	void push_back(const T& val) { data->push_back(val); }
	void push_back(T&& val) { 
		data->push_back(std::move(val)); 
	}

	T& operator[](size_type idx) {
		check(idx, "index out of range");
		return (*data)[idx];
	}

	const T& operator[](size_type idx) const {
		check(idx, "index out of range");
		return (*data)[idx];
	}
	
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type idx, const std::string &msg) const;

};

template<typename T>
void Blob<T>::check(size_type idx, const std::string &msg) const {
	if (idx >= data->size())
		throw std::out_of_range(msg);
}

template<int a, int b>
bool compare()
{
	return a < b;
}


#endif
