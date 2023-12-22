{
    Info<< "    Calculating smokeFoil" << endl;

	volScalarField& smF = smokeFoil;

	forAll(smF, celli) 
		{
			smF[celli] = std::max(smF[celli], p[celli]);
		}
}
