package Visual;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class PanelHelp extends JPanel {

    MyColor c = new MyColor();

    JPanel pCenter = new JPanel(new GridLayout(1, 2));
    JPanel pSouth = new JPanel();
    JPanel pNorth = new JPanel();
    JLabel lWest = new JLabel();
    JLabel lEast = new JLabel();

    ImageIcon help1 = new ImageIcon("images/Help/help_1.png");
    ImageIcon help2 = new ImageIcon("images/Help/help_2.png");

    Font btnFont = new Font(Font.DIALOG, Font.BOLD, 35);
    public JButton btnBack = new JButton("Back");
    public JButton btnHell = new JButton();

    public PanelHelp() {
        setLayout(new BorderLayout());
        setBackground(c.brown);

        lEast.setPreferredSize(new Dimension(100, 720));
        add(lEast, BorderLayout.EAST);
        lWest.setPreferredSize(new Dimension(100, 720));
        add(lWest, BorderLayout.WEST);
        
        btnHell.setUI(new TransparentButtonUI());
        btnHell.setBackground(c.gray);
        btnHell.setFont(btnFont);
        btnHell.setForeground(c.white);
        btnHell.setPreferredSize(new Dimension(150, 70));
        pNorth.add(btnHell);
        pNorth.setPreferredSize(new Dimension(1280, 100));
        pNorth.setBackground(c.brown);
        add(pNorth, BorderLayout.NORTH);

        btnBack.setUI(new CommonButtonUI());
        btnBack.setBackground(c.gray);
        btnBack.setFont(btnFont);
        btnBack.setForeground(c.white);
        btnBack.setPreferredSize(new Dimension(150, 70));
        pSouth.add(btnBack);
        pSouth.setPreferredSize(new Dimension(1280, 100));
        pSouth.setBackground(c.brown);
        add(pSouth, BorderLayout.SOUTH);

        pCenter.add(new JLabel(help1));
        pCenter.add(new JLabel(help2));
        pCenter.setBackground(c.yellow);
        add(pCenter, BorderLayout.CENTER);
    }
}
