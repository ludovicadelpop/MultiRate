/*
 * FixedJacobianNewtonSolver.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: delpopol
 */

#include "FixedJacobianNewtonSolver.h"
#include <algorithm>
#include <Eigen/SparseLU>
#include <Eigen/Dense>

using namespace Eigen;

FixedJacobianNewtonSolver::FixedJacobianNewtonSolver() {}

FixedJacobianNewtonSolver::~FixedJacobianNewtonSolver() {}

void FixedJacobianNewtonSolver::compute(INewtonFunction& fun, RealMatrixSparse& Jac,RealVector& z, const Real tol_rel,const Real tol_abs,
									Bool& diverge_Newton,const Integer MaxNewtonStep ){

	// Prepare Solver


	Integer z_size = z.size();
	diverge_Newton = false;
	RealVector res(z_size);

	// Compute Function F

	fun.evalF(z,res);

	Real L2norm = res.lpNorm<2>();
	Real L2norm_new = L2norm;

	RealVector del(z_size);

	RealVector L2normvector(z_size);

	BoolVector A(z_size);
	BoolVector B(z_size);

	Real Linfnorm_new = 1;
	Real Linfnorm = 0;

	Eigen::SparseLU<RealMatrixSparse> lu_solve;
	lu_solve.analyzePattern(Jac);
	lu_solve.factorize(Jac);

	for(Integer i = 0; i< MaxNewtonStep; ++i){

		Linfnorm = Linfnorm_new;
		L2norm = L2norm_new;

		//std::cout << "[Method Newton-FixedJacobian] " << "Newton step " << i
		//		<< ", NormL2  = " << L2norm
		//		<< ", NormInf = " << Linfnorm << std::endl;

		// Compute Step DeltaY
		del = lu_solve.solve(-res);

		// Update
		Linfnorm_new = del.lpNorm<Infinity>();
		z = z + del;

		fun.evalF(z,res);
		L2norm_new = res.lpNorm<2>();


		// Check Convergence

		A =( del.array().abs()> ( tol_rel * z.array().abs() + tol_abs ) );
		Bool Nerr1 = A.array().any();


		L2normvector.fill(L2norm);
		B =( L2normvector.array() > ( tol_rel * z.array().abs() + tol_abs ) );
		Bool Nerr2 = B.array().any();

		Bool Nerr = (Nerr1 || Nerr2);

		if ( Linfnorm_new > 2*Linfnorm || L2norm_new > 2*L2norm || i == MaxNewtonStep ){
			diverge_Newton = true;
			break;
		}
		else if (Nerr == false)
				break;

	}
}


