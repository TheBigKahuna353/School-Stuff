package app;

public class FuelManager {
    
    int level;
    int maxLevel;
    
    public FuelManager(int maxLevel) {
        this.level = this.maxLevel = maxLevel;
    }
    
    public int getLevel() {
        return level;
    }
    
    public int getMaxLevel() {
        return maxLevel;
    }
    
    public void incrementLevel() throws FuelException {
        if (level >= maxLevel) {
            throw new FuelException("Fuel level cannot go above " + maxLevel);
        }
        level++;
    }
    
    public void decrementLevel() throws FuelException {
        if (level <= 0) {
            throw new FuelException("Fuel level cannot go below 0");
        }
        level--;
    }

    public void simulateFlight(int distance) {
        int tempLevel = level;
        try {
            for (int i = 0; i < distance; i++) {
                decrementLevel();
            }
        } catch (FuelException e) {
            System.out.println(e.getMessage());
            return;
        } finally {
            level = tempLevel;
        }
        System.out.println("Flight successful");
    }

    public void addMaxLevel(String amountToAdd) throws FuelException{ 

        try {
            maxLevel += Integer.parseInt(amountToAdd);
        } catch (NumberFormatException e) {
            throw new FuelException("Cannot add non-numeric value to level");
        }
    
        level = maxLevel;
    
    }
    
}