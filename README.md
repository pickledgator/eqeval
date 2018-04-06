# Eqeval
A library that evaluates a system of equations. 

An application utilizing the library is provided where equations are read from an equations file, parsed and tokenized, and then evaluated such that all unique solutions for each variable in the equations file are found. If no unique solutions for all variables can be found, the input file is returned.

The implementation utilizes the shunting yard algorithm to sort the tokenized RHS expressions into reverse polish notation before being evalulated. While this design principal is over-designed for the single operator input constraints, it facilitates expansion of the library to support all operators.

## Setup

### MacOS
Make sure you have XCode/clang installed and setup
```
brew install bazel
```

### Ubuntu
```shell
sudo apt-get update
sudo apt-get install openjdk-8-jdk curl build-essential -y
sudo echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
```

## Build
```shell
cd eqeval
bazel build eqeval/...
```

## Run Tests
Example test cases (including two equation files) are provided as unit tests
```shell
bazel test eqeval/...
```

## Usage
An example application that reads an equation file from disk and then utilizes the evaluator library to solve the system of equations is provided as:
```shell
bazel-bin/eqeval/equation_evaluator -h
```

Available input arguments:
* `-f` - Path to equations file on disk
* `-h` - Show help

## Equations File Format
* An equation is defined by: `<LHS> = <RHS>`
* Each equation is specified on a separate line
* `<LHS>` is the left-hand side of the equation and is always a variable name
* A variable name is composed of letters from the alphabet ( for which `isalpha(c)` is true ).
* `<RHS>` is the right hand side of the equation and can be composed of:
  * variables
  * unsigned integers
  * the `+` operator

Example equations file format:
```
offset = 4 + random + 1
location = 1 + origin + offset
origin = 3 + 5
random = 2
```

## Assumptions
* The provided application will accept a filename as input
* The application will evaluate the system of equations and print the value of each variable on a new line
* The output will be sorted in ascending order by variable name
* If any variable doesn't have a well-defined and unique solution, this indicates an error in input so the application will print the exact contents of the input file
* All other debug output has been suppressed
  * Exception to this: File read errors
* If two identical solutions are found for the same variable, it is assumed to be a valid solution
* If two non-identical solutions are found for the same variable, it is assumed to be an invalid solution

## Comments
For this project, I designed and implemented a robust library that could be used with different input sources and that could be extended to solve more complex systems of equations and operators. In this specific case, the first type of input source is an equations file read from disk. By standardizing the library's interfaces as a vector of strings, input data can be obtained in any variety of ways (eg, from a file, from a database, from a tcp socket, etc.).

To solve the more generalized problem of evaluating a system of equations, I chose to implement the shunting yard algorithm using an operator stack, which works by sorting a list of tokenized components of an equation into postfix notation (reverse polish), and then evaluates the postfix list of tokens from left to right using another stack. While this algorithm is overkill when only a single operator is used (no precedence, associativity or brackets priorities), I took the opportunity to learn and understand a new algorithm that I had never worked with before. It also provides for the ability to extend the library to support more complex equations without much of a refactor.

I chose to use bazel as the build system due to its intuitive dependency packaging and deterministic output.