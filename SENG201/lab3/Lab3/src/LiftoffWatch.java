public class LiftoffWatch {
    
    double temp;
    String weather;
    double wind;

    void setTemp(double temp) {
        this.temp = temp;
    }

    void setWeather(String weather) {
        this.weather = weather;
    }

    void setWind(double wind) {
        this.wind = wind;
    }

    boolean canWeLaunch() {
        if (temp < 16.5 || temp > 34) {
            return false;
        }
        if (weather == "Sunny" && wind < 60) {
            return true;
        }
        if (weather == "Cloudy" && wind < 45) {
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LiftoffWatch launch = new LiftoffWatch();

        launch.setTemp(27.0);
        launch.setWeather("Sunny");
        launch.setWind(53);
        System.out.println(launch.canWeLaunch());
    }
}
