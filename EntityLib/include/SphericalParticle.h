#ifndef SPHERICAL_PARTICLE_H
#define SPHERICAL_PARTICLE_H

#include <iostream>
#include <vector>
#include <fstream>

#include <Particle.h>

using namespace std;

enum SphericalParticleGeometricParameter{
	RADIUS = 0,
	N_GEOMETRIC_PARAMETER
};

class SphericalParticle: public Particle
{
	public:
		SphericalParticle();
		SphericalParticle(const int order, const int dimension, const int handle = -1);
		
		// ---- Geometrical Parameters ----
		void setGeometricParameter(const int geometricParameterIdentifier, const double geometricParameterValue);
		void setGeometricParameter(const DoubleVector geometricParameterVector);
		double getGeometricParameter(const int geometricParameterIdentifier);
		DoubleVector getGeometricParameter();
		
		bool touch(SphericalParticle particle);
		
		// ---- Input and Output ----
		// void fwritePosition( ostream & outFile, const string horizontalSeparator, const string verticalSeparator );
		
	private:
		DoubleVector geometricParameter;
		
		void reserveGeometricParameterMemory(void);
}; // class SphericalParticle

#endif
