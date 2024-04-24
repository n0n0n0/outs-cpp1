#include <iostream>

template <typename T>
class SmartPtrTracer {
public:
    // 1. без такого конструктора будет ошибка при использовании в классе
    // без инициализирующего значения
    // class C { ... SmartPtrTracer<int> p;  // тут будет ошибка т.к. нет "пустого" конструктора
    // но если добавить инициализацию SmartPtrTracer переменной в классе типа
    // SmartPtrTracer<int> p{42}; то без пустого конструктора можно обойтись
    SmartPtrTracer() {
        m_counter = ++SmartPtrTracer::sharedCounter;
        std::cout << "SmartPtrTracer default contructor (no parameters) obj: " 
            << m_counter << "\n";
        m_ptr = nullptr;
    }

    SmartPtrTracer(T *d) : m_ptr(d) {
        m_counter = ++SmartPtrTracer::sharedCounter;
        std::cout << "SmartPtrTracer contructor (T *) obj: "
            << m_counter << "\n";
    }
    ~SmartPtrTracer() {
        std::cout << "SmartPtrTracer destructor delete resource for: " << m_counter << "\n";
        delete m_ptr;
    }

    SmartPtrTracer(SmartPtrTracer<T> &&other) : m_ptr{other.m_ptr} { 
        std::cout << "SmartPtrTracer move ctor && for: " << m_counter << "\n";
        other.m_ptr = nullptr; 
    }

    SmartPtrTracer<T> &operator=(SmartPtrTracer<T> &&other) {
        std::cout << "SmartPtrTracer operator= for && for: " << m_counter << "\n";
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
        return *this;
    };

    T* operator->() { return m_ptr; }
    T& operator*()   { return *m_ptr; }

    T* data() { return m_ptr; }
    T* get() { return m_ptr; }

    inline static int sharedCounter = 0;
private:
    T *m_ptr;
    int m_counter = 0;
};

class Tracer {
public:
    Tracer() {
        m_counter = ++Tracer::sharedCounter;
        std::cout << "Tracer default contructor (no parameters) obj: " 
            << m_counter << "\n";
        m_ptr = nullptr;
    }

    Tracer(int* x) : m_ptr(x) {
        m_counter = ++Tracer::sharedCounter;
        std::cout << "Tracer contructor (T *) obj: "
            << m_counter << "\n";
    }
    ~Tracer() {
        std::cout << "SmartPtrTracer destructor delete resource for: " << m_counter << "\n";
        delete m_ptr;
    }

    Tracer(Tracer &other) {
        m_counter = ++Tracer::sharedCounter;
        m_ptr = new int;
        *m_ptr = (*other.m_ptr);
        std::cout << "Tracer copy ctor & for: " << m_counter 
                << " copied value: " << (*m_ptr) << " \n";
    }

    Tracer(Tracer &&other) : m_ptr{other.m_ptr} { 
        std::cout << "Tracer move ctor && for: " << m_counter << "\n";
        other.m_ptr = nullptr; 
    }

    Tracer &operator=(Tracer &&other) {
        std::cout << "Tracer operator= for && for: " << m_counter << "\n";
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
        return *this;
    };

    int data() { return 1; }

    inline static int sharedCounter = 0;
private:
    int *m_ptr;
    int m_counter = 0;
};

int main() {
    std::cout << "Hello, from lambda scope!\n";

    {
        std::cout << " --- Scope 1 start --- \n";
        SmartPtrTracer<int> t1(new int{42});
        std::cout << "Tracer t1 point to address: " << t1.get() << "\n";
        std::cout << "Tracer t1 has value: " << (*t1) << "\n";
        std::cout << " --- Scope 1 finised --- \n";
    }

    //SmartPtrTracer<int> t2(new int{42});

    // ошибка, cannot be referenced оператор копирования & по умолчанию deleted
    //auto lambda = [t2]() { };
    //auto lambda = [&t2]() { };    // так можно но нужно ли?

    {
        std::cout << " --- Scope 2 start --- \n";

        SmartPtrTracer<int> *t3 = new SmartPtrTracer<int>(new int{33});

        auto lambda3 = [t3]() { 
            std::cout << "Hello from lambda3 with t3 address: " << t3 << " \n";
            std::cout << "Hello from lambda3 with t3.data address: " << t3->data() << " \n";
            std::cout << "Hello from lambda3 with t3 value: " << (*t3->data()) << " \n";
        };
        std::cout << "Before lambda3() \n";
        lambda3();
        std::cout << "After lambda3() \n";
    }

    {
        std::cout << " --- Scope 3 start --- \n";

        Tracer t4(new int{33});

        auto lambda4 = [t4]() { 
            std::cout << "Hello from lambda4 with t4 value: "; // << t4.data() << " \n";
        };
        std::cout << "Before lambda4() \n";
        lambda4();
        std::cout << "After lambda4() \n";
    }
}