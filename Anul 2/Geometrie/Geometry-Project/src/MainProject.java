
import org.lwjgl.opengl.*;


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
