import java.util.Collection;

public class StarmansBoss {
    
    int getCollectiveAge(Collection<Astronaut> astronauts) {
        int totalAge = 0;
        for (Astronaut astronaut : astronauts) {
            totalAge += astronaut.getAge();
        }
        return totalAge;
    }
}
