public class GreenAlien {
    
    private String name;
    private int eyeCount;
    private String favouriteCandy;
    
    public GreenAlien(String name, int eyeCount, String favouriteCandy) {
        this.name = name;
        this.eyeCount = eyeCount;
        this.favouriteCandy = favouriteCandy;
    }

    public GreenAlien() {
        this("Kloup", 6, "Lollypops");
    }

    public String getDescription() {
        return "This Alien is called " + name + " and has " + eyeCount + " eyes. Gross. It seems to enjoy eating " + favouriteCandy;
    }
}
