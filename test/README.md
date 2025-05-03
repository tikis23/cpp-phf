# Usage

to build the tests:
```
cmake -E make_directory "build"
cmake -DCMAKE_BUILD_TYPE=Release -S . -B "build"
cmake --build "build" --config Release
```

The compiled executable can be found at `build/phftest` or `build/phftest.exe` on windows.