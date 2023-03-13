public class StarmanFixes {

    double oneTurn;  // holds how far one turn of a socket wrench goes.
    double tightenAmount = 0; // holds how far the wheel nut has been tightened so far.

    public void setOneTurn(double oneTurn) {
        this.oneTurn = oneTurn;
    }

    double getTightenAmount() {
        return tightenAmount;
    }

    void tightenQuarter() {
        tightenAmount += oneTurn / 4;
        System.out.println("Starman tightens the nut one quarter of a turn");
    }

    void tightenHalf() {
        tightenQuarter();
        tightenQuarter();
        System.out.println("The nut has been tightened half a turn");
    }

    void tightenFull() {
        tightenHalf();
        tightenHalf();
        System.out.println("The nut has been tightened a full turn");
    }

    public static void main(String[] args) {
        StarmanFixes wheelnut = new StarmanFixes();
    	
        wheelnut.setOneTurn(1);
        wheelnut.tightenQuarter();
        wheelnut.tightenHalf();
        wheelnut.tightenFull();
        System.out.println(wheelnut.getTightenAmount());
    }
}
