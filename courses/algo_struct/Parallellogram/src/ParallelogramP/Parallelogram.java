package ParallelogramP;

public class Parallelogram {
	private float x1;
	private float y1;
	private float x2;
	private float y2;
	private float x3;
	private float y3;
	private float x4;
	private float y4;

	public Parallelogram(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		boolean areParallel12and34 = ((x1 - x2) / (y1 - y2)) == ((x4 - x3) / (y4 - y3));
		boolean areParallel32and41 = ((x3 - x2) / (y3 - y2)) == ((x4 - x1) / (y4 - y1));
		if (areParallel12and34 && areParallel32and41) {
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

	public double perimeter() {
		if (x1 == x2 && y1 == y2) {
			System.out.println("\nThis parallelogram wasn't initialised");
			return Double.NaN;
		} else {
			double side1 = getSideLength(x1, y1, x2, y2);
			double side2 = getSideLength(x2, y2, x3, y3);
			return 2 * (side1 + side2);
		}
	}

	public double area() {
		if (x1 == x2 && y1 == y2) {
			System.out.println("\nThis parallelogram wasn't initialised");
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

	public void output() {
		if (x1 == x2 && y1 == y2)
			System.out.println("\nThis parallelogram wasn't initialised");
		else {
			String outCoord = String.format("{%.2f, %.2f} {%.2f, %.2f} {%.2f, %.2f} {%.2f, %.2f}", x1, y1, x2, y2, x3,
					y3, x4, y4);
			System.out.println("\nThis parallelogrm has coordinates :\n" + outCoord);
			String outAreaAndPer = String.format("\nPerimeter = %.2f\nArea = %.2f\n", perimeter(), area());
			System.out.print(outAreaAndPer);
		}
	}

	private double getSideLength(double x1, double y1, double x2, double y2) {
		return Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
	}

}
