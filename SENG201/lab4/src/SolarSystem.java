import java.util.ArrayList;



public class SolarSystem {
    
    ArrayList<Planet> planets = new ArrayList<>();

    void addPlanet(Planet planet) {
        planets.add(planet);
    }

    void printAllPlanets() {
        for (Planet planet : planets) {
            System.out.println(planet);
        }
    }

    int getPlanetCount() {
        return planets.size();
    }
}
