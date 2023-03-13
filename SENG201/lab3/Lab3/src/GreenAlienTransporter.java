import java.util.ArrayList;

public class GreenAlienTransporter {
    
    private String name;
    private int[] cells = new int[4];
    private ArrayList<GreenAlien> passengers;

    public GreenAlienTransporter() {
        this("Green Alien Transporter");
    }
    public GreenAlienTransporter(String name) {
        this.name = name;
        for (int cell=0; cell < 4; cell++) {
            cells[cell] = 100;
        }
        passengers = new ArrayList<GreenAlien>();
    }

    boolean replaceCell(int cell) {
        cell--;
        if (cell < 0 || cell > 3) {
            return false;
        }
        cells[cell] = 100;
        return true;
    }

    boolean travel(int lightyears) {
        int cell = 0;
        for ( ; cell < 3; cell++) {
            if (cells[cell] != 0) {
                break;
            }
        }
        while (lightyears > 0) {
            if (cells[cell] == 0) {
                cell++;
            }
            cells[cell] -= 10;
            lightyears--;
            if (cell == 3 && cells[cell] <= 0) {
                return false;
            }
        }
        return true;
    }

    int getCharge(int cell) {
        cell--;
        if (cell < 0 || cell > 3) {
            return -1;
        }
        return cells[cell];
    }

    boolean addPassenger(GreenAlien alien) {
        if (passengers.contains(alien)) {
            return false;
        }
        passengers.add(alien);
        return true;
    }

    boolean removePassenger(GreenAlien alien) {
        if (!passengers.contains(alien)) {
            return false;
        }
        passengers.remove(alien);
        return true;
    }

    String getPassengerNames() {
        String names = "";
        for (GreenAlien alien : passengers) {
            names += alien.getName() + ", ";
        }
        return names.substring(0, names.length() - 2);
    }

    int countEyes() {
        int eyes = 0;
        for (GreenAlien alien : passengers) {
            eyes += alien.getEyeCount();
        }
        return eyes;
    }

    public ArrayList<String> shoppingList() {
        ArrayList<String> list = new ArrayList<String>();
        for (GreenAlien alien : passengers) {
            String candy = alien.getFavouriteCandy();
            list.add(candy);
        }
        return list;
    }

    public String toString() {
        return "The passengers on " + name + " are:\n" + getPassengerNames() + "\nThe number of eyes on this transporter is: " + countEyes();
    }

    public static void main(String[] args) {
        GreenAlienTransporter transporter = new GreenAlienTransporter("Fun Club"); 
                                                                           
GreenAlien kloup = new GreenAlien("Yyest", 2, "Biscuits");                 
GreenAlien gwerp = new GreenAlien("Lmona", 99, "Marshmellows");            
GreenAlien blarg = new GreenAlien("Troll", 5, "Pop Rocks");                
GreenAlien lesap = new GreenAlien("Nemoa", 3, "Marshmellows");             
GreenAlien hugso = new GreenAlien("Hugso", 8, "Pop Rocks");                
                                                                           
transporter.addPassenger(kloup);                                           
System.out.println(transporter.addPassenger(kloup));                       
transporter.removePassenger(kloup);                                        
System.out.println(transporter.addPassenger(kloup));                       
transporter.addPassenger(gwerp);                                           
transporter.addPassenger(blarg);                                           
transporter.addPassenger(lesap);                                           
transporter.addPassenger(hugso);                                           
                                                                           
System.out.println(transporter);   
    }
}
