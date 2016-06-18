/*
 * NewtonBasic.cpp
 */

#include "BasicNewtonSolver.h"
#include "StandardTypes.h"
#include <Eigen/IterativeLinearSolvers>
#include <algorithm>

using namespace Eigen;

void BasicNewtonSolver::compute(INewtonFunction& fun, RealMatrixSparse& J,RealVector& Y, const Real tol_rel,const Real tol_abs,
								Bool& diverge_Newton,const Integer MaxNewtonStep ){

	// Prepare Solver

	Integer n = Y.size();

	Integer MinNewtonStep = 0;

	RealVector F(n);
	F.fill(0.0);

	J.setZero();

	for (Integer iStep = 0; iStep < MaxNewtonStep; ++iStep) {

		Integer nNewtonStep = iStep;

		// Compute Function F and Jacobian J

		fun.evalFJ(Y, F, J);

		Real NormF = F.lpNorm<Infinity>();

		std::cout << "[Method Newton-Basic] " << "Newton step " << nNewtonStep
				<< ", NormF = " << NormF << std::endl;

		// Check Convergence

		Real ErrF = NormF;

		if ( ( ErrF < tol_rel ) && ( iStep > MinNewtonStep ) ) { diverge_Newton = false; break; }

		RealVector DeltaY(n);

		// Compute Step DeltaY

		Eigen::SparseLU<RealMatrixSparse> solver;
		solver.analyzePattern(J);
		solver.factorize(J);
		DeltaY = solver.solve(-F);

		// Update

		Y = Y + DeltaY;
	}
}
