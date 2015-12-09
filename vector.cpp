#include "vector.h"

float Vector::distanceTo(const Vector &other) const
{
    if(this->size() != other.size()) return -1;
    float res = 0;
    for (int i = 0; i < this->size(); ++i)
    {
        float tmp = this->value(i) - other.value(i);
        res += tmp * tmp;
    }
    return res;
}
