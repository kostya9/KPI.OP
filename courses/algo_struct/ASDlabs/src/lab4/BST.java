package lab4;

import java.util.LinkedList;
import java.util.List;

/**
 * binary search tree (bst) keeps specified information about students each node
 * contains id (number of student's card) and information about student (name,
 * surname etc.) all search, delete and get operation use unique id as a key
 */

public class BST {
    class CountNodes<T> implements Callable<T>
    {
        private int count;
        public int getCount(){
            return count;
        };

        public void onStart() {
            count = 0;
        }

        public void call(T input){
            count+=1;
        }
        public void onEnd(){
            // Do nothing
        }

    }
    class GetNodesByCondition<Student> implements Callable<Student>{
        private List<Student> list;
        StudentCheck checker;

        GetNodesByCondition(StudentCheck checker)
        {
            this.checker = checker;
        }
        public void onStart() {
            list = new LinkedList();
        }
        public List<Student> getList()
        {
            return list;
        }
        public void call(Student input){
            if(checker.check((lab4.Student) input))
                list.add(input);
        }
        public void onEnd(){
            // Do nothing
        }
    }
    enum Direction { RIGHT, LEFT, ROOT }

    class TreeNode {

        /**
         * number of student's card - unique identifier
         */
        private int id;

        /**
         * information about student. Instance of class Student
         */
        private Student st;

        /**
         * reference to the right node
         */
        private TreeNode right;
        /**
         * reference to the left node
         */
        private TreeNode left;
        /**
         * reference to the parent node
         */

        private TreeNode parent;

        private TreeNode(int id, Student s) {
            this.id = id;
            this.st = s;
        }

        private TreeNode(int id, Student s, TreeNode parent) {
            this(id, s);
            this.parent = parent;
        }
        private Student remove(int id, Direction d)
        {
            if(id < this.id){
                if(this.left == null){
                    return null;
                }
                else{
                    return this.left.remove(id, Direction.LEFT);
                }
            }
            else if (id > this.id) {
                if (this.right == null) {
                    return null;
                } else {
                    return this.right.remove(id, Direction.RIGHT);
                }
            } else {
                return BST.this.remove(this, d);
            }
        }
        private Student get(int id)
        {
            if(id < this.id){
                if(this.left == null){
                    return null;
                }
                else{
                    return this.left.get(id);
                }
            }
            else if (id > this.id) {
                if (this.right == null) {
                    return null;
                } else {
                    return this.right.get(id);
                }
            } else {
                return this.st;
            }
        }
        private Student insert(int id, Student s)
        {
            if(id < this.id){
                if(this.left == null){
                    this.left = new TreeNode(id, s, this);
                    return null;
                }
                else{
                    return this.left.insert(id, s);
                }
            }
            else if (id > this.id) {
                if (this.right == null) {
                    this.right = new TreeNode(id, s, this);
                    return null;
                } else {
                    return this.right.insert(id, s);
                }
            } else {
                Student prevStudent = this.st;
                this.st = s;
                return prevStudent;
            }
        }

    }

    /**
     * root of a tree
     */
    private TreeNode root;

    public BST() {

    }

    /**
     * Returns true if this binary search tree contains an student for the
     * specified id
     *
     * @param id
     *            id whose presence in this tree is to be tested
     * @return true if this tree contains an student record for the specified id
     */
    public boolean containsKey(int id) {
        TreeNode curNode = root;
        while(curNode != null)
        {
            if(id > curNode.id) {
                curNode = curNode.right;
            }
            else if(id < curNode.id){
                curNode = curNode.left;
            }
            else {
                return true;
            }
        }
        return false;
    }

    /**
     *
     * output the tree in table form according to given way of traversal f
     *
     * preorder: ïðÿìèé ïîðÿäîê
     *
     * postorder: çâîðîòíèé ïîðÿäîê
     *
     * inorder: öåíòðîâàíèé ïîðÿäîê
     */
    /**
     *
     */
    public void traverse() {
        PrintTree<Student> printer = new PrintTree<>();
        traverse(printer);
        // TODO call recursive private method to traverse binary search tree

    }

    public void traverse(Callable<Student> toCall) {
        toCall.onStart();
        if(root != null)
            traverse(this.root, toCall);
        toCall.onEnd();
        // TODO call recursive private method to traverse binary search tree

    }
    public void traverse(TreeNode node, Callable<Student> toCall) {
        if(node.left != null)
            traverse(node.left, toCall);
        toCall.call(node.st);
        if(node.right != null)
          traverse(node.right, toCall);
    }

