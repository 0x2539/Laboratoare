import static org.lwjgl.opengl.GL11.GL_TRIANGLE_FAN;
import static org.lwjgl.opengl.GL11.glBegin;
import static org.lwjgl.opengl.GL11.glColor4f;
import static org.lwjgl.opengl.GL11.glEnd;
import static org.lwjgl.opengl.GL11.glVertex2d;
import static org.lwjgl.opengl.GL11.glVertex2f;


public class Circle {
	
	public static void draw(Point center, double radius, boolean invisible) {
		//draw the first wave
		if(!invisible)
		{
			draw(center, radius, 0, 0.5f, 0.7f);
		}
		else
		//draw the white wave
		{
			draw(center, radius, 1, 1, 1);
		}
	}

	public static void draw(Point center, double radius, float red, float green, float blue) {
		
		glColor4f(red, green, blue, 1);
		
		//draw the circle
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(center.x, center.y);
			
			double x1, y1, x2, y2;
			x1 = center.x;
			y1 = center.y;
	
			for (float angle = 0.0f; angle <= 2 * Math.PI + 0.2; angle += 0.2) {
				x2 = x1 + Math.sin(angle) * radius;
				y2 = y1 + Math.cos(angle) * radius;
				glVertex2d(x2, y2);
			}
		glEnd();
	}
}
