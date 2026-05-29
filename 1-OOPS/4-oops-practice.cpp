#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class IPerson{
public:
    virtual void getInfo() const = 0; // only the presence still makes class abstract
    virtual ~IPerson() = 0; // it's pure now so should be implemented below
    // virtual ~IPerson() = default; - virtual, but NOT pure = whole class - mix of pure and impure virtual func!
};

IPerson::~IPerson() {}  // must still define it (body can be empty)
// can also be written as IPerson::~IPerson() = default;

// virtually inheriting IPerson to avoid diamond inheritance problem!
class Teacher: virtual public IPerson{
protected:
    double salary;
    static int teacherCount; // static variable inside class - shared across all Teachers (and TAs) - should declare outside
    // inline static int teacherCount = 0;  // definition + initialization right here allowed in C++ 17
public:
    int id;
    string name;
    string dept;
    friend class HR;

    // Teacher(){ 
    //     cout<<"Default Constructor overloaded!";
    // }

    Teacher(){ // Non-parameterized Constructor
        id = 0; name = ""; dept = ""; salary = 0.0;
        ++teacherCount;
    }

    // Good practice to write const in parameter's and use address saves time copying here again for pass by value.
    Teacher(const int id,const string &name,const string &dept,const double salary){
        this->id = id;
        this->name = name;
        this->dept = dept;
        setSalary(salary);
        ++teacherCount;
    }

    // Setter
    void setSalary(const double salary){
        this->salary = salary;
    }

    void setSalary(const double salary, double discount){ // Function overloading
        this->salary = salary * (1-discount)/100;
    }

    // Getter
    double getSalary() const{
        return salary;
    }

    static int getTeacherCount(){ // NEW: can be called as Teacher::getTeacherCount()
        return teacherCount;
    }

    // virtual void getInfo () const override { - writing virtual here is redundant! as already written in interface.
    void getInfo () const override {
        cout<<"#"<<id<<": "<<name<<" from "<<dept<<" dept, earns "<<"$"<<getSalary()<<"/yr!"<<endl;
        cout<<"Total Teachers = "<<teacherCount<<endl;
    }

    // ~Teacher() override = default; // if you don't want to write anything in the destructor keep it as default!
    ~Teacher() override {
        --teacherCount;
    }
};

int Teacher::teacherCount = 0; // IMPORTANT TO DEFINE STATIC VARIABLE IN CLASS!

class Student: virtual public IPerson{
private:
    double fees;
public:
    const int id;
    int age;
    string name;
    int **matrix;
    int size;

    friend void waiveFees(Student &s, double amount);

    Student():id(0){ // No need to write this as constructor with 0 args is already handled with the below constructor!
        this->age = 18;
        this->name = "";
        this->size = 3;
        setFees(0);

        // Allocate Matrix
        matrix = new int*[size];
        for (int i = 0; i < size; ++i)
            matrix[i] = new int[size];
        // Initialize Matrix
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                matrix[i][j] = i + j;
    }

    // Constructor as Initialization List
    Student(int id=0, int age=18, string name="", double fees=0.0, int size=3): id(id), age(age), name(name), size(size){
        // this->id = id; - not allowed as declared constant!
        setFees(fees);

        // Allocate Matrix
        matrix = new int*[size];
        for (int i = 0; i < size; ++i)
            matrix[i] = new int[size];
        // Initialize Matrix
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                matrix[i][j] = i + j;
    }

    // Shallow copy - is already handled by the default copy constructor!
    Student(const Student &s):id(s.id), age(s.age), name(s.name), size(s.size){ //Deep Copy
        this->setFees(s.getFees());
        // Allocate New Matrix
        matrix = new int*[size];
        for (int i = 0; i < size; ++i)
            matrix[i] = new int[size];
        // Copy Values
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                matrix[i][j] = s.matrix[i][j];
    }

    Student& operator=(const Student &s){
        if (this == &s) {
            // self-assignment: s1 = s1;
            return *this;
        }

        // If, logically, a Student’s id should also change on assignment, 
        // then id probably shouldn’t be const, or you should delete operator=:
        // Student& operator=(const Student&) = delete;

        // id is const, so we CANNOT assign to it.
        // You might want to assert that ids are equal if that's a logical requirement:
        // if (id != s.id) { /* maybe throw or log error */ }
        // Note: I'm just copying the content of s2, keeping the original id of s3;

        this->age = s.age;
        this->name = s.name;
        this->setFees(s.getFees());

        // If sizes differ, reallocate matrix
        if (size != s.size) {
            // free old matrix
            if (matrix) {
                for (int i = 0; i < size; ++i)
                    delete[] matrix[i];
                delete[] matrix;
            }
            size = s.size;
            matrix = new int*[size];
            for (int i = 0; i < size; ++i)
                matrix[i] = new int[size];
        }
        // copy the matrix contents
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                matrix[i][j] = s.matrix[i][j];
        return *this;   // return *this, NOT a local
    }

