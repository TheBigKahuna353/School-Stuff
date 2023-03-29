public class Rover implements RemoteControllable {
    private double latitude;
    private double longitude;
    private String mission;

    void setLocation(double lat, double lon) {
        latitude = lat;
        longitude = lon;
    }

    public String getLocation() {
        return "The rover is located " + latitude + ", " + longitude + " on the planet";
    }

    public String getStatusReport() {
        return getLocation() + "\nThe rover is driving to: " + mission;
    }
    
    public void updateMission(String mission) {
        this.mission = mission;
    }
}
