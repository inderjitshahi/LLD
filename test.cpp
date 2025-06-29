#include <bits/stdc++.h>
using namespace std;

class Car
{
public:
    string brand;
    string name;
    int year;

    void drive()
    {
        cout << "Driving a " << brand << " " << name << " from " << year << endl;
    }
    Car(const string &b, const string &n, const int &y) : brand(b), name(n), year(y) {}
};

int main()
{

    // If you define ANY constructor for your class (even just one parameterized constructor), the compiler will NOT automatically generate a default constructor (a zero-parameter constructor) for you.
    // Car car = {"Toyota", "Corolla", 2020}; //aggregate initialization, without parametrized constructor
    Car car = Car("Toyota", "Corolla", 2020); // copy elision
    // Car *car2 = new Car("Honda", "Civic", 2021); //error, aggregate initialization works only with non-heap/stack objects
    // Car *car2 = new Car();
    // car2->drive();
    car.drive();

    // delete car2;
    return 0;
}
