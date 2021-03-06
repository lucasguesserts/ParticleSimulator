#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

// InteractionLib
#include <Interaction.hpp>

// SimulationLib
#include <InteractionSubjectLister.hpp>
#include <IntegratorDefinitions.hpp>
#include <SeekerDefinitions.hpp>
#include <SimulationFileTree.hpp>

// UtilsLib
#include <FileSystem.hpp>
#include <Named.hpp>
#include <Vector3D.hpp>
#include <string.hpp>

// Standard
#include <tuple>

namespace psin
{

template<typename ... ParticleTypes> using ParticleList = mp::type_list<ParticleTypes...>;
template<typename ... BoundaryTypes> using BoundaryList = mp::type_list<BoundaryTypes...>;
template<typename ... InteractionTypes> using InteractionList = mp::type_list<InteractionTypes...>;
template<typename ... IntegratorTypes> using IntegratorList = mp::type_list<IntegratorTypes...>;
template<typename ... SeekerTypes> using SeekerList = mp::type_list<SeekerTypes...>;

template<
	typename Particles,
	typename Boundaries,
	typename Interactions,
	typename Integrators,
	typename Seekers
> 
class Simulator;

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
class Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	IntegratorList<GearIntegrator>,
	SeekerList<BlindSeeker>
> : public Named
{
public:
	using ParticleList = psin::ParticleList<ParticleTypes...>;
	using BoundaryList = psin::BoundaryList<BoundaryTypes...>;
	using InteractionList = psin::InteractionList<InteractionTypes...>;
	using IntegratorList = psin::IntegratorList<GearIntegrator>;
	using SeekerList = psin::SeekerList<BlindSeeker>;
	using InteractionParticleParticleTriplets = typename InteractionSubjectLister::generate_combinations<InteractionList, ParticleList, ParticleList>::type;
	using InteractionParticleBoundaryTriplets = typename InteractionSubjectLister::generate_combinations<InteractionList, ParticleList, BoundaryList>::type;

	void setup(const path & mainInputFilePath);

	void setupInteractions(const json & interactionsJSON);
	void buildParticles(const json & particlesJSON);
	void buildBoundaries(const json & boundariesJSON);

	void openFiles();

	// Output
	void outputMainData();
	void createDirectories() const;
	void backupInteractions() const;
	void backupParticles() const;
	void backupBoundaries() const;

	void exportTime(const bool first);
	void exportParticles(const bool first);
	void exportBoundaries(const bool first);

	void printSuccessMessage() const;

	// Simulate
	void simulate();
	template<typename Time> void endSimulation(const Time & time);

private:
	json fileTree;
	
	std::map<string, unique_ptr<std::fstream>> mainFileMap;
	std::map<string, unique_ptr<std::fstream>> particleFileMap;
	std::map<string, unique_ptr<std::fstream>> boundaryFileMap;

	vector<json> timeJsonVector;
	std::map<string, vector<json>> particleJsonMap;
	std::map<string, vector<json>> boundaryJsonMap;

	double initialInstant;
	double timeStep;
	double finalInstant;
	unsigned long stepsForStoring;
	unsigned long storagesForWriting;
	bool printTime;

	std::tuple< std::vector<ParticleTypes>... > particles;
	std::tuple< std::vector<BoundaryTypes>... > boundaries;

	std::set< std::string > interactionsToUse;
	string integrationAlgorithmToUse;
	string seekerToUse;
};

} // psin

#include <Simulator.tpp>

#endif
