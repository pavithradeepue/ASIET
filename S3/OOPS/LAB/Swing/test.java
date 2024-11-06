/*Pavithra Deepu E
CSE AI 47
Program to demostrate swing */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
class test implements ActionListener{

	JLabel l;
	JTextField t;
	JButton b;
	
	test()
	{

		JFrame f = new JFrame("TextFeild");
		l = new JLabel("Nothing Entered");
		t = new JTextField(16);
		b = new JButton("Submit");
		
		JPanel p = new JPanel(new GridLayout(3,1));
		p.add(l);
		p.add(t);
		p.add(b);
		
		b.addActionListener(this);
		
		f.add(p);
		f.setSize(300,300);
		f.show();
		
	}
	public void actionPerformed(ActionEvent e)
	{
		String s = e.getActionCommand();
		if(s.equals("Submit"))
		{
			l.setText(t.getText());
			t.setText("  ");
		}
	}
	
	public static void main(String args[])
	{
		test t = new test();
	}
}

