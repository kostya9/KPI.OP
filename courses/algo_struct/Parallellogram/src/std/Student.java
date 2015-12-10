package std;

public class Student {
	private String name;
	private int group;
	private float mark;

	public Student(String name, int group) {
		this.name = name;
		this.group = group;
		this.mark = 0.0F;
	}

	public void output() {
		System.out.println("Name : " + name + "\nGroup: " + group + "\nMark : " + mark);
	}

	public void setMark(float mark) {
		this.mark = mark;
	}
}
