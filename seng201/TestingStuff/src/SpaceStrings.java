public class SpaceStrings {
    
    public int getStringLength(String string) {
        return string.length();
    }

    public int getLetterPosition(String string, char letter) {
        return string.indexOf(letter);
    }

    public String makeAllCaps(String string) {
        return string.toUpperCase();
    }

    public String makeAllLower(String string) {
        return string.toLowerCase();
    }

    public String makeHugeString(String string1, String string2) {
        return string1 + string2;
    }

}
