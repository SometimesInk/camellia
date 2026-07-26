# camellia

## Building and Installing

Use CMake to build and install camellia for the local user. By default, the install directory is `$HOME/.local` as written in the `CMakePresets.json` file.

```sh
cmake -B build --preset debug # Create CMake build files
cmake --build build # Build
cmake --install build # Install to prefix directory
```
