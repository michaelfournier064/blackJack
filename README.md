# Blackjack Backend Library

This project provides the core logic for a simple Blackjack game. It is refactored to be used as a backend library for a Godot project or as a small standalone executable.

## Building with CMake

This project uses CMake for a portable build. Ensure you have a C++17 capable compiler installed.

```
mkdir build && cd build
cmake ..
cmake --build .
```

The above commands produce the `blackjack` executable and a static library that can be linked with other projects.

## Usage

Run the game from the build directory:

```
./blackjack
```

When integrating with Godot, link against the generated `libblackjack.a` (or the appropriate library for your platform) and use the public headers in `include/`.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
