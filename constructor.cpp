#include <bits/stdc++.h>

class MyClass
{
public:
    std::string name;

    // Default Constructor
    MyClass(const std::string &n = "Default") : name(n)
    {
        std::cout << "Constructor called for: " << name << std::endl;
    }

    // Copy Constructor
    MyClass(const MyClass &other) : name(other.name + "_copy")
    {
        std::cout << "Copy Constructor called for: " << name << " from " << other.name << std::endl;
    }

    // Move Constructor (C++11+) - for completeness, though not strictly about copy
    // Improves performance by avoiding deep copies for temporary objects.
    MyClass(MyClass &&other) noexcept : name(other.name + "_moved")
    {
        std::cout << "Move Constructor called for: " << name << " from " << other.name << std::endl;
        other.name = "MOVED_FROM_" + other.name; // Indicate moved-from state
    }

    // Destructor
    // No parameters, No return type, Cannot be overloaded
    // a C++ class can only have one destructor.
    // If your class uses dynamic memory allocation, you MUST free memory inside destructor.
    ~MyClass()
    {
        std::cout << "Destructor called for: " << name << std::endl;
    }

    void display() const
    {
        std::cout << "MyClass object name: " << name << std::endl;
    }
};

// --- Scenarios where Copy Constructor is Called ---

// 1. Pass by Value: Object passed as function argument
void func_passByValue(MyClass obj)
{
    std::cout << "  Inside func_passByValue, received: ";
    obj.display();
    // When obj goes out of scope, its destructor is called
} // Destructor for 'obj' (the copy) is called here

// 2. Return by Value: Returning object from a function
MyClass func_returnByValue(const std::string &name_prefix)
{
    MyClass temp_obj("Temp_" + name_prefix); // Constructor
    std::cout << "  Inside func_returnByValue, returning: ";
    temp_obj.display();
    return temp_obj; // Copy Constructor (or Move/Elision) can happen here
}

int main()
{
    std::cout << "--- Main Start ---" << std::endl;

    // MyClass car1 =MyClass(); // will iterprete Car() as a function
    // Object Initialization (Copy-Initialization)
    std::cout << "\n--- Scenario: Object Initialization (Copy-Initialization) ---" << std::endl;
    MyClass original("Original");             // Constructor
    MyClass copy_init_obj = original;         // Copy Constructor called (copying 'original')
    MyClass moveObject = std::move(original); // move constructor is called
    copy_init_obj.display();
    original.display();

    std::cout << "\n--- Scenario: Object Initialization (Direct-Initialization) ---" << std::endl;
    // Direct initialization usually does NOT call copy constructor if a matching constructor exists
    MyClass direct_init_obj("DirectInit"); // Constructor called directly

    // Test specific form where C++17 guarantees copy elision for temporaries
    std::cout << "\n--- Scenario: Object Initialization (Temp Object Copy-Init) ---" << std::endl;
    MyClass temp_copy_init_obj = MyClass("Temporary"); // Constructor called. Copy/Move elided (C++17 guaranteed)
    temp_copy_init_obj.display();

    std::cout << "\n--- Scenario: Pass by Value ---" << std::endl;
    MyClass sender("Sender"); // Constructor
    func_passByValue(sender); // Copy Constructor called (to create 'obj' inside the function)
    sender.display();         // Original 'sender' is unchanged

    std::cout << "\n--- Scenario: Return by Value ---" << std::endl;
    MyClass returned_obj = func_returnByValue("FromFunc"); // Constructor for temp_obj. Then potentially Copy/Move for returned_obj.
                                                           // Usually elided in modern C++ (NRVO).
    returned_obj.display();

    std::cout << "\n--- Scenario: Adding to std::vector by value ---" << std::endl;
    std::vector<MyClass> myVector;
    MyClass element_to_add("VectorElement"); // Constructor
    myVector.push_back(element_to_add);      // Copy Constructor called (to copy 'element_to_add' into vector)
    element_to_add.display();                // Original element_to_add is unchanged

    std::cout << "\n--- Main End ---" << std::endl;

    return 0;
} // Destructors for all stack-allocated objects (original, copy_init_obj, sender, returned_obj, elements in myVector) called here