public class Planet {
    
    private String name;
    private int planetOrder;
    private String temperature;

    Planet(String Name, int order, String temp) {
        name = Name;
        planetOrder = order;
        temperature = temp;
    }

    String orderFromSun() {
        return name + " is number " + planetOrder + " from the Sun";
    }

    String getName() {
        return name;
    }

    public String getTemperature() {
        return temperature;
    }

    String getAxisRotation() {
        return "Counterclockwise";
    }

    String getFact() {
        return name +  " is a planet in the Milky Way galaxy";
    }

    public String toString() {
        return orderFromSun() + " and is " + temperature;
    }
}
