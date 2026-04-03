# Imp commands
- use wsl
- use `make clean && make test`
- `make test` runs predefined list of test cases, hardcoded in makefile
- `make` for simply compiling

# GOLEM Language Specification

# Grid-Oriented Logic for Entity Manipulation

### Akash Gupta - 23110020

### Kaushal Bule - 23110160

### Siddhesh Umarjee - 23110347

## 1 Overview

GOLEM (Grid-Oriented Logic for Entity Manipulation) is a domain-specific programming lan-
guage designed for specifying the behavior of autonomous agents operating within a discrete
two-dimensional grid world. The language focuses on spatial reasoning, deterministic execution,
and concise behavioral descriptions.

```
A GOLEM program defines:
```
- The geometry of the environment
- Static objects such as obstacles
- Behavioral templates called blueprints
- Initialization of the simulation through agent spawning
    Execution produces a final world state describing positions, orientations, and inventories of
all agents.

## 2 Fundamental Concepts

### 2.1 Grid World

- Finite rectangular grid
- Integer coordinate system
- Origin located at the top-left corner (0, 0)
- X increases eastward
- Y increases southward
    Each grid cell may contain empty space, an obstacle, items, or a golem.

### 2.2 Golems

Golems are autonomous agents that:

- Occupy exactly one grid cell
- Maintain orientation (north, south, east, west)
- Execute instructions sequentially
- Maintain an inventory of items


### 2.3 Blueprints

Blueprints are reusable behavior templates. Multiple golems may execute the same blueprint
definition.

## 3 Lexical Elements

### 3.1 Keywords

grid Declares grid dimensions and establishes coordinate bounds.
obstacle Places an immovable barrier that blocks movement.
blueprint Defines a reusable behavioural template for golems.
construct Begins simulation initialisation where agents are spawned.
spawn Instantiates a golem using a blueprint.
at Specifies spawn coordinates.
as Specifies aliases to blueprint objects.
go Moves the agent forward relative to orientation.
turn Changes orientation to a cardinal direction.
scan Inspects an adjacent grid cell without altering state.
pick Transfers an item into inventory.
drop Places an inventory item into the current cell.
if Conditional execution construct.
else Alternative branch for conditional execution.
repeat Executes statements a fixed number of times.
north, south, east, west
Directional constants.
true, false Boolean literals.

### 3.2 Operators

== Equality comparison.
!= Inequality comparison.
? Marks a directional operand as a scan query.

### 3.2a Arithmetic Operators

+ Addition
- Subtraction
* Multiplication
/ Integer Division (result is always integer, truncated toward zero)
% Modulo (remainder after integer division)

### 3.3 Directional Symbols

```
>> East scan shorthand
<< West scan shorthand
^^ North scan shorthand
vv South scan shorthand
```

### 3.4 Delimiters

`{ } ( ) ; ,`

### 3.5 Identifiers

`[a-z][a-zA-Z0-9_]*`

### 3.6 Literals

- Integer values
- String literals for optional logging

### 3.7 Arithmetic Expressions

Arithmetic expressions evaluate to integers and can be used in:
- Grid dimensions: `grid(10, 20)`
- Movement: `go 5 + 3;`, `go 2 * 4;`
- Repetition: `repeat 10 / 2 { ... }`, `repeat 7 % 3 { ... }`
- Coordinates (grid, obstacles, spawn): `at (2 * 3, 4 + 1)`

Operator precedence (highest to lowest):
1. Parentheses `( )`
2. Unary minus `-` (right-associative)
3. Multiplication `*`, Division `/`, and Modulo `%` (left-associative)
4. Addition `+` and Subtraction `-` (left-associative)

### 3.8 Negative Numbers

When a negative integer appears in a `go` statement:
- If the value is exactly 0 (e.g., `-0` or `0 - 0`), the golem does not move
- If the value is negative (e.g., `-5`, `3 - 10`), the golem:
  1. Turns 180° from its current direction
  2. Moves forward by the absolute value of the number
  3. Ends facing the reversed direction

