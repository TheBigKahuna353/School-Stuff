public class Astronaut {
    
    public String name = "Starman";
    public int age = 1;
    public String rocketShip = "Falcon Heavy";
    public String poweredBy = "Electricity";
    public boolean inSpace = true;

    public void printName() {
        System.out.println("Hello, my name is " + name);
    }

    public void printAge() {
        System.out.println("I am " + age + " years old");
    }

    public void printRocket() {
        System.out.println("My rocket is " + rocketShip + " and it is powered by " + poweredBy);
    }

    public boolean isInSpace() {
        return inSpace;
    }

    public static void main(String[] args) {
        Astronaut starman = new Astronaut();
        starman.printName();
        starman.printAge();
        starman.printRocket();
        System.out.println(starman.isInSpace());
    }

}
