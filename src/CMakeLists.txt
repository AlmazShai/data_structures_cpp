set(mainSrc
        main.cpp
        SharedPtr.hpp
        Trie.hpp
        Vector.hpp)

add_executable(Main
        ${mainSrc})

target_include_directories(Main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)