Examples:
```
go -5;          // Turn 180° and move 5 steps in that direction
go 3 - 8;       // Evaluates to -5: turn 180° and move 5 steps
go -0;          // No movement (zero case)
```

**Constraints:**
- Negative values are **NOT allowed** in:
  - Grid dimensions: `grid(-5, 10)` → Parse error
  - Obstacle coordinates: `obstacle(-2, 3)` → Parse error
  - Spawn coordinates: `spawn bot at (-1, 2)` → Parse error
- Repeat counts must be non-negative: `repeat -3 { }` → Parse error

## 4 Program Structure

A GOLEM program is composed of three ordered sections:

1. Grid Declaration
2. Blueprint Definitions
3. Simulation Construction

## 5 Language Constructs

### 5.1 Grid Declaration

```
grid(width, height) {
obstacle(x, y);
}
```
### 5.2 Blueprint Definition

```
blueprint name {
statements
}
```

### 5.3 Simulation Construction

```
construct {
spawn blueprintName at (x,y);
}
```

## 6 Statements

### 6.1 Movement

go n;


### 6.2 Rotation
```
turn north;
turn south;
turn east;
turn west;
```
### 6.3 Environment Scan
```
scan(direction?) == obstacle
scan(direction?) == empty
```
### 6.4 Item Interaction
```
pick item;
drop item;
```
### 6.5 Conditional Execution
```
if(condition) {
statements
}

if(condition) {
statements
} else {
statements
}
```
### 6.6 Repetition
```
repeat k {
statements
}
```
## 7 Execution Model

1. Grid initialized
2. Obstacles placed
3. Agents spawned
4. Each agent executes blueprint sequentially
5. Execution terminates when instructions complete

## 8 Semantic Constraints

- Movement outside grid is prohibited
- Collision with obstacles prevented
- Invalid spawn locations rejected
- Dropping non-existent items rejected
- Scan directions must be valid


## 9 Output Model

Execution produces a world-state report containing:

- Grid dimensions
- Obstacle coordinates
- For each golem:
    - Position
    - Orientation
    - Inventory contents

## 10 Example Programs

### 10.1 Simple Movement
```
grid(5,5) {}

blueprint walker {
go 3;
turn south;
go 1;
}

construct {
spawn walker as W1 at (0,0);
}

### 10.2 Obstacle Avoidance

grid(6,6) {
obstacle(2,0);
}

blueprint avoider {
repeat 3 {
if(scan(east?) == obstacle) {
turn south;
}
go 1;
}
}

construct {
spawn avoider at (0,0);
}
```
### 10.3 Item Transfer

```
grid(4,4) {}

blueprint collector {
pick gold;
go 1;
drop gold;
}

construct {
spawn collector at (1,1);
}
```

### 10.4 Arithmetic Operations

```
grid(20, 20) {
obstacle(5 + 3, 7);
obstacle(15 - 2, 8);
}

blueprint arithmetic_walker {
go 2 + 3;      // move 5 steps
go 10 / 2;     // move 5 steps (integer division)
repeat 2 * 3 { // repeat 6 times
  go 1;
}
turn south;
go (2 + 1) * 3; // move 9 steps (parentheses for grouping)
}

construct {
spawn arithmetic_walker at (1 + 1, 2);
spawn arithmetic_walker at (10 - 3, 15 / 3);
}
```

### 10.5 Negative Movement (Reverse Direction)

```
grid(10, 10) {}

blueprint reverser {
// Move forward
go 3;

// Move backward by turning 180° and stepping forward
go -2;

// Using arithmetic that results in negative
go 1 - 6;     // Evaluates to -5: turn 180° and move 5 steps

// Combination with conditionals
repeat 2 {
  go 4;
  go -2;  // Back up 2 steps
}
}

construct {
spawn reverser at (0, 0);
}
```
## 11 Conclusion

GOLEM provides a compact and expressive language for modeling autonomous agent behavior
within structured environments. Its constrained syntax and deterministic semantics enable clear
reasoning about spatial actions while remaining accessible for experimentation and demonstration.


