using Domain;
namespace Lab3.Model{
    public class BagModel{
        public bool IsActive {get; private set;}
        public Bag Bag {get; private set;}
        public BagModel(Bag bag)
        {
            Bag = bag;
            IsActive = bag.Description != null;
        }
    }
}