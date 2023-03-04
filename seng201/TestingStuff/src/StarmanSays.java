public class StarmanSays {

    public String sayDontPanic() {
        return "Don't Panic!";
    }

    public String sayJavaCool() {
        return "Java is cool";
    }

    public String sayGoodbyeWorld() {
        return "Goodbye, World!";
    }

    public String sayHello() {
        return "Hello";
    }

    public static void main(String[] args) {

        StarmanSays starman = new StarmanSays();
        System.out.println(starman.sayHello());
        System.out.println(starman.sayDontPanic());
    }
}
