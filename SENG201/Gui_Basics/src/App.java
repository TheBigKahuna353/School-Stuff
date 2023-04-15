import java.awt.*;
import java.awt.event.*;

import javax.swing.*;


public class App {

private JFrame frame;

    public static void main(String[] args) throws Exception {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    App window = new App();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    public App() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setSize(600, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblNewLabel = new JLabel("New label");
        lblNewLabel.setBounds(10, 10, 100, 14);
        frame.getContentPane().add(lblNewLabel);

        JLabel lblNewLabel_1 = new JLabel("New label");
        lblNewLabel_1.setBounds(10, 35, 100, 14);
        frame.getContentPane().add(lblNewLabel_1);

        TextField textField = new TextField();
        textField.setBounds(24, 79, 544, 103);
        frame.getContentPane().add(textField);
        textField.setColumns(10);

        JButton btnNewButton = new JButton("New button");
        btnNewButton.setBounds(10, 227, 119, 23);
        btnNewButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.out.println("Hello World");
            }
        });
        frame.getContentPane().add(btnNewButton);
    }
}
