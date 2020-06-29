package Visual;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class PanelStrat extends JPanel {

    MyColor c = new MyColor();
    ImageIcon iconImSoHappy = new ImageIcon("songs/I'm so Happy/I'm so Happy.png");
    ImageIcon iconGekkou = new ImageIcon("songs/gekkou/gekkou.png");

    JPanel pCenter = new JPanel(new GridLayout(1, 2));
    JPanel pSouth = new JPanel();
    JLabel lNorth = new JLabel("Please turn off your Chinese Input Method.",JLabel.CENTER);
    JLabel lWest = new JLabel();
    JLabel lEast = new JLabel();

    JPanel pL = new JPanel(new BorderLayout());
    JPanel gapL = new JPanel();
    JLabel lIconL = new JLabel(iconImSoHappy);
    JPanel pLCenter = new JPanel(new BorderLayout());
    JLabel lNameL = new JLabel("I'm so Happy", JLabel.CENTER);
    JPanel pLSouth = new JPanel(new GridLayout(1, 3));
    JPanel[] pBtnL = new JPanel[3];
    public JButton[] btnL = new JButton[3];

    JPanel pR = new JPanel(new BorderLayout());
    JPanel gapR = new JPanel();
    JLabel lIconR = new JLabel(iconGekkou);
    JPanel pRCenter = new JPanel(new BorderLayout());
    JLabel lNameR = new JLabel("MoonLight Dance", JLabel.CENTER);
    JPanel pRSouth = new JPanel(new GridLayout(1, 3));
    JPanel[] pBtnR = new JPanel[3];
    public JButton[] btnR = new JButton[3];

    Font btnFont = new Font(Font.DIALOG, Font.BOLD, 35);
    public JButton btnBack = new JButton("Back");

    public PanelStrat() {
        setLayout(new BorderLayout());
        setBackground(c.brown);

        lNorth.setPreferredSize(new Dimension(1280, 100));
        lNorth.setFont(btnFont);
        add(lNorth, BorderLayout.NORTH);
        lEast.setPreferredSize(new Dimension(100, 720));
        add(lEast, BorderLayout.EAST);
        lWest.setPreferredSize(new Dimension(100, 720));
        add(lWest, BorderLayout.WEST);

        btnBack.setUI(new CommonButtonUI());
        btnBack.setBackground(c.gray);
        btnBack.setFont(btnFont);
        btnBack.setForeground(c.white);
        btnBack.setPreferredSize(new Dimension(150, 70));
        pSouth.add(btnBack);
        pSouth.setPreferredSize(new Dimension(1280, 100));
        pSouth.setBackground(c.brown);
        add(pSouth, BorderLayout.SOUTH);

        gapL.setBackground(c.brown);
        pL.add(gapL, BorderLayout.EAST);
        pLCenter.setBackground(c.blue);
        pLCenter.add(lIconL, BorderLayout.NORTH);
        lNameL.setFont(btnFont);
        pLCenter.add(lNameL, BorderLayout.CENTER);
        pLSouth.setOpaque(false);
        pLCenter.add(pLSouth, BorderLayout.SOUTH);
        pL.add(pLCenter, BorderLayout.CENTER);
        pL.setBackground(c.blue);
        pCenter.add(pL);

        gapR.setBackground(c.brown);
        pR.add(gapR, BorderLayout.WEST);
        pRCenter.setBackground(c.blue);
        pRCenter.add(lIconR, BorderLayout.NORTH);
        lNameR.setFont(btnFont);
        pRCenter.add(lNameR, BorderLayout.CENTER);
        pRSouth.setOpaque(false);
        pRCenter.add(pRSouth,BorderLayout.SOUTH);
        pR.add(pRCenter, BorderLayout.CENTER);
        pR.setBackground(c.blue);
        pCenter.setOpaque(false);
        pCenter.add(pR);

        for (int i = 0; i < 3; ++i) {
            switch (i) {
                case 0:
                    btnL[i] = new JButton("Trial");
                    btnR[i] = new JButton("Trial");
                    break;
                case 1:
                    btnL[i] = new JButton("Easy");
                    btnR[i] = new JButton("Easy");
                    break;
                default:
                    btnL[i] = new JButton("Hard");
                    btnR[i] = new JButton("Hard");
                    break;
            }
            btnL[i].setUI(new CommonButtonUI());
            btnL[i].setBackground(c.gray);
            btnL[i].setFont(btnFont);
            btnL[i].setForeground(c.white);
            btnL[i].setPreferredSize(new Dimension(0, 70));
            pLSouth.add(btnL[i]);
            btnR[i].setUI(new CommonButtonUI());
            btnR[i].setBackground(c.gray);
            btnR[i].setFont(btnFont);
            btnR[i].setForeground(c.white);
            btnR[i].setPreferredSize(new Dimension(0, 70));
            pRSouth.add(btnR[i]);
        }

        pCenter.setBackground(c.brown);
        add(pCenter, BorderLayout.CENTER);
    }
}
