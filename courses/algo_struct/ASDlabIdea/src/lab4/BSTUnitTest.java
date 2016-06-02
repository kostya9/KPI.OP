package lab4;

import static org.junit.Assert.*;
import org.junit.Test;

import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.PrintStream;

/**
 * Created by kostya on 6/2/2016.
 */
public class BSTUnitTest {
    @Test
    public void bstContains(){
        BST tree = new BST();
        Student s = new Student("HeyySurname", "HeyyName", 2, 300, 10.1f, "HeyyStreet");
        tree.insert(s.getId(), s);
        Student s1 = new Student("HeyySurname1", "HeyyName1", 2, 101, 10.1f, "HeyyStreet");
        tree.insert(s1.getId(), s1);
        Student s2 = new Student("HeyySurname2", "HeyyName2", 2, 102, 10.1f, "HeyyStreet");
        tree.insert(s2.getId(), s2);
        Student s3 = new Student("HeyySurname3", "HeyyName3", 2, 103, 10.1f, "HeyyStreet");
        tree.insert(s3.getId(), s3);
        Student s4 = new Student("HeyySurname4", "HeyyName4", 2, 99, 10.1f, "HeyyStreet");
        tree.insert(s4.getId(), s4);
        assertTrue(tree.containsKey(s2.getId()));
        assertTrue(tree.containsKey(s.getId()));
    }
    @Test
    public void bstSize(){
        BST tree = new BST();
        Student s = new Student("HeyySurname", "HeyyName", 2, 300, 10.1f, "HeyyStreet");
        tree.insert(s.getId(), s);
        assertEquals(1, tree.size());
        Student s1 = new Student("HeyySurname1", "HeyyName1", 2, 101, 10.1f, "HeyyStreet");
        tree.insert(s1.getId(), s1);
        Student s2 = new Student("HeyySurname2", "HeyyName2", 2, 102, 10.1f, "HeyyStreet");
        tree.insert(s2.getId(), s2);
        Student s3 = new Student("HeyySurname3", "HeyyName3", 2, 103, 10.1f, "HeyyStreet");
        tree.insert(s3.getId(), s3);
        Student s4 = new Student("HeyySurname4", "HeyyName4", 2, 99, 10.1f, "HeyyStreet");
        tree.insert(s4.getId(), s4);
        assertEquals(5, tree.size());
    }
    @Test
    public void bstInOrderTraverse(){
        BST tree = new BST();
        Student s = new Student("HeyySurname", "HeyyName", 2, 120, 10.1f, "HeyyStreet");
        tree.insert(s.getId(), s);
        assertEquals(1, tree.size());
        Student s1 = new Student("HeyySurname1", "HeyyName1", 2, 99, 10.1f, "HeyyStreet");
        tree.insert(s1.getId(), s1);
        Student s2 = new Student("HeyySurname2", "HeyyName2", 2, 97, 10.1f, "HeyyStreet");
        tree.insert(s2.getId(), s2);
        Student s3 = new Student("HeyySurname3", "HeyyName3", 2, 98, 10.1f, "HeyyStreet");
        tree.insert(s3.getId(), s3);
        Student s4 = new Student("HeyySurname4", "HeyyName4", 2, 131, 10.1f, "HeyyStreet");
        tree.insert(s4.getId(), s4);
        java.io.ByteArrayOutputStream out = new java.io.ByteArrayOutputStream();
        System.setOut(new java.io.PrintStream(out));
        tree.traverse();
        System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
        String outputStringTraversal = out.toString().split("\n")[2];
        assertEquals("97 98 99 120 131 ", outputStringTraversal);
    }
    @Test
    public void bstRemove()
    {
        BST tree = new BST();
        Student s = new Student("HeyySurname", "HeyyName", 2, 120, 10.1f, "HeyyStreet");
        tree.insert(s.getId(), s);
        assertEquals(1, tree.size());
        Student s1 = new Student("HeyySurname1", "HeyyName1", 2, 99, 10.1f, "HeyyStreet");
        tree.insert(s1.getId(), s1);
        Student s2 = new Student("HeyySurname2", "HeyyName2", 2, 97, 10.1f, "HeyyStreet");
        tree.insert(s2.getId(), s2);
        Student s3 = new Student("HeyySurname3", "HeyyName3", 2, 98, 10.1f, "HeyyStreet");
        tree.insert(s3.getId(), s3);
        Student s4 = new Student("HeyySurname4", "HeyyName4", 2, 131, 10.1f, "HeyyStreet");
        tree.insert(s4.getId(), s4);
        Student returnedStudent = tree.remove(s.getId()); // Two children
        assertEquals(returnedStudent , s);
        java.io.ByteArrayOutputStream out = new java.io.ByteArrayOutputStream();
        System.setOut(new java.io.PrintStream(out));
        tree.traverse();
        String outputStringTraversal = out.toString().split("\n")[2];
        assertEquals("97 98 99 131 ", outputStringTraversal);

        java.io.ByteArrayOutputStream out1 = new java.io.ByteArrayOutputStream();
        System.setOut(new java.io.PrintStream(out1));
        tree.remove(s2.getId()); // one child
        tree.traverse();
        outputStringTraversal = out1.toString().split("\n")[2];
        assertEquals("98 99 131 ", outputStringTraversal);

        java.io.ByteArrayOutputStream out2 = new java.io.ByteArrayOutputStream();
        System.setOut(new java.io.PrintStream(out2));
        tree.remove(s4.getId()); // no children
        tree.traverse();
        System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
        outputStringTraversal = out2.toString().split("\n")[2];
        assertEquals("98 99 ", outputStringTraversal);
    }
    @Test
    public void removeByCondition()
    {
        StudentCheck checker = new StudentCheckVar20();
        BST tree = new BST();
        Student s = new Student("HeyySurname", "HeyyName", 2, 120, 5.0f, "HeyyStreet");
        tree.insert(s.getId(), s);
        assertEquals(1, tree.size());
        Student s0 = new Student("HeyySurname4", "HeyyName4", 3, 11, 4.8f, "Hostel");
        tree.insert(s0.getId(), s0);
        Student s1 = new Student("HeyySurname1", "HeyyName1", 2, 99, 3.9f, "HeyyStreet");
        tree.insert(s1.getId(), s1);
        Student s2 = new Student("HeyySurname2", "HeyyName2", 3, 97, 3.8f, "Hostel");
        tree.insert(s2.getId(), s2);
        Student s3 = new Student("HeyySurname3", "HeyyName3", 3, 98, 4.1f, "HeyyStreet");
        tree.insert(s3.getId(), s3);
        Student s4 = new Student("HeyySurname4", "HeyyName4", 3, 131, 4.9f, "Hostel");
        tree.insert(s4.getId(), s4);
        int delta = tree.remove(checker);
        assertEquals(delta, 2);
        assertFalse(tree.containsKey(s4.getId()));
        assertFalse(tree.containsKey(s0.getId()));

    }

}