# C++ OOPS – Cheatsheet (with Code Insights)

> *Redacted using GPT 5.3: Thinking Model*

## 1. Object & Class

- **Object**: A real-world entity / instance of a class  
  Example: `Teacher t1(1, "Steve", "CSE", 100000);`
- **Class**: Blueprint for creating objects; defines **data members** and **member functions**.  
  Example: `Teacher`, `Student`, `TA` are all classes.

---

## 2. Class Structure

A class typically contains:

- **Data members / attributes / fields / properties**
- **Member functions / methods**
- **Constructors**
- **Destructor**
- **Access specifiers**: `public`, `private`, `protected`
- `Getters / setters`

Optional:

- `static` members  
- `friend` functions / classes  
- `virtual` functions  
- Operator overloads  

Example from the code:

```cpp
class Teacher : virtual public IPerson {
protected:
    double salary;
    static int teacherCount;   // shared across all Teacher objects
public:
    int id;
    string name;
    string dept;

    Teacher();
    Teacher(const int id, const string &name, const string &dept, const double salary);
    void setSalary(const double salary);
    double getSalary() const;
    static int getTeacherCount();
    void getInfo() const override;
    ~Teacher() override;
};
```

---

## 3. Constructors

A **constructor** is a special function called automatically when an object is created.

### 3.1 Types of Constructors

1. **Default Constructor**
   - Takes no parameters **or** all parameters have default values.
   - If you define **no** constructor, the compiler generates a default one.
   - Once you define any constructor, the compiler **does not** generate a default one automatically (unless you explicitly declare `= default`).

   ```cpp
   class Student {
   public:
       Student() = default;  // explicitly defaulted
       // or
       Student(int id = 0, int age = 18, string name = "", double fees = 0.0);
   };
   ```

2. **Non-parameterized Constructor**

   ```cpp
   Teacher::Teacher() {
       id = 0; name = ""; dept = ""; salary = 0.0;
       ++teacherCount;
   }
   ```

3. **Parameterized Constructor**

   ```cpp
   Teacher::Teacher(const int id,const string &name,const string &dept,const double salary) {
       this->id = id;
       this->name = name;
       this->dept = dept;
       setSalary(salary);
       ++teacherCount;
   }
   ```

4. **Copy Constructor**

   ```cpp
   Student::Student(const Student &s)
       : id(s.id), age(s.age), name(s.name), size(s.size) {
       setFees(s.getFees());
       // Deep copy of matrix
       matrix = new int*[size];
       for (int i = 0; i < size; ++i)
           matrix[i] = new int[size];
       for (int i = 0; i < size; ++i)
           for (int j = 0; j < size; ++j)
               matrix[i][j] = s.matrix[i][j];
   }
   ```

### 3.2 Shallow vs Deep Copy

- **Shallow copy**
  - Copies member values as-is (default behavior).
  - For raw pointers, both objects point to the same memory.

- **Deep copy**
  - Allocates new memory and copies the pointed-to content.
  - Used in the `Student` copy constructor to own its own `matrix`.

### 3.3 Copy Assignment Operator

Used when assigning one existing object to another:

```cpp
Student s3(201, 23, "Haseeb", 5000, 4);
s3 = s2;  // calls operator=
```

Implementation:

```cpp
Student& Student::operator=(const Student &s) {
    if (this == &s) return *this; // self-assignment guard

    // id is const: cannot be assigned; we keep original id
    age = s.age;
    name = s.name;
    setFees(s.getFees());

    // reallocate matrix if sizes differ
    if (size != s.size) {
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

    // copy matrix contents
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i][j] = s.matrix[i][j];

    return *this;
}
```

**Copy constructor vs copy assignment:**

- Copy constructor: called on **creation** → `Student s2(s1);`
- Copy assignment: called on **assignment** → `s3 = s2;`, can be called many times.

### 3.4 Rule of 3

If a class manages a resource (`new`/`delete`), you usually need:

1. **Destructor**  
2. **Copy constructor**  
3. **Copy assignment operator**  

`Student` correctly implements all three → good example of the **Rule of 3**.

---

## 4. Destructors

