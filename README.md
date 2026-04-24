# camellia

## Building and Installing

Use cmake to build and install to prefix directory. By default, the install directory is `$HOME/.local` as written in the `CMakePresets.json`.

```bash
cmake --preset debug # Create CMake build files
cmake --build build # Build
cmake --install build --preset build # Install to prefix directory
```
