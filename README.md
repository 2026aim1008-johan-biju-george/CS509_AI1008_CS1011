# CS509 Laboratory Repository

## Repository Overview

This repository contains the laboratory assignments completed for the **CS509 Software Laboratory**. Each assignment is organized into its own directory and contains the source code, headers, driver modules, test cases, documentation, and executable (where applicable).

A common wrapper program is provided to launch individual assignments through a single menu-driven interface.

---

## Pair Details

- **Student Name:** Johan Biju George 
- **Roll Number:** 2026AIM1008

- **Buddy Name:** Diwakar Patel
- **Roll Number:** 2026CSM1011

---

## Language and Environment

### Programming Language
- C++

### Compiler
- GNU g++ (MinGW-w64)

### Operating System
- Windows 11

### IDE
- Visual Studio Code

### C++ Standard
- C++17

---

## Directory Structure

```text
CS509_AI1008_CS1011/
│
├── assignment_01/
│   ├── driver/
│   ├── headers/
│   ├── src/
│   ├── tests/
│   ├── README.md
│   └── assignment1.exe
│
├── assignment_02/
│   └── ...
│
├── assignment_03/
│   └── ...
│
├── common_wrapper/
├── wrapper.exe
│
└── README.md
```

Each assignment directory contains:

- `driver/` – Assignment driver module
- `headers/` – Header files
- `src/` – Source code files
- `tests/` – Input/output test files
- `README.md` – Assignment-specific documentation

---

## Common Wrapper: Build and Usage

The common wrapper provides a single interface to launch any assignment.

### Build

Compile the wrapper using:

```bash
g++ common_wrapper/common_wrapper.cpp -o wrapper.exe
```

### Execute

Windows:

```bash
.\wrapper.exe
```

Linux/macOS:

```bash
./wrapper
```

### Menu

Example:

```text
CS509 Laboratory Wrapper

1. Assignment 1
2. Assignment 2
3. Assignment 3
...
0. Exit

Enter your choice:
```

Selecting an assignment launches its corresponding executable.

---

## Repository Organization

Each assignment is implemented independently and includes:

- Source code
- Driver module
- Test case generators
- Benchmarking utilities (where required)
- Assignment-specific README
- Input test files

---

## Compilation

Each assignment should be compiled independently from its respective directory.

Example:

```bash
g++ driver/driver.cpp src/*.cpp -o assignment1.exe
```

Refer to the individual assignment README for detailed compilation instructions.

---