- Special member function called when an object goes out of scope or `delete` is used.
- Name: `~ClassName()`.
- Used for cleanup (freeing heap memory, closing files, etc.).

```cpp
Student::~Student() override {
    if (matrix) {
        for (int i = 0; i < size; ++i)
            delete[] matrix[i];
        delete[] matrix;
    }
    cout << "#" << id << ": " << name 
         << ", Age: " << age 
         << ", Matrix of size " << size << " is deleted!" << endl;
}
```

> **Polymorphic types:** If you delete derived objects through a base pointer, the **base class destructor must be virtual**.

```cpp
class IPerson {
public:
    virtual ~IPerson() = 0;
};
IPerson::~IPerson() {}
```

---

## 5. `this` Pointer

- `this` is a special pointer inside non-static member functions.
- Points to the **current object**.
- `this->x` is equivalent to `(*this).x`.

```cpp
void Teacher::setSalary(const double salary){
    this->salary = salary;
}
```

---

## 6. Initialization List & `const`

### 6.1 Initialization List

- Preferred way to initialize members, especially:
  - `const` data members  
  - Reference members  
  - Base classes  

```cpp
Student::Student(int id, int age, string name, double fees, int size)
    : id(id), age(age), name(name), size(size) {
    setFees(fees);
    ...
}
```

### 6.2 `const` Variants

1. **`const` data members**

   ```cpp
   class Student {
   public:
       const int id;  // must be set in init list
       ...
   };
   ```

2. **`const` parameters**

   ```cpp
   void setFees(const double fees) {
       this->fees = fees;
   }
   ```

3. **`const` member functions**

   ```cpp
   double getFees() const {
       return fees;
   }

   void getInfo() const override {
       ...
   }
   ```

---

## 7. Access Specifiers

- **`public`**: Accessible from anywhere.
- **`private`**: Accessible only inside the class and its friends.
- **`protected`**: Accessible inside the class, its friends, and derived classes.

Example:

```cpp
class Teacher {
protected:
    double salary;   // accessible by derived classes & friends
public:
    int id;
    string name;
    string dept;
};
```

---

## 8. Core OOP Concepts

### 8.1 Encapsulation

- Wrapping data and methods into a single unit (**class**).
- Typically keep data `private`/`protected` and use getters/setters.

### 8.2 Inheritance

> Reuse base class data members and functions in a derived class.

**Modes of Inheritance:**

```cpp
class Base { public: int x; protected: int y; private: int z; };

class DerivedPublic   : public Base   {};  // x: public, y: protected
class DerivedPrivate  : private Base  {};  // x,y: private in Derived
class DerivedProtected: protected Base{};  // x,y: protected in Derived
```

**Types of Inheritance:**

- Single  
- Multi-level  
- Multiple  
- Hierarchical  
- Hybrid  

Your code uses:

- **Multiple inheritance**:

  ```cpp
  class TA : public Student, protected Teacher { ... };
  ```

- **Virtual inheritance** to solve the diamond problem:

  ```cpp
  class IPerson {
  public:
      virtual void getInfo() const = 0;
      virtual ~IPerson() = 0;
  };

  class Teacher : virtual public IPerson { ... };
  class Student : virtual public IPerson { ... };
  class TA : public Student, protected Teacher { ... };
  ```

Without `virtual`, `TA` would have **two separate** `IPerson` subobjects.

### 8.3 Polymorphism

> Same interface, different behavior.

#### 8.3.1 Compile-Time Polymorphism (Static)

Via:

- **Function overloading**
- **Constructor overloading**
- **Operator overloading**

Example:

```cpp
void setSalary(const double salary);
void setSalary(const double salary, double discount); // overload
```

> Overloading is based on different parameter lists (types/number), not return type alone.

#### 8.3.2 Run-Time Polymorphism (Dynamic)

Via:

- **Virtual functions**
- **Function overriding**

Requires:

- `virtual` function in base
- Derived class overriding it
- Base pointer/reference pointing to derived object

