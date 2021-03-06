#ifndef SPHERICAL_PARTICLE_HPP
#define SPHERICAL_PARTICLE_HPP

// Standard
#include <ostream>
#include <vector>

// EntityLib
#include <Particle.hpp>
#include <FixedInfinitePlane.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <metaprogramming.hpp>
#include <NamedType.hpp>
#include <string.hpp>
#include <Vector.hpp>

namespace psin {

template<typename ... PropertyTypes>
class SphericalParticle : public Particle<Radius, PropertyTypes...>
{
	public:
		using BaseParticle = Particle<Radius, PropertyTypes...>;

		constexpr static bool is_spherical = true;

		SphericalParticle() = default;
		explicit SphericalParticle(const BaseParticle & base);
		explicit SphericalParticle(const string & name, const int taylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
		
		// ---- Collision ----
		template<typename...Us>
		Vector3D relativeTangentialVelocity(const SphericalParticle<Us...> & neighbor) const;
		
		template<typename...Us>
		Vector3D tangentialVersor(const SphericalParticle<Us...> & neighbor) const;

		template<typename...Us>
		Vector3D normalVersor(const SphericalParticle<Us...> & neighbor) const;
};

template<typename T, typename SFINAE = void>
struct is_spherical : std::false_type {};

template<typename T>
struct is_spherical<
		T,
		std::enable_if_t<T::is_spherical or not T::is_spherical>
	>
	: mp::bool_constant<T::is_spherical>
{};

template<typename...Ts, typename...Us>
double distance(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs);

template<typename...Ts, typename...Us>
bool touch(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs);

template<typename...Ts, typename...Us>
bool touch(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs);

template<typename...Ts, typename...Us>
double overlap(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs);

template<typename...Ts, typename...Us>
double overlap(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs);

template<typename...Ts, typename...Us>
double overlapDerivative(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs);

template<typename...Ts, typename...Us>
double overlapDerivative(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs);

template<typename...Ts, typename...Us>
Vector3D contactPoint(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs);

template<typename...Ts, typename...Us>
Vector3D normalVersor(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs);

template<typename...Ts, typename...Us>
Vector3D normalVersor(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs);

template<typename...Ts, typename...Us>
Vector3D relativeVelocityContactPoint(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs);

template<typename...Ts, typename...Us>
Vector3D relativeVelocityContactPoint(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs);

template<typename...Prs>
void from_json(const json& j, SphericalParticle<Prs...> & p);
template<typename...Prs>
void to_json(json& j, const SphericalParticle<Prs...> & p);

} // psin

#include <SphericalParticle.tpp>

#endif
