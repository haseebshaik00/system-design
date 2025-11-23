#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class Teacher{
protected:
    double salary;
public:
    int id;
    string name;
    string dept;

    // Teacher(){ 
    //     cout<<"Default Constructor overloaded!";
    // }

    Teacher(){ // Non-parameterized Constructor
        id = 0; name = ""; dept = ""; salary = 0.0;
    }

    Teacher(int id, string name, string dept, double salary){
        this->id = id;
        this->name = name;
        this->dept = dept;
        setSalary(salary);
    }

    // Setter
    void setSalary(double salary){
        this->salary = salary;
    }

    // Getter
    double getSalary(){
        return salary;
    }

    void getInfo(){
        cout<<"#"<<id<<": "<<name<<" from "<<dept<<" dept, earns "<<"$"<<getSalary()<<"/yr!"<<endl;
    }

    ~Teacher(){}
};

class Student{
private:
    double fees;
public:
    const int id;
    int age;
    string name;
    int **matrix;
    int size;

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
    Student(const Student &s): id(s.id){ //Deep Copy
        this->age = s.age;
        this->name = s.name;
        this->size = s.size;
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
    
    void setFees(const double fees){ // const parameters: whose values aren't changed inside the function
        this->fees = fees; // this function can't be constant
    }

    double getFees() const {
        return fees;
    }

    void getInfo() const { // const functions: functions that don't change the data members values of the class
        cout<<id<<" "<<name<<" "<<age<<" "<<getFees()<<endl;
        cout<<"Matrix"<<endl;
        for(int i=0; i<size; ++i){
            for(int j=0; j<size; ++j)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
    }

    ~Student(){
        if(matrix){
            for(int i=0; i<size; ++i)
                delete[] matrix[i];
            delete[] matrix;
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Teacher t1(0001, "Steve", "CSE", 100000.00);
    Teacher t2(0002, "Jacob", "MAE", 250000.00);
    t2.setSalary(200000);
    t1.getInfo();
    t2.getInfo();

    Student s1(001, 25, "Harry", 10000);
    s1.getInfo();
    Student s2(s1); // Deep copy constructor
    s2.getInfo();
    // After deep copying and changing s2 fees & matrix!
    s2.setFees(12000);
    s2.matrix[0][0]=1;
    s1.getInfo();
    s2.getInfo();

    return 0;
}