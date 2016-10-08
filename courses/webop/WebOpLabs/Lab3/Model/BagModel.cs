using Domain;
namespace Lab3.Model{
    class BagModel{
        public bool IsActive {get; private set;}
        public Bag Bag {get; private set;}
        public BagModel(Bag bag)
        {
            Bag = bag;
            IsActive = bag.Id != 0 ? true : false;
        }
    }
}