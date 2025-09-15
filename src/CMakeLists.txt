set(mainSrc
        main.cpp
        SharedPtr.hpp
        UniquePtr.hpp
        Trie.hpp
        Vector.hpp
        SpscQueue.hpp)

add_executable(Main
        ${mainSrc})

target_include_directories(Main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
