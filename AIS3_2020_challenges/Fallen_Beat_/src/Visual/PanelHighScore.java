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

public class PanelHighScore extends JPanel {

    MyColor c = new MyColor();

    ImageIcon iconImSoHappyHS = new ImageIcon("songs/I'm so Happy/I'm so Happy_HS.png");
    ImageIcon iconGekkouHS = new ImageIcon("songs/gekkou/gekkou_HS.png");
    JLabel[] lIconHS = new JLabel[2];

    JPanel[] pRecord = new JPanel[2];
    JPanel[] pGap = new JPanel[2];
    JPanel[] pTextPlate = new JPanel[2];
    JPanel[] pText = new JPanel[4];
    JLabel[][] text = new JLabel[4][10];
    JPanel pCenter = new JPanel(new GridLayout(2, 1));

    JPanel pSouth = new JPanel();
    JLabel lNorth = new JLabel();
    JLabel lWest = new JLabel();
    JLabel lEast = new JLabel();

    Font textFont;
    Font btnFont = new Font(Font.DIALOG, Font.BOLD, 35);
    public JButton btnBack = new JButton("Back");

    public PanelHighScore() {
        setLayout(new BorderLayout());
        setBackground(c.brown);

        try {
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("images/consola.ttf")));
        } catch (Exception ex) {
            System.out.println(ex);
        }
        textFont = new Font("Consolas", Font.BOLD, 25);

        lNorth.setPreferredSize(new Dimension(1280, 100));
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

        pRecord[0] = new JPanel(new BorderLayout());
        pRecord[0].setBackground(c.blue);
        pGap[0] = new JPanel();
        pGap[0].setBackground(c.brown);
        pRecord[0].add(pGap[0], BorderLayout.SOUTH);
        lIconHS[0] = new JLabel(iconImSoHappyHS);
        lIconHS[0].setBorder(new EmptyBorder(0, 10, 0, 10));
        pRecord[0].add(lIconHS[0], BorderLayout.WEST);
        pCenter.add(pRecord[0]);

        pRecord[1] = new JPanel(new BorderLayout());
        pRecord[1].setBackground(c.blue);
        pGap[1] = new JPanel();
        pGap[1].setBackground(c.brown);
        pRecord[1].add(pGap[1], BorderLayout.NORTH);
        lIconHS[1] = new JLabel(iconGekkouHS);
        lIconHS[1].setBorder(new EmptyBorder(0, 10, 0, 10));
        pRecord[1].add(lIconHS[1], BorderLayout.WEST);
        pCenter.add(pRecord[1]);

        for (int i = 0; i < 2; ++i) {
            pTextPlate[i] = new JPanel(new GridLayout(1, 2));
            pTextPlate[i].setBorder(new EmptyBorder(10, 10, 10, 10));
            pTextPlate[i].setOpaque(false);
            pRecord[i].add(pTextPlate[i], BorderLayout.CENTER);
        }

        for (int i = 0; i < 4; ++i) {
            pText[i] = new JPanel(new GridLayout(5, 2));
            pText[i].setBackground((i % 2 == 0) ? c.white : c.yellow);
            pText[i].setBorder(new EmptyBorder(10, 10, 10, 10));
            if (i < 2) {
                pTextPlate[0].add(pText[i]);
            } else {
                pTextPlate[1].add(pText[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 10; ++j) {
                text[i][j] = new JLabel();
                text[i][j].setFont(textFont);
            }
            for (int j = 0; j < 5; j++) {
                pText[i].add(text[i][j]);
                pText[i].add(text[i][j + 5]);
            }
            text[i][0].setText((i % 2 == 0) ? "====EASY====" : "====HARD====");
            text[i][1].setText("Score:");
            text[i][2].setText("Rate :");
            text[i][3].setText("Rank :");
            text[i][4].setText("");
            text[i][5].setText("Critical:");
            text[i][6].setText("Early   :");
            text[i][7].setText("Late    :");
            text[i][8].setText("Miss    :");
            text[i][9].setText("MaxCombo:");
        }

        pCenter.setOpaque(false);
        add(pCenter, BorderLayout.CENTER);
    }

    public void readRecord() throws Exception {
        for (int i = 0; i < 4; ++i) {
            File f;
            switch (i) {
                case 0:
                    f = new File("songs/I'm so Happy/highScoreEasy.txt");
                    break;
                case 1:
                    f = new File("songs/I'm so Happy/highScoreHard.txt");
                    break;
                case 2:
                    f = new File("songs/gekkou/highScoreEasy.txt");
                    break;
                default:
                    f = new File("songs/gekkou/highScoreHard.txt");
                    break;
            }
            BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(f), "GBK"));

            String[] data = new String[9];

            for (int j = 0; j < 9 && br.ready(); ++j) {
                String s = br.readLine();
                if (s.toCharArray()[0] == '*' || s.toCharArray()[0] == '=') {
                    --j;
                    continue;
                }
                data[j] = s;
            }
            br.close();

            text[i][0].setText((i % 2 == 0) ? "====EASY====" : "====HARD====");
            text[i][1].setText("Score:" + String.format("%6s", data[0]));
            text[i][2].setText("Rate :" + String.format("%5s", data[1]) + "%");
            text[i][3].setText("Rank :" + String.format("%6s", data[2]));
            text[i][4].setText(("0".equals(data[3])) ? "" : "[Full Combo]");
            text[i][5].setText("Critical:" + String.format("%4s", data[4]));
            text[i][6].setText("Early   :" + String.format("%4s", data[5]));
            text[i][7].setText("Late    :" + String.format("%4s", data[6]));
            text[i][8].setText("Miss    :" + String.format("%4s", data[7]));
            text[i][9].setText("MaxCombo:" + String.format("%4s", data[8]));
        }
    }
}
