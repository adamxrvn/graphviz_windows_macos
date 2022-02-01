# How to use Graphviz with C++ on Windows/Mac os

 1. Install Graphviz for [Windows](https://graphviz.org/download/#windows)/[Mac OS](https://graphviz.org/download/#mac) and remember the installation path. In my case it is "C:\\Program Files\\Graphviz".
 2. Next we need to add the libraries (files from "Graphviz\\lib") and its includes ("Graphviz\\include\\graphviz") to a project.
 3. Open CMakeLists.txt and define the location of our library using "set" command. Replace "C:/Program Files/Graphviz" with your path.
 ```cmake 
set(GRAPHVIZ_DIR "C:/Program Files/Graphviz") 
```
4. Add the libraries and includes
 ```cmake
file(GLOB GVC_LIBS "${GRAPHVIZ_DIR}/lib/*.lib")
target_link_libraries(${CMAKE_PROJECT_NAME} ${GVC_LIBS})
include_directories("${GRAPHVIZ_DIR}/include/graphviz")
```
You will end up with CMake like this
![CMakeLists](pictures/g_1.png "CMakeLists")


