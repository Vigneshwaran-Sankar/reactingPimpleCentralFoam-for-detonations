scalar nDim = runTime.controlDict().lookupOrDefault<scalar>("nDimensions",2); // Number of spatial dimensions in the simulation
const bool simType = runTime.controlDict().lookupOrDefault("isShockAttached",true); // Switch for LFR or SFR simulations
const bool thermicitySwitch = runTime.controlDict().lookupOrDefault("writeThermicity",true); // Switch for LFR or SFR simulations


Info<< "Reading thermophysical properties\n" << endl;
autoPtr<psiReactionThermo> pThermo(psiReactionThermo::New(mesh));
psiReactionThermo& thermo = pThermo();
thermo.validate(args.executable(), "h", "e");

basicSpecieMixture& composition = thermo.composition();
PtrList<volScalarField>& Y = composition.Y();

word inertSpecie(thermo.lookup("inertSpecie"));

thermo.correct();

volScalarField& p = thermo.p();
volScalarField& h = thermo.he();
volScalarField& psi = const_cast<volScalarField&>(thermo.psi());
const volScalarField& T = thermo.T();

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volVectorField HbyA ("HbyA", U);


Info<< "Creating field kinetic energy K\n" << endl;
volScalarField K
(
    "K",
    0.5*magSqr(U)
);

volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    thermo.rho()
);

dimensionedScalar v_one("v_one", pow(dimTime,-1.0), 1.0);
volScalarField rAU ("rAU", 1.0/rho/v_one);
rAU.primitiveFieldRef() *= runTime.deltaTValue();
rAU.primitiveFieldRef() /= mesh.V().field();


volScalarField KChange
(
    "KChange",
    rho*K / runTime.deltaT() * 0.0
);

volScalarField KSource
(
    "KSource",
    p / runTime.deltaT() * 0.0
);

volScalarField c
(
    IOobject
    (
        "cSound",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    sqrt(thermo.Cp()/thermo.Cv() / psi)
);

volScalarField dQ
(
    IOobject
    (
        "dQ",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("dQ", dimEnergy/dimTime, 0.0)
);

volVectorField gradp
(
    "gradp",
    fvc::grad(p)
);
volVectorField limGradP 
(
    "limGradP",
    fvc::grad(p)
);

////////////////////////////////////// fields for SmokeFoil computation

volScalarField smokeFoil
(
	IOobject
	(
	    "smokeFoil",
	    runTime.timeName(),
	    mesh,
	    IOobject::READ_IF_PRESENT,
	    IOobject::AUTO_WRITE
	),
	mesh,
	dimensionedScalar("smokeFoil", p.dimensions(), 0)
);

vector U_freshGas;
label leftI = mesh.boundaryMesh().findPatchID("leftWall");
const fvPatchVectorField& fvp = U.boundaryField()[leftI];

if (fvp.size())
{
	U_freshGas = fvp[0];
	Info << "U_fresh gas is = " << U_freshGas << endl;
}

reduce(U_freshGas, maxOp<vector>());

volVectorField U_inlet
(
	IOobject
	(
	    "U_inlet",
	    runTime.timeName(),
	    mesh,
	    IOobject::READ_IF_PRESENT,
	    IOobject::AUTO_WRITE
	),
   mesh,
   dimensionedVector("U_inlet", U.dimensions(), U_freshGas)
);

Info<< "Reading/calculating constant flux field phi for smokeFoil equation \n" << endl;
surfaceScalarField Phi_Inlet
(
	IOobject
	(
	    "Phi_Inlet",
	    runTime.timeName(),
	    mesh,
	    IOobject::READ_IF_PRESENT,
	    IOobject::AUTO_WRITE
	),
	linearInterpolate(U_inlet) & mesh.Sf()
);

////////////////////////////////////// Thermicity

volScalarField thermicity
(
    IOobject
    (
        "thermicity",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("thermicity", dimEnergy/dimTime/dimEnergy, 0)
);

///////////////////////////////////////////

DynamicList<label> badQualityCells(0);

Switch updateEnergyInPISO (false);
word fluxScheme (word::null);
Switch noFluxWeighting(false);

