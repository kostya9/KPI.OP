package lab4;

import static org.junit.Assert.*;
import org.junit.Test;

import java.io.*;
import java.nio.file.Files;

/**
 * Created by kostya on 6/2/2016.
 */
public class BSTUnitTest {
    private String getTraverseOutput(BST tree)
    {
        java.io.ByteArrayOutputStream out2 = new java.io.ByteArrayOutputStream();
        System.setOut(new java.io.PrintStream(out2));
        tree.traverse();
        System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
        return out2.toString().split("\n")[2];
    }
    private Student createSimpleStudent(int id)
    {
        return new Student("Heyyname", "HeyySurname", 1, id, 4.0f, "HeyyHostel");
    }
    private BST loadTree(){
        BST tree = new BST();
        File treeText;
        treeText = new File("tree");
        try {
            Files.lines(treeText.toPath()).forEach((String line) -> {
                int id = 0;
                try {
                    id = Integer.parseInt(line);
                } catch (NumberFormatException e) {
                    return;
                }
                tree.insert(id, createSimpleStudent(id));
            });
        }
        catch(IOException e)
        {
            System.out.println("Something is wrong with the file 'tree'");
            return tree;
        }
        return tree;

    }
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

        String outputStringTraversal = getTraverseOutput(tree);
        assertEquals("97 98 99 120 131 ", outputStringTraversal);
    }
    @Test
    public void bstRemove()
    {
        BST tree = loadTree();

        String traverseOutput = getTraverseOutput(tree);
        // https://imgur.com/aI4qmtE
        String expectedraverseString = "160 170 180 190 200 205 210 300 310 360 370 375 380 385 390 400 410 415 420 430 440 450 ";
        assertEquals(expectedraverseString, traverseOutput);

        tree.remove(450); // one child right
        traverseOutput = getTraverseOutput(tree);
        expectedraverseString = "160 170 180 190 200 205 210 300 310 360 370 375 380 385 390 400 410 415 420 430 440 ";
        assertEquals(expectedraverseString, traverseOutput);

        tree.remove(430); // one child right (more later)
        traverseOutput = getTraverseOutput(tree);
        expectedraverseString = "160 170 180 190 200 205 210 300 310 360 370 375 380 385 390 400 410 415 420 440 ";
        assertEquals(expectedraverseString, traverseOutput);

        tree.remove(160); // one child left
        traverseOutput = getTraverseOutput(tree);
        expectedraverseString = "170 180 190 200 205 210 300 310 360 370 375 380 385 390 400 410 415 420 440 ";
        assertEquals(expectedraverseString, traverseOutput);

        tree.remove(190); // one child left (more later)
        traverseOutput = getTraverseOutput(tree);
        expectedraverseString = "170 180 200 205 210 300 310 360 370 375 380 385 390 400 410 415 420 440 ";
        assertEquals(expectedraverseString, traverseOutput);

        tree.remove(400); // two children(successor right)
        traverseOutput = getTraverseOutput(tree);
        expectedraverseString = "170 180 200 205 210 300 310 360 370 375 380 385 390 410 415 420 440 ";
        assertEquals(expectedraverseString, traverseOutput);

        tree.remove(300); // two children(successor left) (root)
        traverseOutput = getTraverseOutput(tree);
        expectedraverseString = "170 180 200 205 210 310 360 370 375 380 385 390 410 415 420 440 ";
        assertEquals(expectedraverseString, traverseOutput);




    }
    @Test
    public void removeByCondition() throws IOException {
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