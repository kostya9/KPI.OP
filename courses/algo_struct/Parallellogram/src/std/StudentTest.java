package std;

public class StudentTest {
	public static void main(String[] args) {
		Student st = new Student("Me", 52);
		st.output();

		st.setMark(4.2F);
		System.out.println("Mark was assigned");
		st.output();
	}
}