    /**
     * Put the specified value with the specified id in this tree. If the tree
     * previously contained a mapping for the id, the old value is replaced.
     *
     * @param id
     *            student's id with which the specified value is to be
     *            associated
     * @param value
     *            value (information about student) to be associated with the
     *            specified id
     */
    public Student insert(int id, Student value) {
        if(this.root != null) {
            return this.root.insert(id, value);
        }
        else {
            this.root = new TreeNode(id, value);
            return null;
        }
    }

    /**
     * Returns the number of nodes in this tree.
     *
     * @return he number of nodes in this tree
     */
    public int size() {
        CountNodes counter = new CountNodes();
        traverse(counter);
        return counter.getCount();
    }

    /**
     * Returns the value to which the specified id is associated, or null if
     * this tree contains no student for the id.
     *
     * @param id
     *            the id whose associated student is to be returned
     * @return the student with the specified id, or null if this tree contains
     *         no student for the id or id is invalid (negative or 0)
     */
    public Student get(int id) {
        return this.root.get(id);
    }

    /**
     * Removes the student for this id from this tree if present.
     *
     * @param id
     *            id for which student should be removed
     * @return the previous value of student associated with id, or null if
     *         there was no student for id.
     */
    public Student remove(int id) {
        if(this.root == null)
            return null;
        else if (this.root.id == id) {
            return this.remove(root, Direction.ROOT);
        }
        else{
            return this.root.remove(id, Direction.RIGHT);
        }
    }


    private Student remove(TreeNode toDel, Direction d) {
        // TODO detect case for deleting (no child, one child, two children)
        // cut out node from a tree

        if(toDel.left == null){
            if(toDel.right == null){
                removeNodeNoChildren(toDel, d);
            }
            else{
                removeNodeRightChild(toDel, d);
            }
        }
        else if(toDel.right == null){
            removeNodeLeftChild(toDel, d);
        }
        else{
            TreeNode successor = findAndDetachSuccessor(toDel);
            replaceToDelWithSuccessor(toDel, successor, d);


        }
        return toDel.st;

    }

    private void replaceToDelWithSuccessor(TreeNode toDel, TreeNode successor, Direction d) {
        //root case
        if(toDel == root){
            root = successor;
            root.left = toDel.left;
            root.right = toDel.right;
        }
        else {
            successor.parent = toDel.parent;
            successor.left = toDel.left;
            toDel.left.parent = successor;
            toDel.right.parent = successor;
            successor.right = toDel.right;
            if(d == Direction.LEFT)
                toDel.parent.left = successor;
            else
                toDel.parent.right = successor;
        }
    }

    private TreeNode findAndDetachSuccessor(TreeNode toDel)
    {
        TreeNode current = toDel.right;
        // First right
        if(current.left == null)
        {
            current.parent.right = current.right;
            if(current.right != null)
                current.right.parent = current.parent;
        }
        else{
            // Right then Left
            while(current.left != null)
                current = current.left;
            current.parent.left = null;
            current.parent.left = current.right;
            if(current.right != null)
                current.right.parent = current.parent;
        }
        current.parent = null;
        current.right = null;
        // current.left is null because of the way we search for successor
        return current;
    }
    private void removeNodeRightChild(TreeNode toDel, Direction d) {
        toDel.right.parent = toDel.parent;
        if(d == Direction.LEFT){
            toDel.parent.left = toDel.right;
        }
        else if(d == Direction.RIGHT){
            toDel.parent.right = toDel.right;
        }
        else
            root = toDel.right;
    }
    private void removeNodeLeftChild(TreeNode toDel, Direction d) {
        toDel.left.parent = toDel.parent;
        if(d == Direction.LEFT){
            toDel.parent.left = toDel.left;
        }
        else if(d == Direction.RIGHT){
            toDel.parent.right = toDel.left;
        }
        else
            root = toDel.left;
    }

    private void removeNodeNoChildren(TreeNode toDel, Direction d) {
        if(d == Direction.RIGHT){
            toDel.parent.right = null;
        }
        else if(d == Direction.LEFT){
            toDel.parent.left = null;
        }
        else
            root = null;

    }
    /**
     * Remove from a tree all students that satisfy specified criteria
     *
     * @param checker
     *            one or more criteria by witch students will be removed from
     *            this tree
     * @return number of students was be removed
     */
    public int remove(StudentCheck checker) {
        // TODO
        // 1) find all nodes witch students satisfy specified removeCriteria
        // save in a list nodes to be removed
        // 2) call method remove (node) for each node in a list
        // 3) call size method to check successful removing
        // 4) return difference between old size and new size
        int prevSize = this.size();
        GetNodesByCondition callable = new GetNodesByCondition(checker);
        traverse(callable);
        List<Student> students = callable.getList();
        for(Student student : students)
            this.remove(student.getId());
        int curSize = this.size();
        return prevSize - curSize;

    }

}
