# Usage

If benchmarks take a very long time to compile, increase `PHF_MEMORY_OVERHEAD` at `src/bm_unordered_map_at.cpp`.

to build the benchmarks:
```
cmake -E make_directory "build"
cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=OFF -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -S . -B "build"
cmake --build "build" --config Release
```

The compiled executable can be found at `build/phfbench` or `build/phfbench.exe` on windows.