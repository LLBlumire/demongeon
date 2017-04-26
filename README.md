# Demongeon

Demongeon provides two makefiles, NMakefile which is designed for use with `MSVC`, and Makefile which is designed for use with `gcc`.

`nmake -f Nmakefile run` (on windows MSVC)

or

`make run` (on linux GNU C)

will build and run the program. The binary will be stored in `build/bin/demongeon.exe`.

## Code Layout

`src` contains all source files, `build` contains output files.

`src/cpp` contains all cpp code files

`src/hpp` contains all header files

`src/stp` contains all cpp sum type polymorphism markup (TOML) files (used with `cppstp` to generate some of the header files)

`build/obj` contains intermediary o files

`boild/bin` contains binaries


# CPPSTP

A build requirement if you wish to regenerate option and result and tile (note: tile will require modification after generation) then you need to build and install `cppstp`, this can be done if rust, and specifically `cargo` is installed on the current stytem. From inside the `cppstp` directiory

`cargo install`

will install it.

