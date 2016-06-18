cmake_minimum_required(VERSION 2.8)
project(MultiRate_SparseMatrix)

#set(CMAKE_CXX_COMPILER $(mkCxxCompiler))
set(CMAKE_CXX_COMPILER "/u/geo2/sw/Packages/compilers/gcc+system/4.9/bin/g++")
set(CMAKE_CXX_FLAGS " -g -std=c++11")

#ADD_SUBDIRECTORY( src )

FILE (GLOB SRCFILES src/AllenCahnRHSFunction/*.cpp src/BESolver/*.cpp src/BESolverNewtonFunction/*.cpp src/ChemicalProblemsUtils/*.cpp src/ChemicalSystemTools/*.cpp src/ConstantBCFunction/*.cpp src/CubicHermiteInterpolationSolver/*.cpp src/FESolver/*.cpp src/GeochemistryRHSFunction/*.cpp src/HyperbolicEquationUpwindRHSFunction/*.cpp src/HyperbolicEquationRusanovFlux/*.cpp
 src/LinearInterpolationSolver/*.cpp src/InterpolationSolver/*.cpp src/MasterSolverOutputManipulator/*.cpp src/MultiRateTRBDF2Solver/*.cpp src/NewtonSolver/*.cpp 
 src/Restab/*.cpp src/SingleRateBESolver/*.cpp src/SingleRateFESolver/*.cpp src/SingleRateTRBDF2Solver/*.cpp src/TestCases/*.cpp src/TRBDF2Solver/*.cpp src/TRBDF2SolverNewtonFunction/*.cpp src/VectorUtility/*.cpp src/*.cpp)

# header file (equivalent to -I on GCC)
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/Eigen"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/AllenCahnRHSFunction"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BESolver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BESolverNewtonFunction"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ChemicalProblemsUtils"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ChemicalSystemTools"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantBCFunction"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CubicHermiteInterpolationSolver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FESolver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/GeochemistryRHSFunction"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/HyperbolicEquationUpwindRHSFunction"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/HyperbolicEquationRusanovFlux"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/InterpolationSolver"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/LinearInterpolationSolver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/MasterSolverOutputManipulator"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/MultiRateTRBDF2Solver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/NewtonSolver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Restab"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SingleRateBESolver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SingleRateFESolver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SingleRateTRBDF2Solver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TestCases"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TRBDF2Solver"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TRBDF2SolverNewtonFunction"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VectorUtility"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)


ADD_EXECUTABLE(${PROJECT_NAME} src/main_solver.cpp ${SRCFILES})

