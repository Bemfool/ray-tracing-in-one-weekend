#pragma once
#include "hittable.h"

class hittable_list : public hittable {
public:
	hittable_list() {}
	hittable_list(hittable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	hittable **list;
	int list_size;
};


