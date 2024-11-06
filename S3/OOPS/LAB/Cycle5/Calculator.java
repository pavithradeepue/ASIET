import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class Calculate {
    float sum(float a, float b) {
        return a + b;
    }

    float sub(float a, float b) {
        return a - b;
    }

    float div(float a, float b) {
        try {
            return a / b;
        } catch (Exception e) {
            System.out.println("Division by 0 is not possible");
            return Float.POSITIVE_INFINITY;
        }
    }

    float mul(float a, float b) {
        return a * b;
    }
}

class UI implements ActionListener {
    JFrame frame;
    JTextField inputField, resultField;
    float a, b, result;
    String operator;
    Calculate calc;
    
    // Operator buttons
    JButton sum, sub, mul, div, equals, clear;

    public UI() {
        frame = new JFrame("Calculator");
        
        // Input field for numbers
        inputField = new JTextField(16);
        inputField.setHorizontalAlignment(JTextField.RIGHT);
        inputField.setEditable(true);
        inputField.setPreferredSize(new Dimension(300, 50));

        // Result field
        resultField = new JTextField(16);
        resultField.setHorizontalAlignment(JTextField.RIGHT);
        resultField.setEditable(false);
        resultField.setPreferredSize(new Dimension(300, 50));
        
        calc = new Calculate();
        
        // Buttons for operations
        sum = new JButton("+");
        sub = new JButton("-");
        mul = new JButton("*");
        div = new JButton("/");
        equals = new JButton("=");
        clear = new JButton("C");

        // Adding action listeners to the buttons
        sum.addActionListener(this);
        sub.addActionListener(this);
        mul.addActionListener(this);
        div.addActionListener(this);
        equals.addActionListener(this);
        clear.addActionListener(this);

        // Panel for operator buttons
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(2, 3, 5, 5));
        panel.add(sum);
        panel.add(sub);
        panel.add(mul);
        panel.add(div);
        panel.add(clear);
        panel.add(equals);

        // Setting up the frame
        frame.setLayout(new BorderLayout());
        frame.add(inputField, BorderLayout.NORTH);
        frame.add(resultField, BorderLayout.CENTER);
        frame.add(panel, BorderLayout.SOUTH);
        
        frame.setSize(300, 250); // Adjusted size as we no longer need the number buttons
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();

        if (command.equals("C")) {
            inputField.setText("");
            resultField.setText("");
            a = b = result = 0;
            operator = "";
        } else if (command.equals("=")) {
            // Perform calculation when '=' is clicked
            try {
                b = Float.parseFloat(inputField.getText());
                switch (operator) {
                    case "+":
                        result = calc.sum(a, b);
                        break;
                    case "-":
                        result = calc.sub(a, b);
                        break;
                    case "*":
                        result = calc.mul(a, b);
                        break;
                    case "/":
                        result = calc.div(a, b);
                        break;
                    default:
                        resultField.setText("Error");
                        return;
                }
                // Display result in the result field
                resultField.setText(String.valueOf(result));
                a = result; // Set the result to 'a' for future operations
            } catch (NumberFormatException ex) {
                resultField.setText("Invalid Input");
            }
        } else {
            // When an operator is clicked
            if (!inputField.getText().isEmpty()) {
                a = Float.parseFloat(inputField.getText());
                operator = command;
                inputField.setText(""); // Clear the input field
            }
        }
    }
}

class Main {
    public static void main(String[] args) {
        new UI();
    }
}
