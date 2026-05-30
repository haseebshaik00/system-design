# System Design

**Rundown of all System Design Concepts!**

> [**JP'25 System Design**](https://docs.google.com/document/d/1ZjTLt6h9kvXwfFZaUnJOGhsSgwEkXS2lBqRiGFbD-TA/edit?usp=sharing)

## CPP OOPS

- **Official:** [Notes](OOPS/1-oops-cheatsheet.md) | [Code](OOPS/2-oops.cpp)
- **Personal:** [Notes](OOPS/3-oops-cheatsheet-practice.md) | [Code](OOPS/4-oops-practice.cpp)

## LLD (Low-Level Design) Basics

### [1] What is Low-Level Design (LLD)?
- [What is LLD?](https://algomaster.io/learn/lld/what-is-lld)

### [2] What do interviewers look for during LLD interviews?

- **Object-Oriented Programming (OOPS)**
- **Design Principles**
- **Design Patterns**
- **Problem Solving**
- **Clean Coding**
- **Communication and discussing tradeoffs**

### [3] Quality Factors of Clean Code!
| Factor                    | Meaning in Clean Code / LLD                                                                                                                            |
| ------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Maintainability**       | Code should be easy to read, debug, modify, and fix without breaking unrelated parts.                                                                  |
| **Scalability**           | Components should handle growth gracefully, such as more users, more data, or more notification types.                                                 |
| **Extensibility**         | You should be able to add new features with minimal changes to existing code. Example: adding `WhatsAppSender` without changing `NotificationManager`. |
| **Testability**           | Classes should be easy to unit test independently. This usually needs loose coupling and dependency on interfaces.                                     |
| **Reusability**           | Common components should be reusable in different parts of the system instead of duplicated.                                                           |
| **Readability**           | Another developer should quickly understand what the code does from class names, method names, and structure.                                          |
| **Modularity**            | The system should be divided into small, independent components with clear responsibilities.                                                           |
| **Loose Coupling**        | Classes should depend on abstractions/interfaces instead of concrete implementations.                                                                  |
| **High Cohesion**         | A class should contain only closely related responsibilities. For example, `EmailSender` should only handle email sending.                             |
| **Performance Awareness** | The design should not be unnecessarily slow or memory-heavy, especially when data volume grows.                                                        |
| **Simplicity**            | Avoid over-engineering. Use patterns only when they naturally solve the problem.                                                                       |
| **Collaborability**       | Code structure should be clear enough that multiple developers can work on different parts without confusion.                                          |

###

## SOLID Principles
