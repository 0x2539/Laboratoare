
import static org.lwjgl.opengl.GL11.*;
import org.lwjgl.opengl.*;
import org.lwjgl.*;


public class MainProject {

	public MainProject(){
		
		Renderer.initializeDisplay();
		Renderer.setUpOpenGl();
		Renderer.loadTriangles();
		
		Renderer.gameLoop();
		
		Display.destroy();
	}
	
	public static void main(String[] args) {
		new MainProject();
	}
}
