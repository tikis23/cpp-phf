# cpp-phf: C++ compile time perfect hashes

Compile time `unordered_map`/`set` with perfect minimal hashes (no collisions), which provide faster lookups.

Keys must be know at compile time, but values for `unordered_map` can be changed at runtime.

## WORK-IN-PROGRESS
Currently this is only a prototype/demonstration of minimal perfect hash calculation at runtime. `unordered_map`/`set` will be added later.

## Todo
- perfect hash calculation moved to compile time
- constexpr `unordered_map`/`set` interfaces
- tests & benchmarks
- optimizations

## References
https://stevehanov.ca/blog/?id=119