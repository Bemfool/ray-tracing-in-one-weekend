#pragma once
#include "material.h"
#include "random.h"

class metal : public material {
public:
	metal(const vec3& a) : albedo(a) {
		fuzz = 0;
	}
	metal(const vec3& a, float f) : albedo(a) {
		fuzz = (f < 1) ? f : 1;
	}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
	vec3 albedo;
	float fuzz;
};

