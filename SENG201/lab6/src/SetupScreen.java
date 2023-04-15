import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;

public class SetupScreen {
    

    private JFrame frame = new JFrame("jwi179 Rocket Manager");
    private RocketManager rocketmanager;
    private  JTextField nameField;
    private JSlider slider;

    private JPanel selectedRocketsPanel = new JPanel(null);

    public SetupScreen(RocketManager rocketmanager) {
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
        rocketmanager.finishedSetup();
    }

    private String getSelectedRocket(int i) {
        if (rocketmanager.selectedRockets.size() > i) {
            return rocketmanager.selectedRockets.get(i).getName();
        } else {
            return "";
        }
    }


    public void drawSelectedRockets() {
        selectedRocketsPanel.removeAll();
        for (int i = 0; i < slider.getValue(); i++) {
            Button button = new Button(getSelectedRocket(i), i);
            button.addActionListener(e -> {
                rocketmanager.selectedRockets.remove(button.i);
                drawSelectedRockets();
            });
            button.setBounds(10 + 200*i, 400, 150, 50);
            selectedRocketsPanel.add(button);
        }
        selectedRocketsPanel.setBounds(10, 00, 600, 600);
        frame.add(selectedRocketsPanel);
        frame.revalidate();
        frame.repaint();
    }

    public void init() {
        JLabel label1 = new JLabel("Welcome to Rocket Manager!");
        label1.setBounds(10, 10, 250, 20);
        frame.add(label1);

        JLabel label2 = new JLabel("Please enter your name:");
        label2.setBounds(10, 50, 250, 20);
        frame.add(label2);

        JLabel label3 = new JLabel("How many Rockets do you want to manage?");
        label3.setBounds(10, 100, 250, 20);
        frame.add(label3);

        nameField = new JTextField();
        nameField.setBounds(280, 50, 200, 20);
        frame.add(nameField);

        slider = new JSlider(1, 3);
        slider.setBounds(280, 100, 200, 20);
        slider.setMajorTickSpacing(1);
        slider.setSnapToTicks(true);
        slider.setPaintTicks(true);
        slider.addChangeListener(e -> {
            if (slider.getValueIsAdjusting()) {
                return;
            }
            drawSelectedRockets();
        });
        frame.add(slider);

        // create6 buttons for each rocket in a 2x3 grid
        JButton rocket1 = new JButton(rocketmanager.rockets.get(0).getName());
        rocket1.setBounds(10, 150, 150, 50);
        rocket1.addActionListener(e -> {
            rocketmanager.selectedRockets.add(rocketmanager.rockets.get(0));
            drawSelectedRockets();
        });
        frame.add(rocket1);

        JButton rocket2 = new JButton(rocketmanager.rockets.get(1).getName());
        rocket2.setBounds(210, 150, 150, 50);
        rocket2.addActionListener(e -> {
            rocketmanager.selectedRockets.add(rocketmanager.rockets.get(1));
            drawSelectedRockets();
        });
        frame.add(rocket2);

        JButton rocket3 = new JButton("Rocket 3");
        rocket3.setBounds(410, 150, 150, 50);
        rocket3.addActionListener(e -> {
            rocketmanager.selectedRockets.add(new Rocket("Rocket 3"));
            drawSelectedRockets();
        });
        frame.add(rocket3);

        JButton button1 = new JButton("Rocket 4");
        button1.setBounds(10, 250, 150, 50);
        button1.addActionListener(e -> {
            rocketmanager.selectedRockets.add(new Rocket("Rocket 4"));
            drawSelectedRockets();
        });
        frame.add(button1);

        JButton button2 = new JButton("Rocket 5");
        button2.addActionListener(e -> {
            rocketmanager.selectedRockets.add(new Rocket("Rocket 5"));
            drawSelectedRockets();
        });
        button2.setBounds(210, 250, 150, 50);
        frame.add(button2);

        JButton button3 = new JButton("Rocket 6");
        button3.setBounds(410, 250, 150, 50);
        button3.addActionListener(e -> {
            rocketmanager.selectedRockets.add(new Rocket("Rocket 6"));
            drawSelectedRockets();
        });
        frame.add(button3);


        JButton button4 = new JButton("Start");
        button4.setBounds(620, 500, 150, 50);
        button4.addActionListener(e -> {
            rocketmanager.setName(nameField.getText());
            finished();
        });
        frame.add(button4);

        JLabel label4 = new JLabel("Selected rockets");
        label4.setBounds(10, 350, 250, 20);
        frame.add(label4);

        drawSelectedRockets();
    }
}
