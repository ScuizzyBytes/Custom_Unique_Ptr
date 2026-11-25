#include <iostream>
#include <string>
#include <utility>

using namespace std;

template <typename T>
class MyUniquePtr
{
private:
    T *ptr_ = nullptr;

public:
    explicit MyUniquePtr(T *ptr = nullptr) noexcept : ptr_(ptr) {}

    ~MyUniquePtr()
    {
        delete ptr_;
    }

    MyUniquePtr(const MyUniquePtr &) = delete;
    MyUniquePtr &operator=(const MyUniquePtr &) = delete;

    MyUniquePtr(MyUniquePtr &&other) noexcept : ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
    }

    MyUniquePtr &operator=(MyUniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T &operator*() const noexcept { return *ptr_; }
    T *operator->() const noexcept { return ptr_; }
    T *get() const noexcept { return ptr_; }
};

template <typename Te, typename... Args>
MyUniquePtr<Te> make_my_unique(Args &&...args)
{
    return MyUniquePtr<Te>(new Te(forward<Args>(args)...));
}

struct Player
{
    string name;
    int size;

    Player(string n, int h) : name(move(n)), size(h)
    {
        cout << "[+] Player" << " Created\n";
    }

    ~Player()
    {
        cout << "\n[-] Player" << " Deleted";
    }

    void status() const
    {
        cout << "Name: " << name << " " << "Hp: " << size;
    }
};

int main()
{
    auto p1 = make_my_unique<Player>("Misha", 100);
    p1->status();

    return 0;
}