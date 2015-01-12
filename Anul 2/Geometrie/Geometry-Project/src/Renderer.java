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

	private static int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

	private static List<Triangle> triangles = new ArrayList<Triangle>();

	private static Point thePoint = new Point(400, 400);
	private static Point thePoint2 = new Point(200, 400);

	public static void initializeDisplay() {

		try {
			Display.setDisplayMode(new DisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT));
			Display.setTitle("PacMan");
			Display.create();
		} catch (LWJGLException e) {
			e.printStackTrace();
		}
	}

	public static void setUpOpenGl(){
		
		glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 640, 480, 0, 1, -1);
        glMatrixMode(GL_MODELVIEW);
		//glClearColor(0.1f, 0.7f, 0.99f, 1.f);
		glClearColor(1, 1, 1, 1.f);
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_BLEND );
	}
	
	public static void loadTriangles()
	{
		List<Float> coordinates = new ArrayList<Float>();
		List<Point> points = new ArrayList<Point>();    
		Scanner fileScanner = null;
		
		try {
			fileScanner = new Scanner(new File("triangles.txt"));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		int i = 0;
		while (fileScanner.hasNextFloat()){
		   coordinates.add(fileScanner.nextFloat());
		   i++;
		   if(i % 2 == 0)
		   {
			   float firstPoint = coordinates.get(coordinates.size() - 2);
			   float secondPoint = coordinates.get(coordinates.size() - 1);
			   points.add(new Point(firstPoint, secondPoint));
		   }
		   
		   if(i == 6)
		   {
			   triangles.add(new Triangle(points));
			   points.clear();
			   i = 0;
		   }
		}
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
		for (int i = 0; i < triangles.size(); i++)
		{
			triangles.get(i).draw(i%2 == 0 ? true : false);
		}
		thePoint.draw(true);
		thePoint2.draw(false);
	}
	
	private static void input()
	{
		if(Keyboard.isKeyDown(Keyboard.KEY_F5))
		{
			for (int i = 0; i < triangles.size(); i++)
			{
				triangles.get(i).refresh();
			}
			thePoint.refresh();
			thePoint2.refresh();
		}
	}
}
