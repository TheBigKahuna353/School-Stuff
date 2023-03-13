public class StarmanSummits {
    
    void climbMountain(double height, double dash, double slide) {
        int dashNum = 0;
        while (height > 0) {
            height -= dash;
            dashNum++;
            if (height <= 0) {
                System.out.println(String.format("Starman needs to dash %d times before he reaches the top of the mountain", dashNum));
                break;
            }
            height += slide;
        }
    }

    public static void main(String[] args) {
        StarmanSummits starman = new StarmanSummits();
        starman.climbMountain(21287.4, 16.4, 4.3);
    }
}
