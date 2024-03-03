#include <iostream>
using namespace std;

class Parent
{
public:
    int a;
    int b;
    Parent()
    {
        this->a = 0;
        this->b = 0;
    }

    void set_a(int value)
    {
        this->a = value;
    }

    int get_a()
    {
        return this->a;
    }

    void set_b(int value)
    {
        this->b = value;
    }

    int get_b()
    {
        return this->b;
    }
};

class Child : public Parent
{
public:
    int add_a_and_b()
    {
        return get_a() + get_b();
    }
};

int main(int argc, const char *argv[])
{
    Child c;
    c.set_a(1);
    c.set_b(2);
    std::cout << c.add_a_and_b() << std::endl;

    return 0;
}
