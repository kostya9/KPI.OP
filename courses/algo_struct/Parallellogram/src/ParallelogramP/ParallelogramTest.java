package ParallelogramP;

public class ParallelogramTest {

	public static void main(String[] args) {
		Parallelogram p = new Parallelogram(1.5F, 2.5F, 2.5F, 2.5F, 2.5F, 1.5F, 1.5F, 1.5F);
		p.output();

		Parallelogram p1 = new Parallelogram(18F, 26F, 48F, 26F, 40F, 10F, 10F, 10F);
		p1.output();
		System.out.println("\nPerimeter method was called and the return value printed to console:");
		System.out.println(p1.perimeter());

		Parallelogram p2 = new Parallelogram(1.5F, 1F, 1F, 1F, 2.1F, 2F, 3.9F, 4F);
		p2.output();
		System.out.println("\nArea method was called and the return value printed to console:");
		System.out.println(p2.area());

	}

}