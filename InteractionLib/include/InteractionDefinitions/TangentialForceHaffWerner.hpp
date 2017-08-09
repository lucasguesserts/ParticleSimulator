#ifndef TANGENTIAL_FORCE_HAFF_WERNER_HPP
#define TANGENTIAL_FORCE_HAFF_WERNER_HPP

// EntityLib
#include <SphericalParticle.hpp>

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.18) (see reference)
struct TangentialForceHaffWerner
{
	template<typename...Ts, typename...Us>
	static void calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Vector3D normalForce, double timeStep);
};

#include <InteractionDefinitions/TangentialForceHaffWerner.tpp>

#endif