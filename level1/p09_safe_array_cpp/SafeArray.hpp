#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

// vector 管理内存和复制；本类统一检查所有公开的元素访问。
template <typename T>
class SafeArray {
private:
    std::vector<T> data;

    std::size_t checkedIndex(std::ptrdiff_t index) const {
        if (index < 0 || static_cast<std::size_t>(index) >= data.size()) {
            throw std::out_of_range("SafeArray: index out of range");
        }
        return static_cast<std::size_t>(index);
    }

public:
    explicit SafeArray(std::ptrdiff_t length) {
        if (length < 0) {
            throw std::invalid_argument("SafeArray: negative length");
        }
        data.resize(static_cast<std::size_t>(length));
    }

    std::size_t size() const {
        return data.size();
    }

    T get(std::ptrdiff_t index) const {
        return data[checkedIndex(index)];
    }

    void set(std::ptrdiff_t index, const T& value) {
        data[checkedIndex(index)] = value;
    }

    // reference 别名也兼容 vector<bool> 的特殊引用类型。
    typename std::vector<T>::reference operator[](std::ptrdiff_t index) {
        return data[checkedIndex(index)];
    }

    typename std::vector<T>::const_reference operator[](std::ptrdiff_t index) const {
        return data[checkedIndex(index)];
    }
};
