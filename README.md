# cpp-phf: C++ compile time perfect hashes

Compile time `unordered_map`/`set` with perfect minimal hashes (no collisions), which provide faster lookups.

Keys must be know at compile time and cannot be modified at runtime.  
Values must be know at compile time and cannot be modified at runtime, except for `unordered_map` with `constinit`.

## WORK-IN-PROGRESS
Currently contains only a minimal prototype of `unordered_map`.

## Usage
As this is a header-only library, drop `include` folder into your project and include headers that you need.  

# Example
Minimal example of usage can be found at `example.cpp`.  

To run the example, run `make all` to compile it. Output will be found in directory `bin`.  
- Requires C++23.
- By default used gcc. Change if needed in Makefile.


## Todo
- expanded `unordered_map` interface
- constexpr `unordered_set`
- tests & benchmarks
- optimizations
- make interfaces similar to stl
- add checks to make sure keys are unique
- more TODO's in the code

## References
- https://stevehanov.ca/blog/?id=119
- http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a