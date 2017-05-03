#ifndef UTILS_SHARED_POINTER_HPP
#define UTILS_SHARED_POINTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#define SharedPointer boost::shared_ptr
#define makeShared boost::make_shared
#define StaticPointerCast boost::static_pointer_cast
#define EnableSharedFromThis boost::enable_shared_from_this

#endif
