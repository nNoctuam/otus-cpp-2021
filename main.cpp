#include "lib.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <map>

template<typename T, int INITIAL_SIZE = 10>
class LinearAllocator {
public:
    using value_type = T;

    LinearAllocator() {
        _heap = static_cast<T *>(malloc(INITIAL_SIZE * sizeof(T)));
        for (size_t i = 0; i < INITIAL_SIZE; i++) {
            _blocksAvailability[i] = true;
        }
    }

    template<typename C>
    explicit LinearAllocator(const LinearAllocator<C> &other) noexcept {
        std::cout << "[LinearAllocator] copying constructor" << std::endl;
    }

    T *allocate(std::size_t n) {
        bool isSequenceFree;
        size_t position = 0, i;
        while (position <= INITIAL_SIZE + n) {
            isSequenceFree = true;
            for (i = 0; i < n; i++) {
                if (!_blocksAvailability[position]) {
                    position += n;
                    isSequenceFree = false;
                    break;
                }
            }
            if (!isSequenceFree) {
                continue;
            }

            for (i = 0; i < n; i++) {
                _blocksAvailability[i + position] = false;
            }
            return reinterpret_cast<T *>(_heap + position);
        }

        throw std::runtime_error("[LinearAllocator] cannot allocate memory! requested size=" + std::to_string(n));
    }

    void deallocate(T *p, std::size_t n) {
        for (size_t i = 0; i < n; i++) {
            _blocksAvailability[p - _heap + i] = true;
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }

    void printAvailabilityMap() {
        std::cout << "[LinearAllocator] ";
        for (bool b : _blocksAvailability) {
            std::cout << (b ? '_' : 'x') << " ";
        }
        std::cout << std::endl;
    }

    template<typename U>
    struct rebind {
        using other = LinearAllocator<U>;
    };

    ~LinearAllocator() noexcept {
        free(_heap);
    }

private:
    T *_heap = nullptr;
    bool _blocksAvailability[INITIAL_SIZE] = {};
};


template<class T, class U>
constexpr bool operator==(const LinearAllocator<T> &a, const LinearAllocator<U> &b) noexcept {
    return a._heap == b._heap && a.value_type == b.value_type;
}

template<class T, class U>
constexpr bool operator!=(const LinearAllocator<T> &a, const LinearAllocator<U> &b) noexcept {
    return a._heap != b._heap || a.value_type != b.value_type;
}

template<typename T, typename Allocator = std::allocator<T>>
class DummyArray {
public:
    DummyArray() {
        _elements = new T *[_capacity];
    };

    ~DummyArray() {
        delete[] _elements;
    };

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        explicit Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }

        pointer operator->() { return m_ptr; }

        Iterator &operator++() {
            m_ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; };

        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };

    private:

        pointer m_ptr;
    };

    void push(T value) {
        if (_current == _capacity) {
            T **tmp = new T *[_capacity * 2];
            for (int i = 0; i < _capacity; i++) {
                tmp[i] = _elements[i];
            }
            delete[] _elements;
            _elements = tmp;
            _capacity *= 2;
        }
        auto *memBlock = _allocator.allocate(size_t(1));
        _elements[_current] = new(memBlock) T(value);
        _current++;
    }

    void pop() {
        if (_current == 0) {
            throw std::runtime_error("pop on empty DummyArray");
        }
        _allocator->deallocate(_elements[_current - 1], 1);
        _current--;
    }

    void clear() {
        for (int i = 0; i < _current; i++) {
            delete _elements[i];
        }
    }

    Iterator begin() { return Iterator(_elements[0]); }

    Iterator end() {
        return Iterator(_current == _capacity ? _elements[_current - 1] + 1 : _elements[_current]);
    }

    const T &get(int index) {
        return *_elements[index];
    }

    T &operator[](int index) {
        return *_elements[index];
    }

    int capacity() {
        return _capacity;
    }

    int size() {
        return _current;
    }

    bool empty() {
        return _current == 0;
    }

    void print() {
        for (int i = 0; i < _current; i++) {
            std::cout << std::to_string(*_elements[i]) << " ";
        }
        std::cout << std::endl;
    }

private:
    Allocator _allocator;
    int _current = 0;
    int _capacity = 10;
    T **_elements;
};


int main(int, char **) {
    // region simple map
    std::cout << "MAP =================================================" << std::endl;
    std::map<int, int> m;
    m[0] = 0;
    m[1] = 1;
    for (int i = 2; i < 10; i++) {
        m[i] = m[i - 1] * i;
    }
    for (const auto &item : m) {
        std::cout << item.first << " " << item.second << " " << std::endl;
    }
    std::cout << std::endl;
    // endregion

    // region map with custom allocator
    std::cout << "MAP WITH LA =================================================" << std::endl;
    auto myMap = std::map<int, int, std::less<>,
            LinearAllocator<std::pair<const int, int>, 10>
    >{};
    myMap[0] = 0;
    myMap[1] = 1;
    for (int i = 2; i < 10; i++) {
        myMap[i] = myMap[i - 1] * i;
    }
    for (const auto &item : myMap) {
        std::cout << item.first << " " << item.second << " " << std::endl;
    }
    std::cout << std::endl;
    // endregion

    // region DummyArray
    std::cout << "DUMMY ARRAY =================================================" << std::endl;
    auto list = new DummyArray<int, std::allocator<int>>();
    for (int i = 0; i < 10; i++) {
        list->push(i);
    }
    for (int i = 0; i < 10; i++) {
        std::cout << list->get(i) << std::endl;
    }
    std::cout << std::endl;
    // endregion

    // region DummyArray with LinearAllocator
    std::cout << "DUMMY ARRAY WITH LA =================================================" << std::endl;
    DummyArray<int, LinearAllocator<int, 10>> list2;
    for (int i = 0; i < 10; i++) {
        list2.push(i);
    }

    for (auto i : list2) {
        std::cout << i << std::endl;
    }
    // endregion

    return 0;
}
