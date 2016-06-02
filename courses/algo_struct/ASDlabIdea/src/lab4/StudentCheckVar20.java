package lab4;

/**
 * Created by kostya on 6/2/2016.
 */
public class StudentCheckVar20 implements StudentCheck {
    public boolean check(Student s)
    {
        boolean course = s.getCourse() == 3;
        boolean averageScore = s.getAverageScore() > 4.0f;
        boolean isInHostel = s.getAddress() == "Hostel";
        return course && averageScore && isInHostel;
    }
}
