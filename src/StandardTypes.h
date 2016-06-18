#ifndef _STANDARD_TYPES_H_
#define _STANDARD_TYPES_H_

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Sparse>

#include <iostream>
#include <iomanip>

//! Standard Types
namespace Utils {

typedef double Real;
typedef bool Bool;
typedef int Integer;
typedef std::string String;
typedef char Char;

typedef Eigen::Matrix<Char, Eigen::Dynamic, 1> CharVector;
typedef Eigen::Matrix<String, Eigen::Dynamic, 1> StringVector;
typedef Eigen::Matrix<Bool, Eigen::Dynamic, 1> BoolVector;
typedef Eigen::Matrix<Real, Eigen::Dynamic, 1> RealVector;
typedef Eigen::Matrix<Integer, Eigen::Dynamic, 1> IntegerVector;
typedef Eigen::Matrix<Real, Eigen::Dynamic, Eigen::Dynamic> RealMatrix;
typedef Eigen::Matrix<Integer, Eigen::Dynamic, Eigen::Dynamic> IntegerMatrix;


typedef Eigen::SparseMatrix<Real>  RealMatrixSparse;
typedef Eigen::SparseMatrix<Integer>  IntegerMatrixSparse;

typedef std::map<String,Integer> MapInteger;
typedef std::map<String,Real> MapReal;

typedef std::pair<String,Integer> KeyInteger;
typedef std::pair<String,Real> KeyReal;

}

#endif /* _STANDARD_TYPES_H_ */