    void setFees(const double fees){ // const parameters: whose values aren't changed inside the function
        this->fees = fees; // this function can't be constant
    }

    double getFees() const {
        return fees;
    }

    virtual void getInfo() const override { // const functions: functions that don't change the data members values of the class
        cout<<"#"<<id<<": "<<name<<", Age: "<<age<<", pays="<<getFees()<<" & has matrix: "<<"size="<<size<<endl;
        cout<<"Matrix"<<endl;
        for(int i=0; i<size; ++i){
            for(int j=0; j<size; ++j)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
    }

    ~Student() override{
        if(matrix){
            for(int i=0; i<size; ++i)
                delete[] matrix[i];
            delete[] matrix;
        }
        cout<<"#"<<id<<": "<<name<<", Age: "<<age<<", Matrix of size "<<size<<" is deleted!"<<endl;
    }
};

class GradStudent : public Student{
public:
    bool doingResearch;
    GradStudent(int id=0, int age=18, string name="", double fees=0.0, bool doingResearch=true): 
        Student(id, age, name, fees), doingResearch(doingResearch){}
};

class TA : public Student, protected Teacher{
public:
    TA(int id=0, int age=18, string name="", double fees=0.0, string dept="", 
        double salary=0.0, bool doingResearch=true): 
            Student(id, age, name, fees), Teacher(id, name, dept, salary){}
    
    void getInfo() const override{
        cout << "===== TA Info =====\n";
        cout << "[As Student] ";
        Student::getInfo();   // call Student version
        cout << "[As Teacher] ";
        Teacher::getInfo();   // call Teacher version
    }

    ~TA() override{
        cout<<"Destructor from TA class says Hi!"<<endl;
    }
};

void demoStaticVar(){
    static int count = 0;
    cout<<"[Static variable] count, called "<<++count<<" times!"<<endl;
}

void demoStaticObj(){
    // This is how singletons / caches / loggers are often implemented: static objects that live for the whole run.
    static Student classRep(999, 22, "Static-Rep", 5178, 2);
    cout<<"[demoStaticObject] Class Representative info:"<<endl;
    classRep.getInfo();
}

void waiveFees(Student &s, double amount){
    cout<<"[Friend Func] Waiving $"<<amount<<" for "<<s.name<<endl;
    s.fees -= amount;
}

class HR{
public:
    void raise(Teacher &t, int percentage){
        cout<<"[HR] Teacher "<<t.name<<" old salary ="<<t.salary<<endl; 
        t.salary = t.salary* ((100 + percentage)*1.0)/100;
        cout<<"[HR] Teacher "<<t.name<<" new salary ="<<t.salary<<endl; 
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Teacher Class
    Teacher t1(0001, "Steve", "CSE", 100000.00);
    Teacher t2(0002, "Jacob", "MAE", 250000.00);
    t2.setSalary(200000);
    t1.getInfo();
    t2.getInfo();

    // Student Class
    Student s1(101, 25, "Harry", 10000);
    s1.getInfo();
    Student s2(s1); // Deep copy constructor
    s2.getInfo();
    // After deep copying and changing s2 fees & matrix!
    s2.setFees(12000);
    s2.matrix[0][0]=1;
    s1.getInfo();
    s2.getInfo();
    // with diff id and size! - be careful sending parameters to initialization list!
    Student s3(201, 23, "Haseeb", 5000, 4);
    s3 = s2;
    s3.getInfo();

    // Grad Student Class
    GradStudent g1(301, 27, "MS-Harry", 18000, true);
    g1.getInfo();

    // TA Class
    TA ta1(401, 26, "TA-John", 9000, "CSE", 60000.0, true);
    ta1.getInfo(); // calls TA::getInfo() which prints both Student + Teacher info

    // Runtime Polymorphism: Student *ta2 = new TA();
    Student *ta2 = new TA(402, 27, "TA-Niall", 7500, "MPAc", 75000.0, false); // this is actual runtime polymorphism
    ta2->getInfo();
    delete ta2;

    // Runtime Polymorphism: IPerson *ta2 = new TA();
    IPerson *ta3 = new TA(402, 27, "TA-Niall", 7500, "MPAc", 75000.0, false); // this is actual runtime polymorphism
    // ta3 fails because of the diamond multiple inheritance issue described above!: solution - use virtual inhertance!
    ta3->getInfo();
    delete ta3;

    // Static Variable in Function Check
    demoStaticVar();
    demoStaticVar();
    demoStaticVar();

    // Static Variable in Class Check
    cout<<"Teachers count from main = "<<Teacher::getTeacherCount()<<endl;

    // Static Object Check
    demoStaticObj();

    // Friend Function Check
    s2.getInfo();
    waiveFees(s2, 100);
    s2.getInfo();

    // Friend Class Check
    HR h;
    h.raise(t1, 50);

    return 0;
}