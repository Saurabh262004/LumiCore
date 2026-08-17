g++ `
    src/*.cpp `
    src/Window/*.cpp `
    Main.cpp `
    external/glad/glad.c `
    -Iinclude `
    -Iexternal `
    -lglfw3 `
    -Iopengl32 `
    -o tests/win/app

.\tests\win\app.exe
