public class SpaceStation implements RemoteControllable {
    
    private String planet;
    private String mission;

    SpaceStation(String planet) {
        this.planet = planet;
    }

    String getLocation() {
        return "The space station floats around the planet " + planet;
    }

    public String getStatusReport() {
        return getLocation() + "\nThe station is on a mission to: " + mission;
    }

    public void updateMission(String mission) {
        this.mission = mission;
    }

}
