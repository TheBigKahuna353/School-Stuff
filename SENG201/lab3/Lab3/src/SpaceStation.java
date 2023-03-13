public class SpaceStation {
    
    void dock() {
        System.out.println("Starman floats toward the space station and enters through the airlock");
    }

    void dock(String vehichle) {
        System.out.println("Starman enters the large airlock, piloting " + vehichle);
    }

    void dock(String vehicle, String song) {
        System.out.println("Starman enters the large airlock, piloting " + vehicle);
        System.out.println("... and the station cranks up " + song + " on the entertainment system");
    }

    public static void main(String[] args) {
        SpaceStation station = new SpaceStation();
        station.dock();
        station.dock("the Tesla Roadster");
        station.dock("the Tesla Roadster", "Space Oddity");
    }
}
