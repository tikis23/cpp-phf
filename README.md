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

From my testing, using strings as keys provides around 1.5x-2.0x speed-up compared to `std::unordered_map` when using `at()`.

## Todo
- tests & more benchmarks
- more TODO's in the code

## References
- http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a
- https://github.com/chys87/constexpr-xxh3