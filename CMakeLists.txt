cmake_minimum_required(VERSION 3.14)
project(su20-Hoffman-Project)
set (EXE_NAME Project)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "")
set (input02 "")
set (input03 "")
set (input04 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp AVL.h AVLTree.h Node.h RBTree.h RedBlack.h Splay.h STree.h Tree.h Test.cpp Test.h DocParse.h DocParse.cpp IndexWord.h IndexWord.cpp json.hpp Query.h Query.cpp User.h User.cpp)
#© 2020 GitHub, Inc.