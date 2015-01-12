import static org.lwjgl.opengl.GL11.*;

import java.util.ArrayList;
import java.util.List;

public class Point {
	private double radius;
	private int maxWaves = 3;
	private int currentNrOfWaves = 0;

	double current_radius = 0;
	double current_radius_second = 0;

	float x, y;

	public Point(float x, float y) {
		this.x = x;
		this.y = y;

		initValues();
	}

	public void refresh() {
		current_radius = 0;
		current_radius_second = 0;
		currentNrOfWaves = 0;
	}

	private void initValues() {
		radius = 40;
	}

	public void draw(boolean sin) {
		if (sin == true) {
			drawWavesSin();
		} else {
			drawWavesBlink();
		}
	}

	private void drawWavesBlink() {
		if (currentNrOfWaves <= maxWaves) {

			if (current_radius > 90 * Math.PI / 180.0f
					&& currentNrOfWaves < maxWaves) {
				Circle.draw(this, Math.min(
						radius * Math.sin(current_radius_second), radius),
						28 / 255f, 109 / 255f, 175 / 255f);

				if (current_radius_second > 0) {
					current_radius_second -= 0.04f;
				} else {
					current_radius = 0;
					current_radius_second = 90 * Math.PI / 180.0f;
					currentNrOfWaves++;
				}

			} else {
				current_radius += 0.04f;

				current_radius_second = 90 * Math.PI / 180.0f;

				Circle.draw(this,
						Math.min(radius * Math.sin(current_radius), radius),
						28 / 255f, 109 / 255f, 175 / 255f);

				if (currentNrOfWaves == maxWaves
						&& current_radius > 90 * Math.PI / 180.0f) {
					currentNrOfWaves++;
				}
			}
		} else {
			// if(current_radius == 0)
			// {
			// current_radius = radius;
			// }
			if (current_radius > Math.sin(radius) / 8) {
				current_radius -= 0.04f;
			}
			Circle.draw(this,
					Math.min(radius * Math.sin(current_radius), radius),
					28 / 255f, 109 / 255f, 175 / 255f);
		}
	}

	private void drawWavesSin() {
		if (currentNrOfWaves < maxWaves) {

			if (currentNrOfWaves > 0) {
				Circle.draw(this, radius, 28 / 255f, 109 / 255f, 175 / 255f);
			}

			Circle.draw(this,
					Math.min(radius * Math.sin(current_radius), radius),
					40 / 255f, 158 / 255f, 255 / 255f);

			if (current_radius > 90 * Math.PI / 180.0f) {

				if (current_radius_second < 90 * Math.PI / 180.0f) {
					current_radius_second += 0.04f;
				} else {
					current_radius = 0;
					current_radius_second = 0;
					currentNrOfWaves++;
				}

				Circle.draw(this, Math.min(
						radius * Math.sin(current_radius_second), radius),
						28 / 255f, 109 / 255f, 175 / 255f);
			} else {
				current_radius += 0.04f;
			}
		} else {
			if (current_radius == 0) {
				current_radius = radius;
			}
			if (radius * Math.sin(current_radius) > radius / 8) {
				current_radius -= 0.04f;
			}
			Circle.draw(this,
					Math.min(radius * Math.sin(current_radius), radius),
					28 / 255f, 109 / 255f, 175 / 255f);
		}
	}

}
