public class Saturn extends Planet {

    Saturn() {
        super("Saturn", 6, "Cold");
    }

    String getFact() {
        return super.getFact() + ". Saturn has massive rings.";
    }
}
