# digit-sim Project Documentation

## Overview
The `digit-sim` project is a digital circuit simulation toy that allows users to simulate both combinational and sequential logic circuits. It provides a simple and weak framework for modeling basic logic gates, multiplexers, decoders, flip-flops, latches and some popular MSIs.

## Components

### 1. `src/logic_gates.c`
This file contains functions to simulate basic logic gates.

### 2. `src/combinational.c`
This file contains functions to simulate combinational logic circuits using basic logic gates. 

### 3. `src/clock.c`
This file is designed to simulate clock signal in sequential logic circuits.

### 4. `src/sequential.c`
This file is designed to simulate sequential logic circuits. 

### 5. `main.c`
The main entry point for the application.

### 6. `include/`
This folder contains header files defining basic types and functions.

### 7. `example/`
This folder contains some examples.

### 8. `CMakeLists.txt`
The CMakeLists.txt contains the build instructions for the project. It specifies how to compile the source files and link them into an executable.

## Building the Project
To build the project, navigate to the project directory and run the following command:

```
cmake . build
```

This will compile the source files and create the executable.

## Running the Simulation
After building the project, you can run the simulation using the following command:

```
./build/digit-sim
```

---

*Note: This project is made just for fun.*
