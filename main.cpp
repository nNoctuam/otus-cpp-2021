#include "lib.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <map>

template<typename T>
class DummyAllocator {
public:
    using value_type = T;

    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    DummyAllocator() = default;

    template<typename C>
    explicit DummyAllocator(const C &other) {
        std::cout << "[DummyAllocator] copying constructor" << std::endl;
    }

    T *allocate(std::size_t n) {
        void *p = std::malloc(n * sizeof(T));
        std::cout << "[DummyAllocator] allocate " << p << std::endl;
        return (T *) p;
    }

    void deallocate(T *p, std::size_t) {
        std::cout << "[DummyAllocator] deallocated " << p << std::endl;
        free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        std::cout << "[DummyAllocator] construct " << p << " with ";
//        (std::cout << ... << args);
        std::cout << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }
};

template<typename T, int INITIAL_SIZE = 10>
class LinearAllocator {
public:
    using value_type = T;

    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;


    T *_heap = nullptr;
    bool _blocksAvailability[INITIAL_SIZE] = {};

    LinearAllocator() {
        std::cout << "size=" << INITIAL_SIZE << " sizeof(T)=" << sizeof(T) << " heapSize=" << INITIAL_SIZE * sizeof(T);
        _heap = static_cast<T *>(malloc(INITIAL_SIZE * sizeof(T)));
        std::cout << " _heap=" << _heap << std::endl;
        for (size_t i = 0; i < INITIAL_SIZE; i++) {
            _blocksAvailability[i] = true;
        }
    };

    template<typename C>
    explicit LinearAllocator(const LinearAllocator<C> &other) {
        std::cout << "[LinearAllocator] copying constructor" << std::endl;
    }

    T *allocate(std::size_t n) {
        bool isSequenceFree;
        for (size_t i = 0; INITIAL_SIZE - i >= n; i++) {
            isSequenceFree = true;
            for (size_t s = 0; s < n; s++) {
                if (!_blocksAvailability[i]) {
                    isSequenceFree = false;
                    break;
                }
            }
            if (!isSequenceFree) {
                continue;
            }

            for (size_t s = 0; s < n; s++) {
                _blocksAvailability[s + i] = false;
            }
            std::cout << "[LinearAllocator] allocate n=" << n << ": " << _heap + i << std::endl;
            printMap();
            return reinterpret_cast<T *>(_heap + i);
        }

        printMap();
        throw std::runtime_error("[LinearAllocator] cannot allocate memory! requested size=" + std::to_string(n));

        return nullptr;
    }

    void deallocate(T *p, std::size_t s) {
        std::cout << "[LinearAllocator] deallocate " << p << std::endl;
        for (size_t i = 0; i < s; i++) {
            _blocksAvailability[(p - _heap) + i] = true;
        }
        printMap();
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&... args) {
        std::cout << "[LinearAllocator] construct " << p << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }

    void printMap() {
        std::cout << "[LinearAllocator] ";
        for (bool b : _blocksAvailability) {
            std::cout << (b ? 'x' : '_') << " ";
        }
        std::cout << std::endl;
    }

    template<typename U>
    struct rebind {
        using other = LinearAllocator<U>;
    };

    ~LinearAllocator() = default;
};


template<typename T, typename Allocator = std::allocator<T>>
class DummyArray {
public:
    DummyArray() {
        _elements = new T *[_capacity];
    };

    ~DummyArray() {
        delete[] _elements;
    };

    void append(T value) {
        if (_size == _capacity) {
            T **tmp = new T *[_capacity * 2];
            for (int i = 0; i < _capacity; i++) {
                tmp[i] = _elements[i];
            }
            delete[] _elements;
            _elements = tmp;
            _capacity *= 2;
        }
        auto *memBlock = _allocator.allocate(1);
        _elements[_size] = new(memBlock) T(value);
        _size++;
    }

    void pop() {
        if (_size == 0) {
            throw std::runtime_error("pop on empty DummyArray");
        }
        _allocator->deallocate(_elements[_size - 1], 1);
        _size--;
    }

    const T &get(int index) {
        return *_elements[index];
    }

    T &operator[](int index) {
        return *_elements[index];
    }

    int size() {
        return _size;
    }

    bool empty() {
        return _size == 0;
    }

    void print() {
        for (int i = 0; i < _size; i++) {
            std::cout << *_elements[i] << " ";
        }
        std::cout << std::endl;
    }


private:
    Allocator _allocator;
    int _size = 0;
    int _capacity = 10;
    T **_elements;
};

