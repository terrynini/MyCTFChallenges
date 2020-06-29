package Visual;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class PanelMenu extends JPanel {

    MyColor c = new MyColor();
    ImageIcon logo = new ImageIcon("images/fallenBeatLogo.png");
    
    JPanel pBtnList = new JPanel(new GridLayout(4, 1));
    JLabel lLogo = new JLabel(logo);
    JLabel lNorth = new JLabel();
    JLabel lSouth = new JLabel();
    JLabel lEast = new JLabel();
    
    Font btnFont = new Font(Font.DIALOG, Font.BOLD, 35);
    public JButton btnStart = new JButton("Start");
    public JButton btnHighScore = new JButton("High Score");
    public JButton btnHelp = new JButton("Help");
    public JButton btnExit = new JButton("Exit");

    public PanelMenu() {
        setLayout(new BorderLayout());
        setBackground(c.brown);
        
        lLogo.setPreferredSize(new Dimension(logo.getIconWidth()+150, logo.getIconHeight()));
        add(lLogo, BorderLayout.WEST);

        lNorth.setPreferredSize(new Dimension(1280, 130));
        add(lNorth, BorderLayout.NORTH);
        lSouth.setPreferredSize(new Dimension(1280, 130));
        add(lSouth, BorderLayout.SOUTH);
        lEast.setPreferredSize(new Dimension(100, 720));
        add(lEast, BorderLayout.EAST);

        btnStart.setUI(new MenuButtonUI());
        btnStart.setBackground(c.gray);
        btnStart.setFont(btnFont);
        btnStart.setForeground(c.white);
        pBtnList.add(btnStart);
        
        btnHighScore.setUI(new MenuButtonUI());
        btnHighScore.setBackground(c.gray);
        btnHighScore.setFont(btnFont);
        btnHighScore.setForeground(c.white);
        pBtnList.add(btnHighScore);
        
        btnHelp.setUI(new MenuButtonUI());
        btnHelp.setBackground(c.gray);
        btnHelp.setFont(btnFont);
        btnHelp.setForeground(c.white);
        pBtnList.add(btnHelp);
        
        btnExit.setUI(new MenuButtonUI());
        btnExit.setBackground(c.gray);
        btnExit.setFont(btnFont);
        btnExit.setForeground(c.white);
        pBtnList.add(btnExit);
        
        pBtnList.setBackground(c.brown);
        add(pBtnList, BorderLayout.CENTER);
    }
}
