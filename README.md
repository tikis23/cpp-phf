# cpp-phf: C++ compile time perfect hashes

Compile time `unordered_map`/`set` with perfect minimal hashes (no collisions), which provide faster lookups.

Keys must be know at compile time and cannot be modified at runtime.  
Values must be know at compile time and cannot be modified at runtime, except for `unordered_map` with `constinit`.

## Usage
As this is a header-only library, drop `phf` folder into your project and include headers that you need.  

## Example
Minimal example of usage can be found at `example.cpp`.  

To run the example, run `make all` to compile it. Output will be found in directory `bin`.  
- Requires C++23.
- By default used gcc. Change if needed in Makefile.

## Benchmarks

How to compile & run can be found at `benchmark/README.md`.

From my testing, using short strings as keys provides ~2x speed-up compared to `std::unordered_map` when using `at()`, while using long keys makes `phf::unordered_map` ~7-8x slower. Using faster hash algorithms should make it faster like with short keys. 

## Todo
- tests & more benchmarks
- optimizations (use faster hash algorithms)
- more TODO's in the code

## References
- http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a