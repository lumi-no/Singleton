#include <iostream>
#include <memory>
#include <mutex>


class Singleton {
private:
    static std::shared_ptr<Singleton> instance; 
    static std::mutex mutex;                  

   
    Singleton() {
        std::cout << "Singleton instance created." << std::endl;
    }

public:
   
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

   
    static std::shared_ptr<Singleton> getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr) {
            instance = std::shared_ptr<Singleton>(new Singleton());
        }
        return instance;
    }

    
    void doSomething() const {
        std::cout << "Singleton is doing something!" << std::endl;
    }
};


std::shared_ptr<Singleton> Singleton::instance = nullptr;
std::mutex Singleton::mutex;

int main() {
    auto singleton1 = Singleton::getInstance();
    singleton1->doSomething();

    auto singleton2 = Singleton::getInstance();
    singleton2->doSomething();

    if (singleton1 == singleton2) {
        std::cout << "Both are the same instance." << std::endl;
    }

    return 0;
}