```cpp
class IPerson {
public:
    virtual void getInfo() const = 0;
    virtual ~IPerson() = 0;
};

class Student : virtual public IPerson {
public:
    void getInfo() const override {
        ...
    }
};

IPerson *p = new Student(...);
p->getInfo();    // calls Student::getInfo() at runtime
delete p;
```

Your usages:

```cpp
Student *ta2 = new TA(...);
ta2->getInfo();   // TA::getInfo()

IPerson *ta3 = new TA(...);
ta3->getInfo();   // TA::getInfo()
```

### 8.4 Abstraction vs Data Hiding

- **Abstraction**:
  - Hiding complex implementation details.
  - Providing a clean interface (e.g., abstract class, pure virtual methods).

- **Data Hiding**:
  - Restricting direct access to internal data (via `private`/`protected`).

---

## 9. Abstract Class & Interfaces

- A class is **abstract** if it has at least one **pure virtual function**.
- Cannot be instantiated directly.
- Used as a base class to define an interface.

```cpp
class IPerson {
public:
    virtual void getInfo() const = 0; // pure virtual
    virtual ~IPerson() = 0;           // pure virtual destructor
};

IPerson::~IPerson() {} // still needs a definition
```

- Abstract class may also contain:
  - Concrete (non-virtual) functions  
  - Non-pure virtual functions  
  - Data members  

---

## 10. `static` Keyword

### 10.1 Static Variables Inside Functions

- Lifetime: entire program.
- Scope: inside that function only.
- Initialized only once.

```cpp
void demoStaticVar() {
    static int count = 0;
    cout << "[Static variable] count, called " << ++count << " times!" << endl;
}
```

### 10.2 Static Data Members (Inside Class)

- Shared by **all** instances of the class.
- Need a single definition outside the class:

```cpp
class Teacher {
    static int teacherCount;
public:
    static int getTeacherCount();
};

int Teacher::teacherCount = 0;   // definition
```

- C++17 shortcut:

```cpp
class Teacher {
    inline static int teacherCount = 0;
};
```

### 10.3 Static Member Functions

- Belong to the class rather than to an object.
- No `this` pointer; can only access static members directly.

```cpp
static int getTeacherCount() {
    return teacherCount;
}

cout << Teacher::getTeacherCount() << endl;
```

### 10.4 Static Objects

- `static` objects inside a function are:
  - Created once
  - Persist for the entire program

```cpp
void demoStaticObj() {
    static Student classRep(999, 22, "Static-Rep", 5178, 2);
    classRep.getInfo();
}
```

---

## 11. Friend Function & Friend Class

### 11.1 Why `friend`?

`private` / `protected` members are normally inaccessible from outside.  
`friend` allows **specific** external functions or classes to access these members without making them public.

### 11.2 Friend Function

```cpp
class Student {
    friend void waiveFees(Student &s, double amount);
    ...
};

void waiveFees(Student &s, double amount) {
    cout << "[Friend Func] Waiving $" << amount << " for " << s.name << endl;
    s.fees -= amount;   // direct access to private member
}
```

### 11.3 Friend Class

```cpp
class Teacher {
    friend class HR;
protected:
    double salary;
    ...
};

class HR {
public:
    void raise(Teacher &t, int percentage) {
        cout << "[HR] Teacher " << t.name << " old salary =" << t.salary << endl;
        t.salary = t.salary * ((100 + percentage) * 1.0) / 100;
        cout << "[HR] Teacher " << t.name << " new salary =" << t.salary << endl;
    }
};
```

---

## 12. What This Example Demonstrates

This code combines almost all major C++ OOP concepts:

- **Abstract base class**: `IPerson`  
- **Pure virtual function** + pure virtual destructor  
- **Virtual inheritance**: `Teacher`, `Student`  
- **Multiple inheritance**: `TA` from `Student` and `Teacher`  
- **Runtime polymorphism** via `virtual` + `override`  
- **Rule of 3** in `Student`  
- **Deep copy** of dynamically allocated `matrix`  
- **Static variables and static methods** in `Teacher`  
- **Static locals & static objects** in demo helpers  
- **Friend function** (`waiveFees`) and **friend class** (`HR`)  
- **Const correctness**: `const int id`, `const` getters, `const` `getInfo()`  
