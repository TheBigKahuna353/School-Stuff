/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package lab1;

public class App {
    public String getGreeting(String... args) {
        return String.format("Hello, %s!", args.length > 0 ? args[0] : "world");
    }

    public static void main(String[] args) {
        System.out.println(new App().getGreeting(args));
    }
}
