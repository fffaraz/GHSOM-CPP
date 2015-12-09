#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

class Vector : public QVector<float>
{
public:
    QString name;
    bool has_name = false;
    float distanceTo(const Vector &other) const;
};

#endif // VECTOR_H
