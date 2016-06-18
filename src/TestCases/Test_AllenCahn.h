/*
 * Test_AllenCahn.h
 *
 *  Created on: Jan 23, 2016
 *      Author: pacs_student
 */

#ifndef TEST_ALLENCAHN_H_
#define TEST_ALLENCAHN_H_

#include "NewtonSolver/BasicNewtonSolver.h"
#include "NewtonSolver/FixedJacobianNewtonSolver.h"

#include "SetProblemAllenCahn.h"

#include "MasterSolverOutputManipulator/MasterSolution.h"
#include "MasterSolverOutputManipulator/MasterSolverOutputManipulator.h"
#include "Restab/GenerateNumbComponentsRestabFile.h"
#include "Restab/GeneratePDERestabFile.h"
#include "Restab/GenerateMeshRestabFile.h"
#include "Restab/GenerateDebugRestabFile.h"

#include "AllenCahnRHSFunction/AllenCahnRHSFunction.h"

#include "CubicHermiteInterpolationSolver/CubicHermiteInterpolationSolver.h"
#include "LinearInterpolationSolver/LinearInterpolationSolver.h"

namespace Test_AllenCahn{
void compute(std::unique_ptr<IMasterSolver> solver, Real Dt, Real Newton_tolabs, Real Newton_tolrel,
		Real Error_tolabs,Real Error_tolrel,Real tinit,Real tfinal, std::unique_ptr<INewtonSolver> newt_solver,
		Integer Nx, Real x0, Real xL, Real sigma){

	AllenCahnRHSFunction func;

	RealVector yinit;

	SetProblemAllenCahn::InitAllenCahn(yinit,sigma,Nx,x0,xL);

	func.setNx(Nx);
	func.setSigma(sigma);
	func.setX0(x0);
	func.setXL(xL);

	Integer y_size = yinit.size();
	RealVector hz1(y_size);
	hz1 = func.evalF(tinit,yinit);

	std::unique_ptr<LinearInterpolationSolver> interp (new LinearInterpolationSolver());
	//std::unique_ptr<CubicHermiteInterpolationSolver> interp(new CubicHermiteInterpolationSolver());

	solver->setFun(&func);
	solver->setHinitial(Dt);
	solver->setHz1initial(hz1);
	solver->setNewtSolv(std::move(newt_solver));
	solver->setYinitial(yinit);
	solver->setTfinal(tfinal);
	solver->setTinitial(tinit);
	solver->setErrorTolAbs(Error_tolabs);
	solver->setErrorTolRel(Error_tolrel);
	solver->setNewtonTolAbs(Newton_tolabs);
	solver->setNewtonTolRel(Newton_tolrel);
	solver->setInterpolator(std::move(interp));


	solver->compute();

	std::vector<std::unique_ptr<ISolverData>> output = solver->getSolution();

	vector<MasterSolution> vect_restab = MasterSolverOutputManipulator::getOutputVectorRestab(std::move(output));
	GeneratePDERestabFile::PDERestab(x0,Nx,xL,vect_restab);
	GenerateDebugRestabFile::DebugRestab(x0,Nx,xL,std::move(output));
	GenerateNumbComponentsRestabFile::ComponentsRestab(std::move(output));
	GenerateMeshRestabFile::MeshRestab(x0,Nx,xL,std::move(output));


	for(unsigned int i=0; i < output.size(); i++){
		cout<<"Iter n = "<<i<<" dt = "<<output[i]->getH()<<" Time = "<<output[i]->getTime()<<std::endl;
	}
}
}

#endif /* TEST_ALLENCAHN_H_ */
