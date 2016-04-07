
class Point(object):
    def __init__(self, coord_x, coord_y):
        self.coord_x = coord_x
        self.coord_y = coord_y

def getPointOfIntersection(p1, p2, p3, p4):
    d = (p1.coord_x - p2.coord_x) * (p3.coord_y - p4.coord_y) - (p1.coord_y - p2.coord_y) * (p3.coord_x - p4.coord_x);    
    if d == 0:
        return None

    xi = ((p3.coord_x-p4.coord_x)*(p1.coord_x*p2.coord_y-p1.coord_y*p2.coord_x)-(p1.coord_x-p2.coord_x)*(p3.coord_x*p4.coord_y-p3.coord_y*p4.coord_x))/d;
    yi = ((p3.coord_y-p4.coord_y)*(p1.coord_x*p2.coord_y-p1.coord_y*p2.coord_x)-(p1.coord_y-p2.coord_y)*(p3.coord_x*p4.coord_y-p3.coord_y*p4.coord_x))/d;

    if p3.coord_x == p4.coord_x:
        if yi < min(p1.coord_y, p2.coord_y) or yi > max(p1.coord_y, p2.coord_y):
            return None
    if xi < min(p1.coord_x, p2.coord_x) or xi > max(p1.coord_x, p2.coord_x):
        return None
    if xi < min(p3.coord_x, p4.coord_x) or xi > max(p3.coord_x, p4.coord_x):
        return None

    return Point(xi, yi)

def main():
    p1 = Point(0, 0)
    p2 = Point(2, 0)
    p3 = Point(1, 1)
    p4 = Point(1, -2)
    print getPointOfIntersection(p1, p2, p3, p4).coord_x, getPointOfIntersection(p1, p2, p3, p4).coord_y

main()