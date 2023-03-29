public abstract class Rocket {
    
    protected String name;
    protected int numStages;

    abstract void fly();

    public String getName() {
        return name;
    }

    Rocket(String name, int numStages) {
        this.name = name;
        this.numStages = numStages;
    }
}
