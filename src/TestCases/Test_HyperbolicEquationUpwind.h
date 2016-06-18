/*
 * Test_HyperbolicEquationUpwind.h
 *
 *  Created on: Jan 28, 2016
 *      Author: delpopol
 */

#ifndef TEST_HYPERBOLICEQUATIONUPWIND_H_
#define TEST_HYPERBOLICEQUATIONUPWIND_H_

#include "HyperbolicEquationUpwindRHSFunction/HyperbolicEquationUpwindRHSFunction.h"
#include "HyperbolicEquationUpwindRHSFunction/LinearFluxFunction.h"
#include "HyperbolicEquationRusanovFlux/BurgersFluxFunction.h"
#include "NewtonSolver/BasicNewtonSolver.h"
#include "NewtonSolver/FixedJacobianNewtonSolver.h"
#include "SetProblemLinearHyperbolicEquation.h"

#include "ConstantBCFunction/ConstantBCFunction.h"

#include "Restab/GenerateCourantNumberRestabFile.h"
#include "Restab/GenerateNumbComponentsRestabFile.h"
#include "Restab/GeneratePDERestabFile.h"
#include "Restab/GenerateMeshRestabFile.h"
#include "Restab/GenerateDebugRestabFile.h"
#include "MasterSolverOutputManipulator/IsConservativeMethod.h"
#include "MasterSolverOutputManipulator/CourantNumber.h"

#include "CubicHermiteInterpolationSolver/CubicHermiteInterpolationSolver.h"
#include "LinearInterpolationSolver/LinearInterpolationSolver.h"

namespace Test_HyperbolicEquationUpwind{
void compute(std::unique_ptr<IMasterSolver> solver, Real Dt, Real Newton_tolabs, Real Newton_tolrel,
		Real Error_tolabs,Real Error_tolrel,Real tinit,Real tfinal, std::unique_ptr<INewtonSolver> newt_solver,
		Integer Nx, Real x0, Real xL, Real bc_value, Real alpha){

	ConstantBCFunction bc_func;
	bc_func.setValue(bc_value);

	HyperbolicEquationUpwindRHSFunction func;

	RealVector yinit;

	SetProblemLinearHyperbolicEquation::InitialConditionFunction(yinit,x0,Nx,xL);

	BurgersFluxFunction f_flux;
	//f_flux.setA(alpha);

	func.setNx(Nx);
	func.setFluxFunc(&f_flux);
	func.setX0(x0);
	func.setXL(xL);
	func.setBcFunc(&bc_func);

	Integer y_size = yinit.size();
	RealVector hz1(y_size);
	hz1 = func.evalF(tinit,yinit);

	std::unique_ptr<LinearInterpolationSolver> interp (new LinearInterpolationSolver());
	//std::unique_ptr<CubicHermiteInterpolationSolver> interp(new CubicHermiteInterpolationSolver());

	solver->setFun(&func);
	solver->setNewtSolv(std::move(newt_solver));
	solver->setHinitial(Dt);
	solver->setHz1initial(hz1);
	solver->setYinitial(yinit);
	solver->setTfinal(tfinal);
	solver->setTinitial(tinit);
	solver->setErrorTolAbs(Error_tolabs);
	solver->setErrorTolRel(Error_tolrel);
	solver->setNewtonTolAbs(Newton_tolabs);
	solver->setNewtonTolRel(Newton_tolrel);
	solver->setInterpolator(std::move(interp));

	solver->compute();

	std::vector<unique_ptr<ISolverData>>  output = solver->getSolution();


	std::vector<MasterSolution> vect_restab = MasterSolverOutputManipulator::getOutputVectorRestab(std::move(output));
	GeneratePDERestabFile::PDERestab(x0,Nx,xL,vect_restab);
	GenerateDebugRestabFile::DebugRestab(x0,Nx,xL,std::move(output));
	GenerateNumbComponentsRestabFile::ComponentsRestab(std::move(output));
	GenerateMeshRestabFile::MeshRestab(x0,Nx,xL,std::move(output));


	for(unsigned int i=0; i < output.size(); i++){
		std::cout<<"Iter n = "<<i<<" dt = "<<output[i]->getH()<<" Time = "<<output[i]->getTime()<<std::endl;
	}

	cout<<endl;

	Real dx = (xL-x0)/static_cast<Real>(Nx);
	std::vector<Real> Cour_numb = CourantNumber::compute(std::move(output),dx,f_flux);
	GenerateCourantNumberRestabFile::CourantRestab(Cour_numb);

	Bool check_conservation = IsConservativeMethod::check(std::move(output),dx,f_flux,Newton_tolabs);
	std::cout<<"Is a Conservative method: "<<check_conservation<<std::endl;
 }
}




#endif /* SRC_TESTCASES_TEST_HYPERBOLICEQUATIONUPWIND_H_ */
