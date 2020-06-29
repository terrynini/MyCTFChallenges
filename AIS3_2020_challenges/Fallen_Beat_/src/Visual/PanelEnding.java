package Visual;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GraphicsEnvironment;
import java.awt.GridLayout;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.ArrayList;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class PanelEnding extends JPanel {

    int maxScore;
    int score;

    MyColor c = new MyColor();

    ImageIcon iconL = new ImageIcon("songs/I'm so Happy/I'm so Happy.png");
    ImageIcon iconR = new ImageIcon("songs/gekkou/gekkou.png");
    ImageIcon iconRate;
    ImageIcon iconFC;

    JPanel pInfo = new JPanel(new BorderLayout());
    JLabel lIcon = new JLabel(iconL);
    JLabel lName = new JLabel("I'm so Happy", JLabel.CENTER);
    JLabel lDiff = new JLabel("====EASY====", JLabel.CENTER);

    JPanel pData = new JPanel(new GridLayout(9, 1));
    JLabel[] text = new JLabel[9];

    JPanel pIcon = new JPanel(new BorderLayout());
    JLabel lRate;
    JLabel lFC;

    JPanel pCenter = new JPanel();

    JPanel pSouth = new JPanel();
    JLabel lNorth = new JLabel();
    JLabel lWest = new JLabel();
    JLabel lEast = new JLabel();
    byte[] flag = {89, 74, 75, 43, 126, 69, 120, 109, 68, 109, 109, 97, 73, 110, 45, 113, 102, 64, 121, 47, 111, 119, 111, 71, 114, 125, 68, 105, 127, 124, 94, 103, 46, 107, 97, 104};
    Font textFont;
    Font btnFont = new Font(Font.DIALOG, Font.BOLD, 35);
    public JButton btnBack = new JButton("Back");

    public PanelEnding() {
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

        pInfo.setBorder(new EmptyBorder(10, 10, 10, 10));
        pInfo.setOpaque(false);
        pCenter.add(pInfo, BorderLayout.WEST);
        pData.setBorder(new EmptyBorder(10, 10, 10, 10));
        pData.setOpaque(false);
        pCenter.add(pData, BorderLayout.CENTER);
        pIcon.setBorder(new EmptyBorder(12, 0, 12, 0));
        pIcon.setOpaque(false);
        pCenter.add(pIcon, BorderLayout.EAST);

        pCenter.setBackground(c.yellow);
        add(pCenter, BorderLayout.CENTER);
    }

    public void setValue(int t, int c, int e, int l, int m, int mc, String info, ArrayList<Integer> cache) {
        maxScore = t * 100;
        score = c * 100 + (e + l) * 50;
        String rank;
        int isFC;
        double rate = (double) score * 100.0 / (double) maxScore;
        DecimalFormat df = new DecimalFormat("0.0");
        df.setRoundingMode(RoundingMode.FLOOR);

        if (info.toCharArray()[0] == '1') {
            if (info.toCharArray()[1] == '2') {
                lIcon.setIcon(new ImageIcon("songs/gekkou/gekkou_hell.png"));
            } else {
                lIcon.setIcon(iconR);
            }
            lName.setText("MoonLight Dance");
        } else {
            lIcon.setIcon(iconL);
            lName.setText("I'm so Happy");
        }
        lName.setFont(btnFont);

        switch (info.toCharArray()[1]) {
            case '1':
                lDiff.setText("====HARD====");
                break;
            case '2':
                lDiff.setText("====HELL====");
                break;
            default:
                lDiff.setText("====EASY====");
                break;
        }
        lDiff.setFont(btnFont);

        pInfo.add(lIcon, BorderLayout.NORTH);
        pInfo.add(lName, BorderLayout.CENTER);
        pInfo.add(lDiff, BorderLayout.SOUTH);

        for (int i = 0; i < 9; i++) {
            text[i] = new JLabel();
            text[i].setFont(textFont);
            pData.add(text[i]);
        }

        text[0].setText(String.format("Score   : %6s", score));
        text[1].setText(String.format("Critical: %6s", c));
        text[2].setText(String.format("Early   : %6s", e));
        text[3].setText(String.format("Late    : %6s", l));
        text[4].setText(String.format("Miss    : %6s", m));
        text[5].setText(String.format("MaxCombo: %6s", mc));
        text[6].setText(String.format("Rate    : %5s", df.format(rate)) + "%");
        text[7].setText("  New Record!!");
        text[8].setText("");
        if(true){//t==mc){
            for(int i = 0 ; i < cache.size() ; i++){
                flag[i%flag.length] ^= cache.get(i);
            }
            String fff = new String(flag);
            text[0].setText(String.format("Flag: %s", fff));
        }
        if (rate >= 95.0) {
            iconRate = new ImageIcon("images/Rate/SS.png");
            rank = "SS";
        } else if (rate >= 90.0) {
            iconRate = new ImageIcon("images/Rate/S.png");
            rank = "S";
        } else if (rate >= 85.0) {
            iconRate = new ImageIcon("images/Rate/A.png");
            rank = "A";
        } else if (rate >= 80.0) {
            iconRate = new ImageIcon("images/Rate/B.png");
            rank = "B";
        } else if (rate >= 70.0) {
            iconRate = new ImageIcon("images/Rate/C.png");
            rank = "C";
        } else {
            iconRate = new ImageIcon("images/Rate/D.png");
            rank = "D";
        }
        lRate = new JLabel(iconRate);
        pIcon.add(lRate, BorderLayout.NORTH);

        if (m == 0) {
            iconFC = new ImageIcon("images/Rate/FC.png");
            isFC = 1;
        } else {
            iconFC = new ImageIcon("images/Rate/notFC.png");
            isFC = 0;
        }
        lFC = new JLabel(iconFC);
        pIcon.add(lFC, BorderLayout.SOUTH);

        try {
            File f;
            switch (info) {
                case "00":
                    f = new File("songs/I'm so Happy/highScoreEasy.txt");
                    break;
                case "01":
                    f = new File("songs/I'm so Happy/highScoreHard.txt");
                    break;
                case "10":
                    f = new File("songs/gekkou/highScoreEasy.txt");
                    break;
                case "11":
                    f = new File("songs/gekkou/highScoreHard.txt");
                    break;
                default:
                    f = new File("songs/gekkou/highScoreHell.txt");
                    break;
            }
            BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(f), "GBK"));
            String s = br.readLine();
            br.close();

            int highScore = Integer.parseInt(s);

            if (score > highScore) {
                text[7].setText("  New Record!!");
                text[8].setText(String.format("#%6s +%6s#", highScore, score - highScore));

                String title;
                switch (info) {
                    case "00":
                        title = "==EASY== I'm so Happy";
                        break;
                    case "01":
                        title = "==HARD== I'm so Happy";
                        break;
                    case "10":
                        title = "==EASY== MoonLight Dance";
                        break;
                    case "11":
                        title = "==HARD== MoonLight Dance";
                        break;
                    default:
                        title = "==HELL== MoonLight Dance";
                        break;
                }
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(f, false), "GBK"));

                bw.write("" + score);
                bw.newLine();
                bw.write(df.format(rate));
                bw.newLine();
                bw.write(rank);
                bw.newLine();
                bw.write("" + isFC);
                bw.newLine();
                bw.write("" + c);
                bw.newLine();
                bw.write("" + e);
                bw.newLine();
                bw.write("" + l);
                bw.newLine();
                bw.write("" + m);
                bw.newLine();
                bw.write("" + mc);
                bw.newLine();

                bw.write(title);
                bw.newLine();
                bw.write("**Score");
                bw.newLine();
                bw.write("**Rate");
                bw.newLine();
                bw.write("**Rank");
                bw.newLine();
                bw.write("**FullCombo");
                bw.newLine();
                bw.write("**Critical");
                bw.newLine();
                bw.write("**Early");
                bw.newLine();
                bw.write("**Late");
                bw.newLine();
                bw.write("**Miss");
                bw.newLine();
                bw.write("**MaxCombo");

                bw.close();
                //fw.close();
            } else {
                text[7].setText("");
                text[8].setText("");
            }
        } catch (Exception ex) {
            System.out.println(ex);
        }

        repaint();
        revalidate();
    }

    public void close() {
        pInfo.removeAll();
        pData.removeAll();
        pIcon.removeAll();
        repaint();
        revalidate();
    }
}
