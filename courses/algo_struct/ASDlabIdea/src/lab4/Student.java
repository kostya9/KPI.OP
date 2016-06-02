package lab4;

/**
 * keep information about student
 *
 */
public class Student implements Comparable<Student>{
    private String surname;
    private String name;
    private int course;
    private int id;
    private float averageScore;
    private String address;

    public Student(String surname, String name, int course, int id, float averageScore, String address) {
        this.surname = surname;
        this.name = name;
        this.course = course;
        this.id = id;
        this.averageScore = averageScore;
        this.address = address;
    }
    public Student(Student s) {
        this.surname = s.surname;
        this.name = s.name;
        this.course = s.course;
        this.id = s.id;
        this.averageScore = s.averageScore;
        this.address = s.address;
    }

    public String getSurname() {
        return surname;
    }

    public String getName() {
        return name;
    }

    public int getCourse() {
        return course;
    }

    public int getId() {
        return id;
    }

    public float getAverageScore() {
        return averageScore;
    }

    public String getAddress() {
        return address;
    }
    public int compareTo(Student right)
    {
        return Integer.compare(this.id, right.id);
    }
    @Override
    public String toString()
    {
        return Integer.toString(id);
    }
    // add fields according to your variant

}
