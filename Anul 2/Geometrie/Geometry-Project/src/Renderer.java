import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;

import static org.lwjgl.opengl.GL11.*;

public class Renderer {

	private static int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 800;

	private static List<Triangle> triangles = new ArrayList<Triangle>();
	private static List<Triangle> trianglesInside = new ArrayList<Triangle>();
	private static Line line;

	public static float scaleX, scaleY;

	private static Point thePoint;

	public static void initializeDisplay() {

		try {
			Display.setDisplayMode(new DisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT));
			Display.setTitle("Geometry Project");
			Display.create();
		} catch (LWJGLException e) {
			e.printStackTrace();
		}
	}

	public static void setUpOpenGl() {

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
		glMatrixMode(GL_MODELVIEW);
		// glClearColor(0.1f, 0.7f, 0.99f, 1.f);
		glClearColor(1, 1, 1, 1.f);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	public static void loadTriangles() {
		List<Float> coordinates = new ArrayList<Float>();
		List<Point> points = new ArrayList<Point>();
		Scanner fileScanner = null;

		try {
			fileScanner = new Scanner(new File("triangles.txt"));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		float thePointX = fileScanner.nextFloat();
		float thePointY = fileScanner.nextFloat();
		int i = 0;
		float maxLeft = 0, maxRight = 0, maxUp = 0, maxDown = 0;
		maxLeft = thePointX;
		maxRight = thePointY;
		maxUp = thePointY;
		maxDown = thePointY;
		while (fileScanner.hasNextFloat()) {
			coordinates.add(fileScanner.nextFloat());
			i++;
			if (i % 2 == 0) {
				float firstPoint = coordinates.get(coordinates.size() - 2);
				float secondPoint = coordinates.get(coordinates.size() - 1);
				
					if(firstPoint > maxRight)
					{
						maxRight = firstPoint;
					}
					if(firstPoint < maxLeft)
					{
						maxLeft = firstPoint;
					}
					if(secondPoint > maxUp)
					{
						maxUp = secondPoint;
					}
					if(secondPoint < maxDown)
					{
						maxDown = secondPoint;
					}
				
				points.add(new Point(firstPoint, secondPoint));
			}

			if (i == 6) {
				triangles.add(new Triangle(points));
				points.clear();
				i = 0;
			}
		}
		String position = "";
		if (fileScanner.hasNext()) {
			position = fileScanner.next();
		}
		
		System.out.println(position);

		if (position.equals("Inside")) {
			i = 0;
			points.clear();
			while (fileScanner.hasNextFloat()) {
				coordinates.add(fileScanner.nextFloat());
				i++;
				if (i % 2 == 0) {
					float firstPoint = coordinates.get(coordinates.size() - 2);
					float secondPoint = coordinates.get(coordinates.size() - 1);
					points.add(new Point(firstPoint, secondPoint));
				}

				if (i == 6) {
					trianglesInside.add(new Triangle(points));
					trianglesInside.get(trianglesInside.size() - 1).setColor(0, 0.7f, 0.5f);
					points.clear();
					i = 0;
				}
			}

		} else if (position.equals("Outside")) {

		} else {
			Point p1 = new Point(fileScanner.nextFloat(),
					SCREEN_HEIGHT + fileScanner.nextFloat() * -1);
			Point p2 = new Point(fileScanner.nextFloat(),
					SCREEN_HEIGHT + fileScanner.nextFloat() * -1);

			line = new Line(p1, p2);
		}
		
		float maxWidth = maxRight - maxLeft;
		float maxHeight = maxUp - maxDown;
		
		if(maxWidth > maxHeight)
		{
			scaleX = SCREEN_WIDTH / maxWidth;
		}
		else {
			scaleX = SCREEN_HEIGHT / maxHeight;
		}
		scaleX = SCREEN_WIDTH / maxWidth;
		scaleY = SCREEN_HEIGHT / maxHeight;
		
		maxRight += (maxRight / 6);
		maxUp += (maxUp / 6);
		
		float scale = SCREEN_WIDTH / SCREEN_HEIGHT;
		float max;
		if(maxUp > maxRight)
		{
			max = maxUp;
		}
		else {
			max = maxRight;
		}
		
		System.out.println(scaleX + " " + maxWidth + " " + maxHeight + " " + maxUp + " " + maxDown + " " + maxRight + " " + maxLeft);
		
		for(i = 0; i < triangles.size(); i++)
		{
			Point p1 = triangles.get(i).getPoint(0);
			Point p2 = triangles.get(i).getPoint(1);
			Point p3 = triangles.get(i).getPoint(2);

			System.out.println(i + "1 " + p1.x + " " + p1.y + " " + p2.x + " " + p2.y + " " + p3.x + " " + p3.y);
				
			p1.setX(p1.x / max * SCREEN_WIDTH);
			p1.setY((SCREEN_HEIGHT - p1.y / max * SCREEN_HEIGHT));
			
			p2.setX(p2.x / max * SCREEN_WIDTH);
			p2.setY((SCREEN_HEIGHT - p2.y / max * SCREEN_HEIGHT));
			
			p3.setX(p3.x / max * SCREEN_WIDTH);
			p3.setY((SCREEN_HEIGHT - p3.y / max * SCREEN_HEIGHT));
			
			triangles.get(i).setPoints(p1, p2, p3);
			
			System.out.println(i + "2 " + p1.x + " " + p1.y + " " + p2.x + " " + p2.y + " " + p3.x + " " + p3.y);
		}
		for(i = 0; i < trianglesInside.size(); i++)
		{
			Point p1 = trianglesInside.get(i).getPoint(0);
			Point p2 = trianglesInside.get(i).getPoint(1);
			Point p3 = trianglesInside.get(i).getPoint(2);

			System.out.println(i + "1 " + p1.x + " " + p1.y + " " + p2.x + " " + p2.y + " " + p3.x + " " + p3.y);
				
			p1.setX(p1.x / max * SCREEN_WIDTH);
			p1.setY((SCREEN_HEIGHT - p1.y / max * SCREEN_HEIGHT));
			
			p2.setX(p2.x / max * SCREEN_WIDTH);
			p2.setY((SCREEN_HEIGHT - p2.y / max * SCREEN_HEIGHT));
			
			p3.setX(p3.x / max * SCREEN_WIDTH);
			p3.setY((SCREEN_HEIGHT - p3.y / max * SCREEN_HEIGHT));
			
			trianglesInside.get(i).setPoints(p1, p2, p3);
			
			System.out.println(i + "2 " + p1.x + " " + p1.y + " " + p2.x + " " + p2.y + " " + p3.x + " " + p3.y);
		}
		thePoint = new Point(thePointX/ max * SCREEN_WIDTH, SCREEN_HEIGHT - thePointY / max * SCREEN_HEIGHT);
		//thePoint = new Point(thePointX, thePointY);
	}

	public static void gameLoop() {

		while (!Display.isCloseRequested()) {
			glClear(GL_COLOR_BUFFER_BIT);

			input();

			renderTriangles();

			updateDisplay();
		}
	}

	private static void updateDisplay() {
		Display.update();
		Display.sync(60);

	}

	private static void renderTriangles() {

		for (int i = 0; i < triangles.size(); i++) {
			if (i > 0) {
				if (triangles.get(i - 1).isFinishedDrawing() && !triangles.get(i).isFinishedDrawing()) {
					triangles.get(i).draw();
				}
			}
		}

		if(triangles.get(triangles.size() -1).isFinishedDrawing())
		{
			thePoint.draw(false);
		}
		
		if (line != null && thePoint.isFinished) {
			line.draw();
		} else {
			if(thePoint.isFinished)
			{
				for (int i = 0; i < trianglesInside.size(); i++) {
					if(i > 0) {
						if (trianglesInside.get(i - 1).isFinishedDrawing() && !trianglesInside.get(i).isFinishedDrawing()) {
							trianglesInside.get(i).draw();
						}
					}
				}
				
				for (int i = 0; i < trianglesInside.size(); i++) {
					if (i > 0) {
						if (trianglesInside.get(i).isFinishedDrawing()) {
							trianglesInside.get(i).draw();
						}
					} else {
						trianglesInside.get(i).draw();
					}
				}	

			}
			//thePoint2.draw(false);
		}		
		for (int i = 0; i < triangles.size(); i++) {
			if (i > 0) {
				if (triangles.get(i).isFinishedDrawing()) {
					triangles.get(i).draw();
				}
			} else {
				triangles.get(i).draw();
			}
		}

	}

	private static void input() {
		if (Keyboard.isKeyDown(Keyboard.KEY_F5)) {
			for (int i = 0; i < triangles.size(); i++) {
				triangles.get(i).refresh();
				triangles.get(i).setFinished(false);
			}
			thePoint.refresh();
		}
	}
}

class Line {
	private Point p1, p2;

	public Line(Point p1, Point p2) {
		this.p1 = p1;
		this.p2 = p2;
	}

	public void draw() {
		glColor3f(0.3f, 0.7f, 0.9f);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
		glEnd();
	}
}