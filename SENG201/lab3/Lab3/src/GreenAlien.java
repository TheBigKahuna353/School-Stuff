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

    public String toString() {
        return "This Alien is called " + name + " and has " + eyeCount + " eyes. Gross. It seems to enjoy eating " + favouriteCandy;
    }

    public boolean equals(GreenAlien other) {
        return this.name.equals(other.name) && this.eyeCount == other.eyeCount && this.favouriteCandy.equals(other.favouriteCandy);
    }

    public String getName() {
        return name;
    }

    public String getFavouriteCandy() {
        return favouriteCandy;
    }

    public int getEyeCount() {
        return eyeCount;
    }

    public static void main(String[] args) {
        GreenAlien kloup = new GreenAlien();
        GreenAlien lesap = new GreenAlien();
        GreenAlien gwerp = new GreenAlien("Gwerp", 4, "Marshmellows");
        GreenAlien blarg = new GreenAlien("Kloup", 3, "Pop Rocks");

        System.out.println(kloup.equals(lesap));
        System.out.println(gwerp.equals(lesap));
        System.out.println(kloup.equals(blarg));
    }
}
