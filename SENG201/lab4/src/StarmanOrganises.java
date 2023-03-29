import java.util.ArrayList;
import java.util.List;

public class StarmanOrganises {
    
    private List<RemoteControllable> controllables = new ArrayList<RemoteControllable>();

    void addControllable(Object o) {
        // Add the controllable to a list
        if (o instanceof RemoteControllable) {
            controllables.add((RemoteControllable) o);
        }
    }

    void getAllStatusReports() {
        // Loop through the list and print the status report of each controllable
        for (RemoteControllable controllable : controllables) {
            System.out.println(controllable.getStatusReport());
        }
    }
}
