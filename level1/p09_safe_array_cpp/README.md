### 题目：SafeArray（利用class封装安全数组）

### 功能要求（一）：

实现int型数组的基本功能，当数组下标越界时报错；

### 功能要求（二）（学了运算符重载后再做）：

实现下标运算操作；

### 功能要求（三）（学了模板后再做）：

实现类型无关的安全数组；


## 实现与运行

使用 C++17，运行 CMake 目标 `p09_safe_array_cpp`。

- `SafeArray.hpp`：模板类封装数组，提供 `get`、`set`、`size` 和可读写/只读下标重载。
- 下标先检查负数和上界，越界抛出 `std::out_of_range`；负长度抛出 `std::invalid_argument`。
- 使用 `std::vector` 管理存储、复制和释放，支持 int、double、string 等类型，也兼容 bool。
- `main.cpp` 演示读写、多种类型和越界错误处理。

验证覆盖空数组、负下标、上界越界、const 读取、复制独立性和多种元素类型。
