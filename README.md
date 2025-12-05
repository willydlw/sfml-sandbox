# sfml-sandbox

This is a place to experiment with SFML and ImGui.


## How to build this repo 

```cmake
cmake -B build 
cmake --build build
```

OR

```cmake
mkdir build && cd build 
cmake ..
cmake --build .
```

## Subdirectories

### dependencies

The CMakeLists.txt in the dependencies subdirectory fetches the SFML, Imgui, and ImGui-SFML source code from their github repositories.


| Library | Git Tag |
| --- | --- |
| SFML | 3.0.2 |
| ImGui | 1.92.5 |
| ImGui-SFML | 3.0 |



Thank you to Elias Daler for the incredibly helpful tutorial and CMake template at https://github.com/eliasdaler/cmake-fetchcontent-tutorial-code 


<u><strong>ImGui Build Error Correction</strong></u>

ImGui Git Tag v1.92.5 generates two easy to fix errors when building. If you don't want to deal with the error correction, change  GIT_TAG v1.92.5 to GIT_TAG v1.91.9 in the [CMakeLists.txt](./dependencies/CMakeLists.txt) file and then follow the build steps again.


<strong>Error 1 Message</strong>:

```bash
imgui-sfml-src/imgui-SFML.cpp: In function ‘void {anonymous}::RenderDrawLists(ImDrawData*)’:
/build/_deps/imgui-sfml-src/imgui-SFML.cpp:956:28: error: no match for ‘operator!=’ (operand types are ‘ImTextureRef’ and ‘ImTextureID’ {aka ‘long long unsigned int’})
  956 |     assert(io.Fonts->TexID != (ImTextureID) nullptr); // You forgot to create and set font texture
```

<strong>Error 1 Correction</strong>:

Open the imgui-SFML.cpp file at  */build/_deps/imgui-sfml-src/imgui-SFML.cpp:956* and to go line 956. Replace

```c++
assert(io.Fonts->TexID != (ImTextureID) nullptr); // You forgot to create and set font texture
```

with

```c++
assert(io.Fonts->TexRef._TexData != nullptr); // You forgot to create and set font texture
```


<strong>Error 2 Message:</strong>

```bash
imgui-sfml-src/imgui-SFML.cpp:1043:92: error: ‘const struct ImDrawCmd’ has no member named ‘TextureId’
 1043 |                     const GLuint textureHandle = convertImTextureIDToGLTextureHandle(pcmd->TextureId);
```

<strong>Error 2 Correction:</strong>

Go to line 1043 and replace

```c++ 
const GLuint textureHandle = convertImTextureIDToGLTextureHandle(pcmd->TextureId);
```

with 

```c++ 
const GLuint textureHandle = convertImTextureIDToGLTextureHandle(pcmd->GetTexID());
```

Save and close the file. Next, perform the ```CMake --build build``` step again.
