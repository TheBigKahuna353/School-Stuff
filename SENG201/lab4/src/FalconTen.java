public class FalconTen extends Rocket {


    FalconTen(String name) {
        super(name, 2);
    }

    // @Override
    void fly() {
        System.out.println("Starting flight for: " + getName());
        System.out.println("After 60 seconds, stage 1 separates");
        System.out.println("After 150 seconds, stage 2 separates");
        System.out.println("We're in space!");
    }
}
    
