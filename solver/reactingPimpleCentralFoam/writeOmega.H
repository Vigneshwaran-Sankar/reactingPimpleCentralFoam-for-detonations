const label nComponents = Y.size();
List<autoPtr<volScalarField> > omega_dot(nComponents);

forAll(omega_dot, iCmpt)
{
	volScalarField& Yi = Y[iCmpt];
	word nameTi ("omega_dot_" + Yi.name());
	omega_dot[iCmpt].reset
	(
		new volScalarField
		(
			IOobject
			(
				nameTi,
				runTime.timeName(),
        		mesh,
        		IOobject::NO_READ,
        		IOobject::AUTO_WRITE
    		),
			(reaction->R(Yi) & Yi)
		)
	);
}
