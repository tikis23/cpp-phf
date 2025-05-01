# Usage

to build the benchmarks:
```
cmake -E make_directory "build"
cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=OFF -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -S . -B "build"
cmake --build "build" --config Release
```

The compiled executable can be found at `build/phfbench` or `build/phfbench.exe` on windows.