set(mainSrc
        main.cpp
        SharedPtr.hpp
        Trie.hpp
        Vector.hpp)

add_library(MainLib STATIC
        ${mainSrc})

target_include_directories(MainLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)