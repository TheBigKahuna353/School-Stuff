import java.util.Scanner;


public class hangman {
    
    public static void printWord(String word) {
        for (int i = 0; i < word.length(); i++) {
            System.out.print(word.charAt(i) + " ");
        }
        System.out.println();
    }

    public static String getWord() {
        String[] wordStrings = {"hello", "world", "java", "programming", "computer", "science", "hangman", "game", "fun", "learning"};
        int wordIndex = (int) (Math.random() * wordStrings.length);
        return wordStrings[wordIndex];
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String word = hangman.getWord();
        String guessedWord = "_ ".repeat(word.length());
        int failedGuessesLeft = 5;

        hangman.printWord(guessedWord);
        while (failedGuessesLeft > 0) {
            System.out.println("You have " + failedGuessesLeft + " guesses left.");
            System.out.print("Guess a letter: ");
            char guess = input.nextLine().charAt(0);
            boolean correctGuess = false;
            for (int i = 0; i < word.length(); i++) {
                if (word.charAt(i) == guess) {
                    guessedWord = guessedWord.substring(0, i * 2) + guess + guessedWord.substring(i * 2 + 1);
                    correctGuess = true;
                }
            }
            if (!correctGuess) {
                failedGuessesLeft--;
            }
            hangman.printWord(guessedWord);
            if (guessedWord.indexOf("_") == -1) {
                System.out.println("You win!");
                break;
            }
        }
        if (failedGuessesLeft == 0) {
            System.out.println("You lose!");
        }
        input.close();
    }
}
