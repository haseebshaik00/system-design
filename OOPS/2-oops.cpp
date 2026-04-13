#include<bits/stdc++.h>
#include<iostream>
using namespace std;

// Refactored using GPT 5.3: Thinking Model

// ======= FRIEND FUNCTION DEMO FORWARD DECLARATION =======
class Teacher;

// ======= ABSTRACT CLASS =======
class IPerson {
public:
    virtual void introduce() const = 0;  // pure virtual function
    virtual ~IPerson() {}               // virtual destructor
};

// ======= BASE CLASS =======
class Person : public IPerson {
public:
    const int id;               // const member (must be initialized)
    int age;
    string name;
    static int population;      // static variable - shared accross all the objects

    // If no constuctor is defined, C++ implicitly implements a default constructor

    /*
    // Default constructor - overloaded - [Non-parameterized]
    Person() : id(0), age(0), name("Unknown") {
        cout << "Default constructor called\n";
        population++;
    }
    */
    //Default constructor with default values - overloaded - [parameterized]
    Person(int x = 0) : id(0), age(x), name("Default") {
        cout<<"Constructor with default argument called for "<<name<<endl;
        population++;
    }

    // Parameterized constructor - usually used!
    Person(int age, string name, int personID = 0) : id(personID), age(age), name(name) {
        cout<<"Parameterized constructor called for "<< name<<endl;
        population++;
    }

    // Copy constructor (Shallow copy)
    Person(const Person& p) : id(p.id), age(p.age), name(p.name) {
        cout << "Shallow copy constructor called\n";
    }

    // const function and parameter
    bool isVoteEligible(const bool hasSSN) const {
        return hasSSN && age >= 18;
    }

    // Virtual function for polymorphism
    virtual void introduce() const override {
        cout << "Hi, I'm " << name << ", age " << age << ", ID " << id << ".\n";
    }

    static int getPopulation() {
        return population;
    }

    virtual ~Person() {
        cout << "Destructor of Person called for " << name << endl;
        population--;
    }
};

// This is the definition and initialization of a static data member outside the class. It is shared among all instances of the Person class.
// There is only one copy of it, regardless of how many objects are created. It must be defined outside the class (as it's not tied to any one object).
int Person::population = 0;

// ======= STUDENT CLASS =======
class Student : virtual public Person {
public:
    int* marks;

    // Default constructor
    Student() : Person() {
        marks = new int[3]{0};
    }

    // Parameterized constructor
    Student(int age, string name, int id, int m1 = 0, int m2 = 0, int m3 = 0)
        : Person(age, name, id) {
        marks = new int[3]{m1, m2, m3};
        cout << "Student parameterized constructor called\n";
    }

    // Deep copy constructor
    Student(const Student& s) : Person(s) {
        marks = new int[3];
        for (int i = 0; i < 3; ++i)
            marks[i] = s.marks[i];
        cout << "Deep copy constructor called\n";
    }

    // Copy assignment operator
    void operator=(const Student& s) {
        for (int i = 0; i < 3; ++i)
            marks[i] = s.marks[i];
        cout << "Copy assignment operator called\n";
    }

    void introduce() const override {
        cout << "I'm Student " << name << ", age " << age << ", ID " << id << ".\n";
    }

    ~Student() {
        delete[] marks;
        marks = nullptr;
        cout << "Student destructor called\n";
    }
};

// ======= TEACHER CLASS =======
class Teacher : virtual public Person {
private:
    double salary;

public:
    Teacher() : Person(), salary(0.0) {}
    Teacher(string name, int age, int id, double salary) : Person(age, name, id), salary(salary) {}

    void setSalary(double salary) {
        this->salary = salary;
    }

    double getSalary() const {
        return salary;
    }

    void introduce() const override {
        cout << "I'm Teacher " << name << ", teaching with salary $" << salary << endl;
    }

    friend class TA;                    // Friend class
    friend void revealSalary(const Teacher& t);  // Friend function
};

// ======= FRIEND FUNCTION =======
void revealSalary(const Teacher& t) {
    cout << "[Friend Function] Teacher " << t.name << "'s salary is $" << t.salary << endl;
}

// ======= TA CLASS (MULTIPLE INHERITANCE) =======
class TA : public Student, public Teacher {
public:
    TA(string name, int age, int id, double salary)
        : Person(age, name, id), Student(age, name, id), Teacher(name, age, id, salary) {
        marks = new int[3]{90, 95, 100};
    }

    void introduce() const override {
        cout << "I'm TA " << name << ", ID " << id << ", also assist teacher with salary $" << getSalary() << endl;
    }

    void showTeacherSalary() {
        cout << "[Friend Class] Teacher salary accessed by TA: $" << Teacher::getSalary() << endl;
    }
};

// ======= STATIC OBJECT DEMO =======
void staticObjectDemo() {
    static Person staticPerson(99, "StaticUser", 999);
    staticPerson.introduce();
}

// ======= MAIN =======
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "--- Object Creation ---\n";
    Person p1;
    Person p2(25, "Alice", 101);
    Person p3 = p2;  // copy constructor

    cout << "\n--- Student Example ---\n";
    Student s1;
    s1.name = "Bob";
    s1.age = 20;
    s1.introduce();

    Student s2 = s1;  // deep copy constructor
    s2.marks[0] = 85;

    cout << "\n--- Teacher Example ---\n";
    Teacher t1("Dr. Smith", 45, 201, 70000);
    t1.introduce();
    revealSalary(t1);  // friend function

    cout << "\n--- TA Example ---\n";
    TA ta1("Charlie", 23, 301, 35000);
    ta1.introduce();
    ta1.showTeacherSalary();

    cout << "\n--- Static Object Demo ---\n";
    staticObjectDemo();
    staticObjectDemo();  // will not recreate object

    cout << "\n--- Vote Eligibility ---\n";
    cout << "Is " << p2.name << " eligible to vote? " << (p2.isVoteEligible(true) ? "Yes" : "No") << endl;

    cout << "\nTotal Person objects: " << Person::getPopulation() << endl;

    return 0;
}