#include <iostream>
#include <memory>

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

template <typename T>
class SmartPtrTracerReset {
public:
    SmartPtrTracerReset() {
        m_counter = ++SmartPtrTracerReset::sharedCounter;
        std::cout << "SmartPtrTracerReset default contructor (no parameters) obj: " 
            << m_counter << "\n";
        m_ptr = nullptr;
    }

    SmartPtrTracerReset(T *d) : m_ptr(d) {
        m_counter = ++SmartPtrTracerReset::sharedCounter;
        std::cout << "SmartPtrTracerReset contructor (T *) obj: "
            << m_counter << "\n";
    }
    ~SmartPtrTracerReset() {
        std::cout << "SmartPtrTracerReset destructor delete resource for: " << m_counter << "\n";
        delete m_ptr;
    }

    SmartPtrTracerReset(SmartPtrTracer<T> &&other) : m_ptr{other.m_ptr} { 
        std::cout << "SmartPtrTracerReset move ctor && for: " << m_counter << "\n";
        other.m_ptr = nullptr; 
    }

    SmartPtrTracerReset<T> &operator=(SmartPtrTracer<T> &&other) {
        std::cout << "SmartPtrTracerReset operator= for && for: " << m_counter << "\n";
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
        return *this;
    };

    void reset(T *other = nullptr) noexcept
    {
        if (m_ptr == other)
            return;
        T *old = m_ptr;
        m_ptr = other;
    }

    T* operator->() { return m_ptr; }
    T& operator*()   { return *m_ptr; }

    T* data() { return m_ptr; }
    T* get() { return m_ptr; }

private:
    T *m_ptr;
    int m_counter = 0;
    inline static int sharedCounter = 0;
};

template <typename T>
class unique_ptr {
    T *ptr;
  public:
    unique_ptr(T *ptr_) : ptr{ptr_} {}
    ~unique_ptr() { delete ptr;}

    unique_ptr(const unique_ptr<T> &) = delete;
    unique_ptr<T> &operator=(const unique_ptr<T> &) = delete;

    unique_ptr(unique_ptr<T> &&other) : ptr{other.ptr} { other.ptr = nullptr; }
    unique_ptr<T> &operator=(unique_ptr<T> &&other) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    };

    T *get() { return ptr; }

    T *operator->() { return ptr; }
    T& operator*() { return *ptr; }
};

class NullService {
public:
    NullService() {
        std::cout << "NullService constructor \n";
        m_client = SmartPtrTracer<int>(new int{84});
    }
    ~NullService() {
        std::cout << "~NullService() but not explicit delete (SmartPtrTracer)m_client \n";
    }
private:
    // так нужен будет конструктор "по умолчанию" т.е. без параметров в классе SmartPtrTracer
    SmartPtrTracer<int> m_client;
    // а так не нужен будет
    //SmartPtrTracer<int> m_client{nullptr};
};

template <typename T>
class NullServiceTpl {
public:
    NullServiceTpl() {
        std::cout << "NullServiceTpl constructor \n";
        //m_client = SmartPtrTracer<int>(new int{84});
        m_client = T(new int{63});
    }

    ~NullServiceTpl() {
        std::cout << "~NullServiceTpl() but not explicit delete (T)m_client \n";
    }
private:
    T m_client;
};

template <typename T>
class NullServiceTplReset {
public:
    NullServiceTplReset() {
        std::cout << "NullServiceTplReset constructor \n";
        //m_client = SmartPtrTracer<int>(new int{84});
        m_client.reset(T(new int{63}));
    }

    ~NullServiceTplReset() {
        std::cout << "~NullServiceTplReset() but not explicit delete (T)m_client \n";
    }
private:
    T m_client;
};

int main(int, char**){
    std::cout << "Hello, from smartptr!\n";

    {
        std::cout << " --- Scope 1 start --- \n";
        SmartPtrTracer<int> t1(new int{42});
        std::cout << "Tracer t1 point to address: " << t1.get() << "\n";
        std::cout << "Tracer t1 has value: " << (*t1) << "\n";
        std::cout << " --- Scope 1 finised --- \n";
    }
    SmartPtrTracer<int>::sharedCounter = 0;

    std::cout << " --------- scope NullService with SmartPtrTracer as member ------ \n";
    {
        NullService ns;
    }

    std::cout << " --------- scope NullServiceTpl with SmartPtrTracer<int> as tpl member ------ \n";
    {
        NullServiceTpl<SmartPtrTracer<int>> ns2;
    }

    std::cout << " --------- scope NullServiceTpl with SmartPtrTracerReset<int> as tpl member ------ \n";
    {
        NullServiceTpl<SmartPtrTracer<int>> ns3;
    }

    std::cout << " --------- scope NullServiceTplReset with SmartPtrTracerReset<int> as tpl member ------ \n";
    // {
    //     NullServiceTpl<SmartPtrTracerReset<int>> ns4;
    // }
}
