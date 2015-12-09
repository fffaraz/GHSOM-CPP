#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

class Vector : public QVector<float>
{
public:
    float distanceTo(const Vector &other) const;
};

#endif // VECTOR_H
