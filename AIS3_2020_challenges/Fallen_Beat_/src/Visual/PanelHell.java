package Visual;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GraphicsEnvironment;
import java.awt.GridLayout;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class PanelHell extends JPanel {

    MyColor c = new MyColor();

    JPanel pText = new JPanel(new GridLayout(10, 1));
    JLabel[] text = new JLabel[10];

    JPanel pHell = new JPanel(new BorderLayout());

    JPanel pCenter = new JPanel(new GridLayout(1, 2));

    JPanel pSouth = new JPanel();
    JLabel lNorth = new JLabel("Please turn off your Chinese Input Method.", JLabel.CENTER);
    JLabel lWest = new JLabel();
    JLabel lEast = new JLabel();

    ImageIcon iconHell = new ImageIcon("songs/gekkou/gekkou_hell.png");
    JLabel lIcon = new JLabel(iconHell);
    JLabel lName = new JLabel("MoonLight Dance", JLabel.CENTER);
    JPanel pBtn = new JPanel();

    Font btnFont = new Font(Font.DIALOG, Font.BOLD, 35);
    Font textFont;
    public JButton btnBack = new JButton("Back");
    public JButton btnHell = new JButton("Hell");

    public PanelHell() {
        setLayout(new BorderLayout());
        setBackground(c.brown);

        try {
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("images/consola.ttf")));
        } catch (Exception ex) {
            System.out.println(ex);
        }
        textFont = new Font("Consolas", Font.BOLD, 35);

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

        for (int i = 0; i < 10; ++i) {
            text[i] = new JLabel();
            text[i].setFont(textFont);
            text[i].setHorizontalAlignment(JLabel.CENTER);
            pText.add(text[i]);
        }
        text[0].setText("=====RECORD=====");
        text[1].setText("Score   :");
        text[2].setText("Rate    :");
        text[3].setText("Rank    :");
        text[4].setText("");
        text[5].setText("Critical:");
        text[6].setText("Early   :");
        text[7].setText("Late    :");
        text[8].setText("Miss    :");
        text[9].setText("MaxCombo:");
        pText.setOpaque(false);
        pText.setBorder(new EmptyBorder(10, 30, 10, 10));
        pCenter.add(pText);

        pHell.add(lIcon, BorderLayout.NORTH);
        lName.setFont(btnFont);
        pHell.add(lName, BorderLayout.CENTER);
        btnHell.setUI(new CommonButtonUI());
        btnHell.setBackground(c.gray);
        btnHell.setFont(btnFont);
        btnHell.setForeground(c.white);
        btnHell.setPreferredSize(new Dimension(150, 70));
        pBtn.add(btnHell);
        pBtn.setOpaque(false);
        pHell.add(pBtn, BorderLayout.SOUTH);
        pHell.setOpaque(false);
        pCenter.add(pHell);

        pCenter.setBackground(c.blue);
        add(pCenter, BorderLayout.CENTER);
    }

    public void readRecord() throws Exception {

        File f = new File("songs/gekkou/highScoreHell.txt");
        BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(f), "GBK"));

        String[] data = new String[9];

        for (int i = 0; i < 9 && br.ready(); ++i) {
            String s = br.readLine();
            if (s.toCharArray()[0] == '*' || s.toCharArray()[0] == '=') {
                --i;
                continue;
            }
            data[i] = s;
        }
        br.close();

        text[1].setText("Score   :" + String.format("%6s", data[0]));
        text[2].setText("Rate    :" + String.format("%5s", data[1]) + "%");
        text[3].setText("Rank    :" + String.format("%6s", data[2]));
        text[4].setText(("0".equals(data[3])) ? "" : "[Full Combo]");
        text[5].setText("Critical:" + String.format("%6s", data[4]));
        text[6].setText("Early   :" + String.format("%6s", data[5]));
        text[7].setText("Late    :" + String.format("%6s", data[6]));
        text[8].setText("Miss    :" + String.format("%6s", data[7]));
        text[9].setText("MaxCombo:" + String.format("%6s", data[8]));

    }
}
