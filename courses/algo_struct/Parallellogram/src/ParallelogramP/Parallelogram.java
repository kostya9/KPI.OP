package ParallelogramP;
/**
 * Represents a parallelogram in coordiantes form. Can calculate area and perimeter of the parallelogram. Can output it's characteristics.
 * @author Kostya Sharovarsky
 * @version 1.0
 *
 */
public class Parallelogram {
	private float x1;
	private float y1;
	private float x2;
	private float y2;
	private float x3;
	private float y3;
	private float x4;
	private float y4;

	/**Creates a parallelogram from 4 points(given parameters).
	 * If they don't represent a parallelogram -  outputs "This figure isn't a parallelogram"
	 * and assigns all four points of this object to (0, 0)
	 * @param x1 X of Point 1
	 * @param y1 Y of Point 1
	 * @param x2 X of Point 2
	 * @param y2 Y of Point 2
	 * @param x3 X of Point 3
	 * @param y3 Y of Point 3
	 * @param x4 X of Point 4 
	 * @param y4 Y of Point 4
	 */
	public Parallelogram(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		boolean parEq12n34 = ((x1 - x2) / (y1 - y2)) == ((x4 - x3) / (y4 - y3));
		boolean parEq32n41= ((x3 - x2) / (y3 - y2)) == ((x4 - x1) / (y4 - y1));
		if (parEq12n34 && parEq32n41) {
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
			this.x3 = x3;
			this.y3 = y3;
			this.x4 = x4;
			this.y4 = y4;
		} else
			System.out.print("\nThis figure isn't a parallelogram");
	}
 /**
  * Calculates the perimeter of the parallelogram
  * @return the perimeter of th parallelogram or NaN if the parallelogram was not initialized properly
  */
	public double getPerimeter() {
		if (x1 == x2 && y1 == y2) {
			return Double.NaN;
		} else {
			double side1 = getSideLength(x1, y1, x2, y2);
			double side2 = getSideLength(x2, y2, x3, y3);
			return 2 * (side1 + side2);
		}
	}
	 /**
	  * Calculates the area of the parallelogram
	  * @return the area of this parallelogram or NaN if the parallelogram was not initialized properly
	  */
	public double getArea() {
		if (x1 == x2 && y1 == y2) {
			return Double.NaN;
		} else {
			double side1 = getSideLength(x1, y1, x2, y2);
			double vec1x = x2 - x1;
			double vec1y = y2 - y1;
			double vec2x = x3 - x2;
			double vec2y = y3 - y2;
			double side2 = getSideLength(x2, y2, x3, y3);
			double angle = Math.acos((vec1x * vec2x + vec1y * vec2y) / (side1 * side2));
			return side1 * side2 * Math.sin(angle);
		}
	}
	 /**
	  * Outputs the area and perimeter of the parallelogram
	  * If it was not initialized properly - outputs "This parallelogram wasn't initialized"
	  */
	public void output() {
		if (x1 == x2 && y1 == y2)
			System.out.println("\nThis parallelogram wasn't initialized");
		else {
			String outCoord = String.format("{%.2f, %.2f} {%.2f, %.2f} {%.2f, %.2f} {%.2f, %.2f}", x1, y1, x2, y2, x3,
					y3, x4, y4);
			System.out.println("\nThis parallelogrm was built from points :\n" + outCoord);
			String outAreaAndPer = String.format("\nPerimeter = %.2f\nArea = %.2f\n", getPerimeter(), getArea());
			System.out.print(outAreaAndPer);
		}
	}
/**
 *  Calculates the length of a side
 * @param x1 X coordinate of Point 1
 * @param y1 Y coordinate of Point 1
 * @param x2 X coordinate of Point 2
 * @param y2 Y coordiante of Point 2
 * @return Length of the side
 */
	private double getSideLength(float x1, float y1, float x2, float y2) {
		return Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
	}

}
