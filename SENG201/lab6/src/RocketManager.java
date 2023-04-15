import java.util.ArrayList;

public class RocketManager {
    
    private String Name;
    ArrayList<Rocket> rockets = new ArrayList<Rocket>();

    ArrayList<Rocket> selectedRockets = new ArrayList<Rocket>();

    public String getName() {
        return Name;
    }

    public void setName(String name) {
        Name = name;
    }

    public ArrayList<Rocket> getRockets() {
        return rockets;
    }

    public void setRockets(ArrayList<Rocket> rockets) {
        this.rockets = rockets;
    }

    public static void main(String[] args) {

        ArrayList<Rocket> rockets = new ArrayList<Rocket>();
        rockets.add(new Rocket("Falcon 9"));
        rockets.add(new Rocket("Falcon Heavy"));
        rockets.add(new Rocket("Starship"));

        RocketManager rocketmanager = new RocketManager();
        rocketmanager.setRockets(rockets);
        rocketmanager.launchSetupScreen();
    }

    public void launchMainScreen() {
        new MainScreen(this);
    }

    public void launchSetupScreen() {
        new SetupScreen(this);
    }

    public void finishedSetup() {
        launchMainScreen();
    }

    public void finishedMain() {
        System.exit(0);
    }
}
