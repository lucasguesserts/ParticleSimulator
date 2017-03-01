#ifndef FORCE_MODEL_SET_H
#define FORCE_MODEL_SET_H

// std
#include <set>

// ForceModelLib
#include <ForceModel.h>

// boost
#include <boost/make_shared.hpp>

using namespace std;

namespace ForceModelSet{
		struct ForceModelCompare{
			bool operator()( const ForceModel & left, const ForceModel & right ) const
			{ return left.getName() < right.getName();}
		};
};

static set<ForceModel, ForceModelSet::ForceModelCompare> forceModelSet;

#endif