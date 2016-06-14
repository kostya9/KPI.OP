package Task3;

import com.sun.istack.internal.NotNull;

/**
 * Created by kostya on 6/14/2016.
 */
public class DictionaryBST<T extends Comparable, E> {

    BSTNode root;

    private class BSTNode{
        T key;
        E value;

        BSTNode parent;
        BSTNode left;
        BSTNode right;

        BSTNode(T key, E value, @NotNull BSTNode parent){
            this.parent = parent;
            this.key = key;
            this.value = value;

            if(this.key.compareTo(parent.key) < 0){
                parent.left= this;
            }
            else{
                parent.right = this;
            }
        }

        BSTNode(T key, E value){
            this.key = key;
            this.value = value;
            this.parent = null;
        }
    }
    public void buildWorstCase(int length){
        root = new BSTNode((T)(Object)0, (E)(Object)0);
        BSTNode curNode = root;
        for(int i = 1; i < length; i++){
            curNode = new BSTNode((T)(Object)i, (E)(Object)i, curNode);
        }
    }
    public E insert(T key, E element){
        if(root == null) {
            root = new BSTNode(key, element);
            return null;
        }

        BSTNode curNode = root;
        BSTNode prevNode = null;
        while(curNode != null){
            if(key.compareTo(curNode.key) < 0){
                prevNode = curNode;
                curNode = curNode.left;
            }
            else if(key.compareTo(curNode.key) > 0){
                prevNode = curNode;
                curNode = curNode.right;
            }
            else{
                E retValue = curNode.value;
                curNode = new BSTNode(key, element, prevNode);
                return retValue;
            }
        }

        curNode = new BSTNode(key, element, prevNode);
        return null;
    }

    public E get(T key){
        BSTNode curNode = root;

        while(curNode != null){
            if(key.compareTo(curNode.key) < 0){
                curNode = curNode.left;
            }
            else if(key.compareTo(curNode.key) > 0){
                curNode = curNode.right;
            }
            else{
                return curNode.value;
            }
        }

        return null;
    }
    // TODO test
    private int getCount(BSTNode node){
        if(node!= null)
            return 1 + getCount(node.left) + getCount(node.right);
        else
            return 0;
    }
    public int getCount(){
        return getCount(root);
    }


}
