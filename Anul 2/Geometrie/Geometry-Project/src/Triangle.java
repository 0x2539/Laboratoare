import static org.lwjgl.opengl.GL11.*;

import java.util.ArrayList;
import java.util.List;

public class Triangle {
	private List<Point> points;
	private Point center;
	private double radius;

	float current_radius = 0;
	float current_radius_second = 0;
	
	public void refresh()
	{
		current_radius = 0;
		current_radius_second = 0;
	}

	public Triangle(List<Point> list) {
		points = new ArrayList<Point>();
		for(int i = 0; i < list.size(); i++)
		{
			points.add(list.get(i));
		}
		
		initValues();
	}
	
	public Triangle(Point p1, Point p2, Point p3) {
		points = new ArrayList<Point>();
		
		points.add(p1);
		points.add(p2);
		points.add(p3);
		
		initValues();
	}
	
	private void initValues()
	{
		center = find_center(points.get(0), points.get(1), points.get(2));
		radius = distance(center, points.get(0));
	}

	public void draw(boolean sin) {
		// drawTheSquares();
		if(!sin)
		{
			drawWavesSin();
		}
		else
		{
			drawWaves();
		}
		drawSquares();
	}
	
	private void drawWavesSin()
	{
		Circle.draw(center, Math.min(radius * Math.sin(current_radius), radius), false);
		if(current_radius > 90 * Math.PI / 180.0f)
		{
			if(current_radius_second < 90 * Math.PI / 180.0f)
			{
				current_radius_second += 0.04f;
			}
			Circle.draw(center, Math.min(radius * Math.sin(current_radius_second), radius), true);

			drawLines();
		}
		else
		{
			current_radius += 0.04f;
		}
	}

	private void drawWaves()
	{
		Circle.draw(center, Math.min(current_radius, radius), false);
		if(current_radius > radius)
		{
			if(current_radius_second < radius)
			{
				current_radius_second += 2.0f;
			}
			Circle.draw(center, Math.min(current_radius_second, radius), true);

			drawLines();
		}
		else
		{
			current_radius += 2.0f;
		}
	}
	
	private void drawSquares()
	{
		for(int i = 0; i < points.size(); i++)
		{
			int j = (i + 1) % points.size();
			int k = (i + 2) % points.size();
			Square.drawSquare(points.get(i), points.get(j), points.get(k));	
		}
	}

	private void drawLines() {
		glColor4f(0, 0.5f, 0.7f, 1.f);
		glEnable(GL_LINE_SMOOTH);
		glLineWidth(2);
		
		for (int i = 0; i < points.size(); i++) {
			int j = (i + 1) % points.size();
			glBegin(GL_LINES);
				glVertex2f(points.get(i).x, points.get(i).y);
				glVertex2f(points.get(j).x, points.get(j).y);
			glEnd();
		}
	}

	private double distance(Point p1, Point p2) {
		return Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)
				* (p1.y - p2.y));
	}

	public Point find_center(Point A, Point B, Point C) {
		Point U = new Point(0, 0);

		float D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x
				* (A.y - B.y));

		U.x = ((A.x * A.x + A.y * A.y) * (B.y - C.y) + (B.x * B.x + B.y * B.y)
				* (C.y - A.y) + (C.x * C.x + C.y * C.y) * (A.y - B.y))
				/ D;
		U.y = ((A.x * A.x + A.y * A.y) * (C.x - B.x) + (B.x * B.x + B.y * B.y)
				* (A.x - C.x) + (C.x * C.x + C.y * C.y) * (B.x - A.x))
				/ D;
		return U;
	}
}

class Square {
	private static int drawn_times = 0;

	public static void drawSquare(Point p1, Point p2, Point other) {
		drawn_times = 0;
		square(p1, p2, other, false);
	}

	private static float getSide(Point p, Point A, Point B) {
		return Math.signum((B.x - A.x) * (p.y - A.y) - (B.y - A.y)
				* (p.x - A.x));
	}

	private static void square(Point p1, Point p2, Point other, boolean both) {
		drawn_times++;

		Point p3 = new Point(0, 0);
		Point p4 = new Point(0, 0);
		Point pCenter1 = new Point(0, 0);
		Point pCenter2 = new Point(0, 0);

		pCenter1.x = (p1.x + p2.x) / 2;
		pCenter1.y = (p1.y + p2.y) / 2; // Center point
		pCenter2.x = (p1.x - p2.x) / 2;
		pCenter2.y = (p1.y - p2.y) / 2; // Half-diagonal

		p3.x = pCenter1.x - pCenter2.y;
		p3.y = pCenter1.y + pCenter2.x; // Third corner
		p4.x = pCenter1.x + pCenter2.y;
		p4.y = pCenter1.y - pCenter2.x; // Fourth corner

		glColor4d(1, 1, 1, 1);
		
		//draw only half of the square
		if (!both) {
			if (getSide(other, p1, p2) != getSide(p4, p1, p2)) {
				
				drawTriangle(p1, p2, p4);
				
				if (drawn_times == 1) {
					square(p1, p4, p3, true);
					square(p2, p4, p1, true);
				}
			} else {
				
				drawTriangle(p1, p2, p3);

				if (drawn_times == 1) {
					square(p1, p3, p2, true);
					square(p2, p3, p1, true);
				}
			}
		}
		else
			//draw the full square
		{
			drawTriangle(p1, p2, p4);
			drawTriangle(p1, p2, p3);
		}
	}
	
	private static void drawTriangle(Point p1, Point p2, Point p3)
	{
		glBegin(GL_TRIANGLES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p3.x, p3.y);
		glVertex2d(p2.x, p2.y);
		glEnd();
	}

}

