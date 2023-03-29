public class SaturnSix extends Rocket {
    
    SaturnSix(String name) {
        super(name, 3);
    }

    // @Override
    void fly() {
        System.out.println("Starting flight for: " + getName());
        System.out.println("After 50 seconds, stage 1 separates");
        System.out.println("After 150 seconds, stage 2 separates");
        System.out.println("After 350 seconds, stage 3 separates");
        System.out.println("We're in space!");
    }
}
