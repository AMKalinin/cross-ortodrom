#pragma once

#include <vector>
#include <math.h>

double distance_between_coord(std::vector<double> point1, std::vector<double> point2)
{
	double R = 6371110;
	double phi1 = point1[0];
	double lambda1 = point1[1];

	double phi2 = point2[0];
	double lambda2 = point2[1];

	double delta_lambda = lambda2 - lambda1;
	double p1 = sin(delta_lambda) * cos(phi2);
	double p2 = cos(phi1) * sin(phi2) - sin(phi1) * cos(phi2) * cos(delta_lambda);
	double q = sin(phi1) * sin(phi2) + cos(phi1) * cos(phi2) * cos(delta_lambda);
	double res = abs(atan2(sqrt(p1 * p1 + p2 * p2), q) * R);
	return res;
}

std::vector<double> vectornoe_proizvedenie(std::vector<double> v1, std::vector<double> v2)
{
	std::vector<double> tmp = { 1,1,1 };
	tmp[0] = v1[1] * v2[2] - v1[2] * v2[1];
	tmp[1] = -(v1[0] * v2[2] - v1[2] * v2[0]);
	tmp[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return tmp;
}

std::vector<double> norm(std::vector<double> vector)
{
	std::vector<double> tmp = { 1,1,1 };
	double length = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
	tmp[0] = vector[0] / length;
	tmp[1] = vector[1] / length;
	tmp[2] = vector[2] / length;
	return tmp;
}

std::vector<double> GEO_GSK(std::vector<double> vector)
{
	std::vector<double> tmp = { cos(vector[0]) * cos(vector[1]), cos(vector[0]) * sin(vector[1]),  sin(vector[0]) };
	return tmp;
}

std::vector<double> GSK_GEO(std::vector<double> vector)
{
	std::vector<double> tmp_v = { 1, 1 };
	double lat = asin(vector[2]);
	double tmp = cos(lat);
	double sign = asin(vector[1] / tmp);
	double lon;
	if (sign < 0)
	{
		lon = -abs(acos(vector[0] / tmp));
	}
	else
	{
		lon = abs(acos(vector[0] / tmp));
	}
	tmp_v = { lat, lon };
	return tmp_v;
}

bool proverka_tochki(std::vector<double> start1, std::vector<double> end1, std::vector<double> start2, std::vector<double> end2, std::vector<double> point)
{
	double obsh_dist_1 = distance_between_coord(start1, end1);
	double dist_do_1 = distance_between_coord(start1, point);
	double dist_posle_1 = distance_between_coord(point, end1);

	double obsh_dist_2 = distance_between_coord(start2, end2);
	double dist_do_2 = distance_between_coord(start2, point);
	double dist_posle_2 = distance_between_coord(point, end2);

	double a = obsh_dist_1 - dist_do_1 - dist_posle_1;
	if (a > 0.0000001 || a < -0.000001) { return false; }

	double b = obsh_dist_2 - dist_do_2 - dist_posle_2;
	if (b > 0.0000001 || b < -0.000001) { return false; }
	
	double c = abs(a - b);
	if (c < 0.0000001) { return true; }
	else { return false; }
}

std::vector<double> intersection_ortodrom(std::vector<double> start1, std::vector<double> end1, std::vector<double> start2, std::vector<double> end2)
// Если размер возвращаемого вектора равен 1, то пересечения нет. 
{
	std::vector<double> p1 = GEO_GSK(start1);
	std::vector<double> p2 = GEO_GSK(end1);

	std::vector<double> p3 = GEO_GSK(start2);
	std::vector<double> p4 = GEO_GSK(end2);

	std::vector<double> v1 = vectornoe_proizvedenie(p1, p2);
	std::vector<double> v2 = vectornoe_proizvedenie(p3, p4);

	std::vector<double> u1 = norm(v1);
	std::vector<double> u2 = norm(v2);

	std::vector<double> d = vectornoe_proizvedenie(v1, v2);

	std::vector<double> s1 = norm(d);
	std::vector<double> s2 = { -s1[0], -s1[1], -s1[2] };

	p1 = GSK_GEO(s1);
	p2 = GSK_GEO(s2);

	if (proverka_tochki(start1, end1, start2, end2, p1))
	{
		return p1;
	}

	if (proverka_tochki(start1, end1, start2, end2, p2))
	{
		return p2;
	}
	std::vector<double> er = { 1 };
	return er;

}

