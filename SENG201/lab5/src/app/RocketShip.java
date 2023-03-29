package app;
public class RocketShip {

    int MAX_FUEL_LEVEL = 100;

    int fuelLevel;
    int currentHeight;

    public RocketShip(int fuelLevel) {
        this.fuelLevel = fuelLevel;
        this.currentHeight = 0;
    }

    public int getFuelLevel() {
        return fuelLevel;
    }

    public int getCurrentHeight() {
        return currentHeight;
    }

    public void fuelUp(int fuelAmount) {
        fuelLevel += fuelAmount;
    }

    public void takeOff() {
        if (fuelLevel < 20) {
            throw new IllegalStateException("Not enough fuel!");
        }
        fuelLevel -= 20;
        currentHeight += 20;
    }

    public void goHigher() {
        fuelLevel -= 10;
        currentHeight += 50;
    }

    public void goLower() {
        currentHeight -= 50;
    }

    public void land() {
        currentHeight = 0;
    }
}