# Design_Patterns

>In software engineering, a design pattern is a general repeatable solution to a commonly occurring problem in software design. A design pattern isn't a finished design that can be transformed directly into code. It is a description or template for how to solve a problem that can be used in many different situations.


## Uses of Design Patterns

>Design patterns can speed up the development process by providing tested, proven development paradigms. Effective software design requires considering issues that may not become visible until later in the implementation. Reusing design patterns helps to prevent subtle issues that can cause major problems and improves code readability for coders and architects familiar with the patterns.

>Often, people only understand how to apply certain software design techniques to certain problems. These techniques are difficult to apply to a broader range of problems. Design patterns provide general solutions, documented in a format that doesn't require specifics tied to a particular problem.

>In addition, patterns allow developers to communicate using well-known, well understood names for software interactions. Common design patterns can be improved over time, making them more robust than ad-hoc designs.

## Active Object

* A proxy, which provides an interface towards clients with publicly accessible methods.
* An interface which defines the method reques on an active object.
* A list of pending requests from clients.
* A scheduler, which decides which request to execute next.
* The implementation of the active object method.
* A callback or variable for the client to receive the result.


## Guard
>a guard is a boolean expression that must evaluate to true if the program execution is to continue in the branch in question. The guard provides an early exit from a subroutine, and is a commonly used deviation from structured programming, removing one level of nesting and resulting in flatter code.

## Singleton

>the singelton pattern restricts the instantiation of a class to one "single" instance. This is useful when exactly one object is needed to coordinate actions across the sytem.

>Singleton is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.

![](https://refactoring.guru/images/patterns/content/singleton/singleton.png?id=108a0b9b5ea5c4426e0afa4504491d6f)

## Problem

>The Singleton pattern solves two problems at the same time, violating the Single Responsibility Principle:

>Ensure that a class has just a single instance. Why would anyone want to control how many instances a class has? The most common reason for this is to control access to some shared resource—for example, a database or a file.

>Here’s how it works: imagine that you created an object, but after a while decided to create a new one. Instead of receiving a fresh object, you’ll get the one you already created.

>Note that this behavior is impossible to implement with a regular constructor since a constructor call must always return a new object by design.

![](https://refactoring.guru/images/patterns/content/singleton/singleton-comic-1-en.png?id=157509c5693a657ba465c7a9d58a7c25)


# Reactor
>The reactor design pattern is an event handling pattern for handling service requests delivered concurrently to a service handler by one or more inputs. The service handler then demultiplexes the incoming requests and dispatches them synchronously to the associated request handlers.


![](https://slidetodoc.com/presentation_image_h/136c7afd59593191617eb0651f9f30e6/image-20.jpg)

## How to use the programm:
```bash
$ "PUSH [your input]" : inserting element into the queue 
$ "EXIT" : to exit the programm and close the connection between the client and the server
```

## Running Programm:
```bash
# Clone the repository
$ git clone https://github.com/bsharabi/Design_Patterns.git
# Go into the repository
$ cd Design_pattern
# Open the terminal on Linux
$ Run "make run"
$ -- Q1-3 -- 
$ Run main1 "./main"
$ Run client "./client"
$ -- Q4 -- 
$ Run guard "./guard"
$ -- Q5 -- 
$ Run Singelton "./Singelton"
$ -- Q6 -- 
$ Run Reactor "./reactor"
```

## Running Test:

```bash
# Clone the repository
$ git clone https://github.com/bsharabi/Design_Patterns.git
# Go into the repository
$ cd Design_pattern
# Open the terminal on Linux
$ Run "make run"
$ Run Test "./test"
```

## Cleaning files:
```bash
$ Run "make clean"
```