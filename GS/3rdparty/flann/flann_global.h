#ifndef FLANN_GLOBAL_H
#define FLANN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FLANN_LIBRARY)
#  define FLANNSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FLANNSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FLANN_GLOBAL_H
