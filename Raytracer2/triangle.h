#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
public:
	triangle() {}
	triangle(point3 p0, point3 p1, point3 p2) : V0(p0), V1(p1), V2(p2) {};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 V0, V1, V2;
};

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	//compute plane's normal
	vec3 V0V1 = V1 - V0;
	vec3 V0V2 = V2 - V0;
	vec3 N = cross(V0V1, V0V2);
	double denom = dot(N, N);

	// Step 1: Find P

	double NdotRayDir = dot(N, r.direction());
	if (fabs(NdotRayDir) < 1e-8)
	{
		return false;
	}

	// compute d parameter
	double d = dot(N, V0);

	// compute t
	double t = (dot(N, r.origin()) + d) / NdotRayDir;
	//check if triangle is behind the ray
	if (t < 0) return false;

	// compute intersection point P
	vec3 P = r.at(t);

	// Step 2: Inside-Outside test
	vec3 C;

	// edge 0
	vec3 edge0 = V1 - V0;
	vec3 vp0 = P - V0;
	C = cross(edge0, vp0);
	if (dot(N, C) < 0) return false;

	// edge 1
	vec3 edge1 = V2 - V1;
	vec3 vp1 = P - V1;
	C = cross(edge1, vp1);
	if ((rec.u = dot(N, C)) < 0) return false;

	// edge 2
	vec3 edge2 = V0 - V2;
	vec3 vp2 = P - V2;
	C = cross(edge2, vp2);
	if ((rec.v = dot(N, C)) < 0) return false;

	rec.t = t;
	rec.p = P;
	rec.u /= denom;
	rec.v /= denom;
	rec.set_face_normal(r, N);
	return true;
}
#endif // !TRIANGLE_H