int main(int, char **) {
//    LinearAllocator<int16_t, 10> la;
//    int16_t ** ms = new int16_t *[10];
//    ms[0] = la.allocate(1);
//    ms[1] = la.allocate(1);
////    la.construct(ms[0], 9);
//    new(ms[0]) int16_t ( int16_t(INT16_MAX-1));
//    new(ms[1]) int16_t(8);
//    std::cout << *ms[0] << std::endl;
//    std::cout << *ms[1] << std::endl;
//    std::cout << std::endl;




    std::cout << "\nSIMPLE MAP =================================================" << std::endl;
    // region simple map
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

    std::cout << "\nMAP WITH LA =================================================" << std::endl;

    // region map with custom allocator
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

    std::cout << "\nDUMMY ARRAY =================================================" << std::endl;

    // region DummyArray
    auto list = new DummyArray<int, std::allocator<int>>();
    for (int i = 0; i < 10; i++) {
        list->append(i);
    }
    for (int i = 0; i < 10; i++) {
        std::cout << list->get(i) << std::endl;
    }
    // endregion

    std::cout << "\nDUMMY ARRAY WITH LA =================================================" << std::endl;

    // region DummyArray with LinearAllocator
    auto list2 = new DummyArray<int, LinearAllocator<int>>();
    for (int i = 0; i < 10; i++) {
        list2->append(i);
    }
    for (int i = 0; i < 10; i++) {
        int v = list2->get(i);
        std::cout << v << std::endl;
    }
    // endregion

    return 0;

//    region old
//    std::cout << std::endl << "----- DummyAllocator<int> -----" << std::endl;
//    DummyAllocator<int> dai;
//    int *di = dai.allocate(1);
//    dai.construct(di, 7);
//    std::cout << "check: " << di[0] << '\n';
//    dai.deallocate(di, 1);
//
//
//    std::cout << std::endl << "----- DummyAllocator<string> -----" << std::endl;
//    DummyAllocator<std::string> das;
//    std::string *ds = das.allocate(1);
//    das.construct(ds, "foo");
//    std::cout << "check: " << ds[0] << '\n';
//    das.deallocate(ds, 1);
//
//
//    std::cout << std::endl << "----- std::vector<int, DummyAllocator<int>> -----" << std::endl;
//    std::vector<int, DummyAllocator<int>> vda;
//    vda.push_back(35354);
//    vda.push_back(6443);
//    std::cout << vda[0] << " " << vda[1] << std::endl;
//    vda.clear();
//
//
    std::cout << std::endl << "----- LinearAllocator<int> -----" << std::endl;
    LinearAllocator<int> lai;
    int *li = lai.allocate(1);
    lai.construct(li, 22334455);
    int *li2 = lai.allocate(1);
    lai.construct(li2, 5555555);
    int *li3 = lai.allocate(2);
    lai.construct(li3, 7);
    std::cout << "check: " << *li2 << '\n';
    std::cout << "check: " << li[0] << '\n';
    std::cout << "check: " << *li3 << '\n';

    lai.deallocate(li, 1);
    lai.deallocate(li2, 1);
    int *li4 = lai.allocate(1);
    lai.construct(li4, 99);

    std::cout << "check: " << *li3 << '\n';
    std::cout << "check: " << *li4 << '\n';

    lai.deallocate(li3, 2);
    lai.deallocate(li4, 1);

//
//    std::cout << std::endl << "-----  LinearAllocator<std::string> -----" << std::endl;
//    LinearAllocator<std::string> las;
//    std::string *ls = las.allocate(1);
//    las.construct(ls, "foobaereer");
//    std::cout << "check: " << ls[0] << '\n';
//    las.deallocate(ls, 1);


//    std::cout << std::endl << "-----  DummyArray<std::string, std::allocator<std::string>> -----" << std::endl;
//    auto list = new DummyArray<std::string, std::allocator<std::string>>();
//    list->append("foo");
//    list->append("bar");
//    list->append("foobarrr!!!");
//    std::cout << "size=" << list->size() << std::endl;
//    std::cout << "last=" << list->get(list->size()-1) << std::endl;
//    list->print();
//    list->pop();
//    std::cout << "size=" << list->size() << std::endl;
//    list->print();
//    list->pop();
//    list->pop();
//    list->pop();
//    for (auto *element = list->first(); element != nullptr; element = element->next()) {
//        std::cout << "[" << element->_value << "]";
//    }
//    std::cout << std::endl;
//
//    list->remove(list->first());
//    list->remove(list->first());
//    list->remove(list->first());
//    std::cout << "removed all, size=" << list->size() << std::endl;
//    endregion
    return 0;
}
