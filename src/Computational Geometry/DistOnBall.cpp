double distOnBall(double lati1, double longi1, double lati2, double longi2, double R) {
	lati1 *= PI / 180; longi1 *= PI / 180;
	lati2 *= PI / 180; longi2 *= PI / 180;
	double x1 = cos(lati1) * sin(longi1);
	double y1 = cos(lati1) * cos(longi1);
	double z1 = sin(lati1);
	double x2 = cos(lati2) * sin(longi2);
	double y2 = cos(lati2) * cos(longi2);
	double z2 = sin(lati2);
	double theta = acos(x1 * x2 + y1 * y2 + z1 * z2);
	return R * theta;
}