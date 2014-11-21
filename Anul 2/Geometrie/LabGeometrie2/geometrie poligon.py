from math import copysign
from math import acos
from math import degrees
from math import sqrt

class Point(object):
	def __init__(self, coord_x, coord_y):
		self.coord_x = coord_x
		self.coord_y = coord_y


def crossProductConvexity(list_of_points):
	p1, p2, p3 = list_of_points
	dx1 = p2.coord_x - p1.coord_x
	dy1 = p2.coord_y - p3.coord_y
	dx2 = p3.coord_x - p2.coord_x
	dy2 = p3.coord_y - p3.coord_y
	zcrossproduct = dx1 * dy2 - dy1 * dx2
	return zcrossproduct

def solveConvexity():
	
	points = [Point(0, 0), Point(1, 0), Point(0, 1), Point(1, 1)]
	sign = 0

	for index in range(0, len(points)):
		passing_points = []
		for secondIndex in range(index, index + 3):
			passing_points.append(points[secondIndex % len(points)])
		if sign == 0:
			sign = crossProductConvexity(passing_points)
		else:
			if copysign(1, crossProductConvexity(passing_points)) != copysign(1, sign):
				return False
	return True

def getDistanceBetween2Points(p1, p2):
	return sqrt((p1.coord_x - p2.coord_x) * (p1.coord_x - p2.coord_x) + (p1.coord_y - p2.coord_y) * (p1.coord_y - p2.coord_y))

def getAngleBetween3Points(list_of_points):
	p12 = getDistanceBetween2Points(list_of_points[0], list_of_points[1])
	p13 = getDistanceBetween2Points(list_of_points[0], list_of_points[2])
	p23 = getDistanceBetween2Points(list_of_points[1], list_of_points[2])
	return degrees(acos((p12 ** 2 + p13 ** 2 - p23 ** 2) / (2 * p12 * p13)))

def solvePointPosition():
	points = [Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)]
	the_point = Point(1.25, 0.666)

	angle = 0

	for index in range(0, len(points)):
		passing_points = [the_point]
		for secondIndex in range(index, index + 2):
			passing_points.append(points[secondIndex % len(points)])
			print points[secondIndex % len(points)].coord_x, points[secondIndex % len(points)].coord_y
		angle += getAngleBetween3Points(passing_points)

	return angle

def main():
	print solveConvexity()
	print solvePointPosition()

main()