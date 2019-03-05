cmake_minimum_required(VERSION 3.12)
project(EarthGRAM2016)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(EarthGRAM2016 STATIC
        Atmod1.cpp
        Atmod1.h
        AuxProf.cpp
        AuxProf.h
        HWM.cpp
        HWM.h
        Init.cpp
        Init.h
        InitP.cpp
        InitP.h
        JB2008.cpp
        JB2008.h
        Map.cpp
        Map.h
        MET.cpp
        MET.h
        MSIS.cpp
        MSIS.h
        NCEP.cpp
        NCEP.h
        Pert.cpp
        Pert.h
        RRA.cpp
        RRA.h)

set_property(TARGET EarthGRAM2016 PROPERTY POSITION_INDEPENDENT_CODE ON)