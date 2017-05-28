cmake_minimum_required(VERSION 2.8)
add_executable(Main
	Main.cpp
	Block.cpp
	Placement.cpp
	Field.cpp
	Utility.cpp
	ZobristHashing.cpp
	BeamSearch.cpp
)
add_definitions("-std=c++11")
add_definitions("/O2")
add_definitions("/Ob2")
add_definitions("/Ot")
add_definitions("/Oi")

