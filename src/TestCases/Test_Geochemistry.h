/*
 * Test_Geochemistry.h
 *
 *  Created on: Jan 22, 2016
 *      Author: pacs_student
 */

#ifndef TEST_GEOCHEMISTRY_H_
#define TEST_GEOCHEMISTRY_H_

#include "NewtonSolver/BasicNewtonSolver.h"
#include "NewtonSolver/FixedJacobianNewtonSolver.h"

#include "SetProblemSHPCO2SourceRate.h"
#include "SetProblemGeoChemEx.h"
#include "SetProblemGeoChemEx2.h"

#include "MasterSolverOutputManipulator/MasterSolution.h"
#include "MasterSolverOutputManipulator/MasterSolverOutputManipulator.h"
#include "Restab/GenerateGeochemistryRestabFile.h"
#include "Restab/GenerateMeshRestabFile.h"
#include "Restab/GenerateNumbComponentsRestabFile.h"

#include "GeochemistryRHSFunction/GeochemistryRHSFunction.h"
#include "CubicHermiteInterpolationSolver/CubicHermiteInterpolationSolver.h"
#include "LinearInterpolationSolver/LinearInterpolationSolver.h"

namespace Test_Geochemistry{

void compute(std::unique_ptr<IMasterSolver> solver, Real Dt, Real Newton_tolabs, Real Newton_tolrel,
	Real Error_tolabs,Real Error_tolrel,Real tinit,Real tfinal, std::unique_ptr<INewtonSolver> newt_solver ){


	GeochemistryRHSFunction func;
	GeochemistryParameters param;
	RealVector y0;



	//param = SetProblemGeoChemEx::getParameters(y0);
	param = SetProblemGeoChemEx2::getParameters(y0);
	//param = SetProblemSHPCO2SourceRate::getParameters(y0);
	func.setParameters(param);

	RealVector hz0 = func.evalF(tinit,y0);

	std::unique_ptr<CubicHermiteInterpolationSolver> interp(new CubicHermiteInterpolationSolver());
	//std::unique_ptr<LinearInterpolationSolver> interp (new LinearInterpolationSolver());

	solver->setTfinal(tfinal);
	solver->setFun(&func);
	solver->setNewtSolv(std::move(newt_solver));
	solver->setTinitial(tinit);
	solver->setHinitial(Dt);
	solver->setYinitial(y0);
	solver->setNewtonTolAbs(Newton_tolabs);
	solver->setNewtonTolRel(Newton_tolrel);
	solver->setErrorTolAbs(Error_tolabs);
	solver->setErrorTolRel(Error_tolrel);
	solver->setHz1initial(hz0);
	solver->setInterpolator(std::move(interp));

	solver->compute();

	vector<std::unique_ptr<ISolverData>> output = solver->getSolution();

	Integer numb_iteration = output.size();
	std::cout<<"Iteration = "<<numb_iteration<<std::endl;




	vector<MasterSolution> vect_restab = MasterSolverOutputManipulator::getOutputVectorRestab(std::move(output));
	GenerateGeochemistryRestabFile::GeochemistryRestab(param,vect_restab);
	GenerateMeshRestabFile::MeshRestab(std::move(output));
	GenerateNumbComponentsRestabFile::ComponentsRestab(std::move(output));

	for(unsigned int i=0; i < output.size(); i++){
			cout<<"Iter n = "<<i<<" dt = "<<output[i]->getH()<<" Time = "<<output[i]->getTime()<<std::endl;
		}

	}
}




#endif /* SRC_TESTCASES_TEST_GEOCHEMISTRY_H_ */
