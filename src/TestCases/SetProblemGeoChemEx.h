/*
 * SetProblemGeoChemEx.h
 *
 *  Created on: 10 d�c. 2015
 *      Author: delpopol
 */

#ifndef SETPROBLEMGEOCHEMEX_H_
#define SETPROBLEMGEOCHEMEX_H_

#include "ChemicalSystemTools/ChemicalSystem.h"
#include "ChemicalSystemTools/ChemicalSystemState.h"
#include "ChemicalSystemTools/ChemicalSourceRate.h"
#include "GeochemistryRHSFunction/GeochemistryParameters.h"
#include "ChemicalProblemsUtils/ChemicalProblemsUtils.h"

namespace SetProblemGeoChemEx{
	GeochemistryParameters getParameters(RealVector& y0){
		    std::cout << "Get Parameters for extended TestSHPCO2 " << "\n" ;


		    ///============ System = SHPCO2 System

		    ChemicalSystem system;

		    ///============ Phase

		    ChemicalPhase phaseWater("w","Water","Ideal");
		    system.addPhase(phaseWater);

		    ChemicalPhase phaseCalcite("m1","Calcite","Ideal");
		    system.addPhase(phaseCalcite);

		    ChemicalPhase phaseQuartz("m2","Quartz","Ideal");
		    system.addPhase(phaseQuartz);

		    ChemicalPhase phaseGas("g","Gas","Ideal");
		    system.addPhase(phaseGas);

		    ///============ Species

		    ChemicalSpecies speciesH2O("H2O","w","Solvent","Ideal",0.0);
		    system.addSpecies(speciesH2O);

		    ChemicalSpecies speciesH("H+","w","Solute","Ideal",0.0);
		    system.addSpecies(speciesH);

		    ChemicalSpecies speciesCO2aq("(CO2)aq","w","Solute","Ideal",0.0);
		    system.addSpecies(speciesCO2aq);

		    ChemicalSpecies speciesCl("Cl-","w","Solute","Ideal",0.0);
		    system.addSpecies(speciesCl);

		    ChemicalSpecies speciesNa("Na+","w","Solute","Ideal",0.0);
		    system.addSpecies(speciesNa);

		    ChemicalSpecies speciesCa("Ca++","w","Solute","Ideal",0.0);
		    system.addSpecies(speciesCa);

		    ChemicalSpecies speciesSiO2aq("(SiO2)aq","w","Solute","Ideal",0.0);
		    system.addSpecies(speciesSiO2aq);

		    ChemicalSpecies speciesHCO3("HCO3-","w","Solute","Ideal",-6.2206340);
		    system.addSpecies(speciesHCO3);

		    ChemicalSpecies speciesOH("OH-","w","Solute","Ideal",-13.235362);
		    system.addSpecies(speciesOH);

		    ChemicalSpecies speciesCaCO3("(CaCO3)s","m1","Pole","Ideal",-7.7454139);
		    system.addSpecies(speciesCaCO3);

		    ChemicalSpecies speciesSiO2s("(SiO2)s","m2","Pole","Ideal",3.5862160);
		    system.addSpecies(speciesSiO2s);

		    ChemicalSpecies speciesCO2g("(CO2)g","g","Pole","Ideal",2.0861861);
		    system.addSpecies(speciesCO2g);

		    for(Integer i=0; i<100; ++i){
		    	String tmp_name = "sp"+std::to_string(i);
		    	ChemicalSpecies species(tmp_name,"w","Solute","Ideal",0.0);
		    	system.addSpecies(species);
		    }



		    ///============ Reaction

		    ChemicalReaction reactionH2O("reactionH2O",1.e3);
		    KeyReal sp1("H2O",1);
		    reactionH2O.addSpecies(sp1);
		    KeyReal sp2("OH-",-1);
		    reactionH2O.addSpecies(sp2);
		    KeyReal sp3("H+",-1);
		    reactionH2O.addSpecies(sp3);
		    system.addReaction(reactionH2O);

		    ChemicalReaction reactionCO2aq("reactionCO2aq",1.e3);
			KeyReal sp4("HCO3-",1);
			reactionCO2aq.addSpecies(sp4);
			KeyReal sp5("H+",1);
			reactionCO2aq.addSpecies(sp5);
			KeyReal sp6("(CO2)aq",-1);
			reactionCO2aq.addSpecies(sp6);
			KeyReal sp7("H2O",-1);
			reactionCO2aq.addSpecies(sp7);
			system.addReaction(reactionCO2aq);

			ChemicalReaction reactionSiO2s("reactionSiO2s",1.e-1);
			KeyReal sp8("(SiO2)s",1);
			reactionSiO2s.addSpecies(sp8);
			KeyReal sp9("(SiO2)aq",-1);
			reactionSiO2s.addSpecies(sp9);
			system.addReaction(reactionSiO2s);

			ChemicalReaction reactionCO2g("reactionCO2g",1.e1);
			KeyReal sp10("(CO2)aq",1);
			reactionCO2g.addSpecies(sp10);
			KeyReal sp11("(CO2)g",-1);
			reactionCO2g.addSpecies(sp11);
			system.addReaction(reactionCO2g);

			ChemicalReaction reactionCaCO3("reactionCaCO3",1.e-1);
			KeyReal sp12("Ca++",1);
			reactionCaCO3.addSpecies(sp12);
			KeyReal sp13("HCO3-",1);
			reactionCaCO3.addSpecies(sp13);
			KeyReal sp14("(CaCO3)s",-1);
			reactionCaCO3.addSpecies(sp14);
			KeyReal sp15("H+",-1);
			reactionCaCO3.addSpecies(sp15);
			system.addReaction(reactionCaCO3);

			///============ System State = SHPCO2 Init Compo A

			ChemicalSystemState systemInit;

			KeyReal sp16("H2O",8071.20559);   // initial condition from SHPCO2 paper
			//KeyReal sp16("H2O",8072.37);
			systemInit.setAmountSpecies(sp16);

			KeyReal sp17("H+",0.00377657);
			//KeyReal sp17("H+",0.000347237);
			systemInit.setAmountSpecies(sp17);

			KeyReal sp18("(CO2)aq",119.23091);
			//KeyReal sp18("(CO2)aq",1.19148);
			systemInit.setAmountSpecies(sp18);

			KeyReal sp19("Cl-",156.803187);
			//KeyReal sp19("Cl-",156.803187);
			systemInit.setAmountSpecies(sp19);

			KeyReal sp20("Na+",145.432629);
			//KeyReal sp20("Na+",145.432629);
			systemInit.setAmountSpecies(sp20);

			KeyReal sp21("Ca++",7.01164993);
			//KeyReal sp21("Ca++",5.84686);
			systemInit.setAmountSpecies(sp21);

			KeyReal sp22("(SiO2)aq",0.03770169);
			//KeyReal sp22("(SiO2)aq",0.03770169);
			systemInit.setAmountSpecies(sp22);

			KeyReal sp23("HCO3-",2.62191679);
			//KeyReal sp23("HCO3-",0.288906);
			systemInit.setAmountSpecies(sp23);

			KeyReal sp24("OH-",3.091e-7);
			//KeyReal sp24("OH-",3.40577e-06);
			systemInit.setAmountSpecies(sp24);

			KeyReal sp25("(CO2)g",4.27e2);
			//KeyReal sp25("(CO2)g",546.208);
			systemInit.setAmountSpecies(sp25);

			KeyReal sp26("(CaCO3)s",4.33e3);
			//KeyReal sp26("(CaCO3)s",4331.16);
			systemInit.setAmountSpecies(sp26);

			KeyReal sp27("(SiO2)s",2.82e4);
			systemInit.setAmountSpecies(sp27);

		    for(Integer i=0; i<100; ++i){
		    	String tmp_name = "sp"+std::to_string(i);
		    	KeyReal species(tmp_name,156.803187);
		    	systemInit.setAmountSpecies(species);
		    }



		    GeochemistryParameters param = ChemicalProblemsUtils::buildParameters(system);

		    StringVector species = param.getSpecies();
		    Integer size = species.size();

		    y0.resize(size);
		    y0 = ChemicalProblemsUtils::buildInitialCondition(systemInit,species);

		    return param;

		}

	}


#endif /* SETPROBLEMGEOCHEMEX_H_ */
