public class Earth extends Planet{
    
    Earth() {
        super("Earth", 3, "Warm");
    }

    String home() {
        return "Home to every one of us";
    }

    long getPopulation() {
        return 7_874_965_825L;
    }
}
