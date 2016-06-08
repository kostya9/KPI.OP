package lab4;

/**
 * Created by kostya on 6/1/2016.
 */
public class BSTTest {
    public static void main(String[] args) {
        BST tree = new BST();
        Student s = new Student("HeyySurname", "HeyyName", 2, 300, 10.1f, "HeyyStreet");
        tree.insert(s.getId(), s);
        Student s1 = new Student("HeyySurname1", "HeyyName1", 2, 101, 10.1f, "HeyyStreet");
        tree.insert(101, s1);
        Student s2 = new Student("HeyySurname2", "HeyyName2", 2, 102, 10.1f, "HeyyStreet");
        tree.insert(102, s2);
        Student s3 = new Student("HeyySurname3", "HeyyName3", 2, 103, 10.1f, "HeyyStreet");
        tree.insert(103, s3);
        Student s4 = new Student("HeyySurname4", "HeyyName4", 2, 99, 10.1f, "HeyyStreet");
        tree.insert(99, s4);
        tree.traverse();
        tree.remove(300);
        tree.traverse();
    }
}
