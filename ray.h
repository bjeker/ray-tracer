#ifndef RAYH_H
#define RAYH_H

#include "vec3.h"

class ray {
    public:
        ray() {}

        //create a ray using an origin point and a direction vector
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        //return an immutable reference to members, either use reference directly or make mutable copy
        const point3& origin() const { return orig; }
        const vec3& direc() const { return dir; }

        //t is a real num value that can change the point along the ray
        point3 at(double t) const {
            return orig + t * dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif