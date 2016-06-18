#include "SingleRateBESolver/SingleRateBESolver.h"
#include "SingleRateTRBDF2Solver/SingleRateTRBDF2Solver.h"
#include "MultiRateTRBDF2Solver/MultiRateTRBDF2Solver.h"
#include "SingleRateFESolver/SingleRateFESolver.h"

#include "TestCases/Test_Geochemistry.h"
#include "TestCases/Test_AllenCahn.h"
#include "TestCases/Test_HyperbolicEquationUpwind.h"
#include "TestCases/Test_HyperbolicEquationRusanov.h"

#include "GetPot.hpp"
#include "chrono.hpp"

#include "StandardTypes.h"
using namespace Utils;

using namespace Timings;

int main(int argc, char ** argv){
	Chrono temp;

	temp.start();

	GetPot      ifile("data.pot");

	String rhsFunction = ifile ("common_parameters/rhs","Geochemistry");
	String Solver = ifile ("common_parameters/Solver","SingleRateTRBDF2Solver");
	Real Newton_tolabs = ifile("common_parameters/Newton_tol_abs",1.e-3);
	Real Newton_tolrel = ifile("common_parameters/Newton_tol_rel",1.e-3);
	Real Error_tolabs = ifile("common_parameters/Error_tol_abs",1.e-3);
	Real Error_tolrel = ifile("common_parameters/Error_tol_rel",1.e-3);
	Real delta_t = ifile("common_parameters/delta_t",0.1);
	Real T_init = ifile("common_parameters/tInitial",0.0);
	Real T_final = ifile("common_parameters/tFinal",10.0);
	String Newton_solver = ifile("common_parameters/NewtonSolver","BasicNewtonSolver");
// TEST GEOCHEMISTRY

	if (rhsFunction == "Geochemistry"){
		if(Solver=="SingleRateBESolver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
				Test_Geochemistry::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt));
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
				Test_Geochemistry::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt));
			}
			}

		if(Solver=="SingleRateFESolver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
				Test_Geochemistry::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt));
			}
			else{
			if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
				Test_Geochemistry::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt));
			}
			}
		}

		if(Solver=="SingleRateTRBDF2Solver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
				Test_Geochemistry::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt));
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
				Test_Geochemistry::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt));
			}

		}

		if(Solver=="MultiRateTRBDF2Solver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<CubicHermiteInterpolationSolver> inter(new CubicHermiteInterpolationSolver());
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
				Test_Geochemistry::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt));
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
				Test_Geochemistry::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt));
			}
		}
	}

	if (rhsFunction == "HyperbolicEquationUpwind"){

		Real x0 = ifile("HyperbolicEquationUpwind/x0",0.0);
		Real xL = ifile("HyperbolicEquationUpwind/xL",1.0);
		Real bc_value = ifile("HyperbolicEquationUpwind/BC_value",0.0);
		Integer Nx = ifile("HyperbolicEquationUpwind/nx",100);
		Real alpha = ifile("HyperbolicEquationUpwind/alpha",1.0);


		if(Solver=="SingleRateBESolver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
				Test_HyperbolicEquationUpwind::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
				Test_HyperbolicEquationUpwind::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}
		}

		if(Solver=="SingleRateFESolver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
				Test_HyperbolicEquationUpwind::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
				Test_HyperbolicEquationUpwind::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}
		}

		if(Solver=="SingleRateTRBDF2Solver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
				Test_HyperbolicEquationUpwind::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
				Test_HyperbolicEquationUpwind::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}

		}

		if(Solver=="MultiRateTRBDF2Solver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
				Test_HyperbolicEquationUpwind::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
				Test_HyperbolicEquationUpwind::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt),Nx,x0,xL,bc_value,alpha);
			}
		}
	}
	if (rhsFunction == "AllenCahn"){

		Real x0 = ifile("AllenCahn/x0",0.0);
		Real xL = ifile("AllenCahn/xL",1.0);
		Integer Nx = ifile("AllenCahn/nx",100);
		Real sigma = ifile("AllenCahn/sigma",1.0);


		if(Solver=="SingleRateBESolver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
				Test_AllenCahn::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,sigma);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
				Test_AllenCahn::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,sigma);
			}
		}

		if(Solver=="SingleRateFESolver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
				Test_AllenCahn::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,sigma);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
				Test_AllenCahn::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
				Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,sigma);
			}
		}

		if(Solver=="SingleRateTRBDF2Solver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
				Test_AllenCahn::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,sigma);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
				Test_AllenCahn::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,sigma);
			}

		}

		if(Solver=="MultiRateTRBDF2Solver"){
			if(Newton_solver == "BasicNewtonSolver"){
				std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
				std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
				Test_AllenCahn::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt),Nx,x0,xL,sigma);
			}
			else if(Newton_solver == "FixedJacobianNewtonSolver"){
				std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
				std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
				Test_AllenCahn::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
						Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt),Nx,x0,xL,sigma);
			}
		}
	}
	if (rhsFunction == "HyperbolicEquationRusanov"){

			Real x0 = ifile("HyperbolicEquationRusanov/x0",0.0);
			Real xL = ifile("HyperbolicEquationRusanov/xL",1.0);
			Real bc_value = ifile("HyperbolicEquationRusanov/BC_value",0.0);
			Integer Nx = ifile("HyperbolicEquationRusanov/nx",100);


			if(Solver=="SingleRateBESolver"){
				if(Newton_solver == "BasicNewtonSolver"){
					std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
					std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
					Test_HyperbolicEquationRusanov::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
					Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value);
				}
				else if(Newton_solver == "FixedJacobianNewtonSolver"){
					std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
					std::unique_ptr<SingleRateBESolver> BE(new SingleRateBESolver());
					Test_HyperbolicEquationRusanov::compute(std::move(BE),delta_t,Newton_tolabs,Newton_tolrel,
					Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value);
				}
			}

			if(Solver=="SingleRateFESolver"){
				if(Newton_solver == "BasicNewtonSolver"){
					std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
					std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
					Test_HyperbolicEquationRusanov::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
					Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value);
				}
				else if(Newton_solver == "FixedJacobianNewtonSolver"){
					std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
					std::unique_ptr<SingleRateFESolver> FE(new SingleRateFESolver());
					Test_HyperbolicEquationRusanov::compute(std::move(FE),delta_t,Newton_tolabs,Newton_tolrel,
					Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value);
				}
			}

			if(Solver=="SingleRateTRBDF2Solver"){
				if(Newton_solver == "BasicNewtonSolver"){
					std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
					std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
					Test_HyperbolicEquationRusanov::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
							Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value);
				}
				else if(Newton_solver == "FixedJacobianNewtonSolver"){
					std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
					std::unique_ptr<SingleRateTRBDF2Solver> SR_TRBDF2(new SingleRateTRBDF2Solver());
					Test_HyperbolicEquationRusanov::compute(std::move(SR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
							Error_tolabs,Error_tolrel,T_init,T_final,std::move(Newt),Nx,x0,xL,bc_value);
				}

			}

			if(Solver=="MultiRateTRBDF2Solver"){
				if(Newton_solver == "BasicNewtonSolver"){
					std::unique_ptr<BasicNewtonSolver> Newt(new BasicNewtonSolver());
					std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
					Test_HyperbolicEquationRusanov::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
							Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt),Nx,x0,xL,bc_value);
				}
				else if(Newton_solver == "FixedJacobianNewtonSolver"){
					std::unique_ptr<FixedJacobianNewtonSolver> Newt(new FixedJacobianNewtonSolver());
					std::unique_ptr<MultiRateTRBDF2Solver> MR_TRBDF2(new MultiRateTRBDF2Solver());
					Test_HyperbolicEquationRusanov::compute(std::move(MR_TRBDF2),delta_t,Newton_tolabs,Newton_tolrel,
							Error_tolabs,Error_tolrel,T_init,T_final, std::move(Newt),Nx,x0,xL,bc_value);
				}
			}
		}
temp.stop();
std::cout<<temp<<std::endl;

}

