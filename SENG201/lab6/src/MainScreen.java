import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class MainScreen {

    JFrame frame = new JFrame("Rocket Manager Main Screen");
    private RocketManager rocketmanager;


    public MainScreen(RocketManager rocketmanager) {
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLayout(null);
        frame.setLocationRelativeTo(null);
        this.rocketmanager = rocketmanager;
        init();
        frame.setVisible(true);
    }

    public void close() {
        frame.dispose();
    }

    public void finished() {
        close();
        rocketmanager.finishedMain();
    }

    public void init() {
        JLabel label = new JLabel("Hello " + rocketmanager.getName() + "!");
        label.setBounds(10, 10, 100, 20);
        frame.add(label);

        JButton button1 = new JButton("Falcon 9");
        button1.setBounds(10, 100, 150, 50);
        frame.add(button1);

        JLabel label2 = new JLabel("Fuel: Full");
        label2.setBounds(10, 200, 100, 20);
        frame.add(label2);

        JButton button2 = new JButton("Falcon Heavy");
        button2.setBounds(200, 100, 150, 50);
        frame.add(button2);

        JLabel label3 = new JLabel("Fuel: Full");
        label3.setBounds(200, 200, 100, 20);
        frame.add(label3);

        JButton button3 = new JButton("Quit");
        button3.setBounds(400, 400, 150, 50);
        frame.add(button3);

        JButton button4 = new JButton("Refuel Rocket");
        button4.setBounds(200, 400, 150, 50);
        frame.add(button4);

        JButton button5 = new JButton("Clean Rocket");
        button5.setBounds(10, 400, 150, 50);
        frame.add(button5);
    }
}
