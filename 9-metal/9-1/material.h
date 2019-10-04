#pragma once

#include "hittable.h"

class hit_record;
class ray;
class vec3;

class material {
public:
	virtual bool scatter( const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

