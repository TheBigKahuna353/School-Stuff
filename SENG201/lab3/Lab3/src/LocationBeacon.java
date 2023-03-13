public class LocationBeacon {
    
    // Starman has been thinking about installing a location beacon in his roadster so scientists 
    // from Earth can keep track of his position in the Universe. All the beacon does is emit a 'heartbeat' 
    // signal with a current timestamp and distance.

    // Today, the time is 14:31 hours (24 hour time) and Starman is 300,000 kilometres away from Earth (relatively close!) 
    // He travels 60,000km away from the earth every hour in his Red Tesla Roadster. Output a heartbeat every ten minutes of 
    // the time and his distance away from Earth.

    int hours;
    int minutes;
    int distance;

    void heartBeat(int startHour, int startMinute, int startDistance, int speed, int duration) {
        hours = startHour;
        minutes = startMinute;
        distance = startDistance;
        int time = duration;
        int speedPer10Minute = speed / 6;
        for (int i = 0; i <= time; i++) {
            if (i % 10 == 0 && i != 0) {
                distance += speedPer10Minute;
                String temp = String.format("[%d:%d] Starman is %dkm away from Earth", hours, minutes, distance);
                System.out.println(temp);
            }
            minutes++;
            if (minutes == 60) {
                hours++;
                minutes = 0;
            }
            if (hours == 24)
                hours = 0;
        }
    }

    public static void main(String[] args) {
        LocationBeacon beacon = new LocationBeacon();
        beacon.heartBeat(14, 31, 300000, 60000, 60);

        beacon.heartBeat(23, 28, 630000, 10000, 90);
    }

}
