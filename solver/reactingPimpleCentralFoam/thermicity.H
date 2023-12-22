// Here thermicity is calculated based on the reaction rate (omega_dot)
{
    Info << "    Calculating thermicity" << endl;
	
	volScalarField& smF = smokeFoil;
	volScalarField cp = thermo.Cp();

	forAll(smF, celli) 
	{	
		scalar invW_mix = 0.0;
		scalar firstTerm = 0.0; //First term of thermicity
		scalar secondTerm = 0.0; //second term of thermicity
	
		forAll(omega_dot, iCmpt)
		{	
			volScalarField& temp = omega_dot[iCmpt]();	
			volScalarField& Yi = Y[iCmpt];	
			scalar Wspecie = composition.W(iCmpt); // MW of iCmpt^th species
	    	invW_mix += Y[iCmpt][celli]/Wspecie; // Summing over to get the mixture MW
			firstTerm += (temp[celli]/Wspecie); // Summing over term 
			secondTerm += temp[celli]*(composition.Hs(iCmpt,p[celli],T[celli]) - composition.Hc(iCmpt)) /(T[celli]*cp[celli]); 

			/*if (celli == 7084)
			{
				Info << "MoleFraction of " << Yi.name() << " mixture is " << Y[iCmpt][celli] << " MW is " << Wspecie << " DYDt is " << temp[celli] << " new enthalpy is " << composition.Hs(iCmpt,p[celli],T[celli]) << endl;
				Info << "Formation enthalpy (?) of this specie " << Yi.name() << " is " << composition.Hc(iCmpt) << endl;				
			}*/
		}		
		firstTerm = firstTerm*(1./invW_mix);	
		thermicity[celli] = (-firstTerm + secondTerm)/rho[celli];

		/*if (celli == 7084)
		{
			Info << "1st term of thermicity is " << thermicity[celli] << " ; rho here is " << rho[celli] << " and Temperature is " << T[celli] << endl;
			Info << "Molecular weight of the mixture is " << 1./invW_mix << " and Cp is " << cp[celli] << endl;
		}*/
	}
}
