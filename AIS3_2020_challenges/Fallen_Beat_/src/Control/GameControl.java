package Control;

import Visual.*;
import java.awt.Font;
import java.awt.GraphicsEnvironment;
import java.awt.LayoutManager;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class GameControl extends Thread implements KeyListener {

    Frame f;
    PanelGaming pg;
    PanelEnding pe;

    MyColor c = new MyColor();

    AudioPlayer music;

    JLabel note;
    JPanel pFumen = new JPanel((LayoutManager) null);
    JPanel pCL = new JPanel((LayoutManager) null);
    JLabel lCL;
    ImageIcon bt = new ImageIcon("images/BT.png");
    ImageIcon fx = new ImageIcon("images/FX.png");
    ImageIcon cl = new ImageIcon("images/CL.png");
    ImageIcon aeY = new ImageIcon("images/ActionEffect/yellow.png");
    ImageIcon aeG = new ImageIcon("images/ActionEffect/green.png");
    ImageIcon aeB = new ImageIcon("images/ActionEffect/blue.png");
    ImageIcon aeR = new ImageIcon("images/ActionEffect/red.png");
    ImageIcon aeW = new ImageIcon("images/ActionEffect/white.png");
    JLabel[] lAE = new JLabel[4];
    ArrayList<Integer> cache;
    JLabel lbanner;

    JLabel wordCombo = new JLabel("Combo", JLabel.LEFT);
    JLabel showCombo = new JLabel(String.format("%4s", "0"), JLabel.LEFT);
    int bpm;
    int y;
    int distance = 80;
    int deltaY = 10;
    int delay;
    int initY;
    long spf;

    int[] key = new int[]{68, 70, 74, 75, 32}; // D, F, J, K

    ArrayList<ArrayList<Integer>> check;
    int[] checkSize = new int[5];

    int criticalTime = 80;
    int nearTime = 200;

    int total;
    int critical;
    int early;
    int late;
    int miss;
    int combo;
    int idx;
    int comboMax;

    String info;

    public GameControl(Frame fTemp, PanelEnding peTemp, PanelGaming pgTemp, String fumenPath) {

        try {
            f = fTemp;
            pe = peTemp;
            pg = pgTemp;

            check = new ArrayList<>();
            for (int i = 0; i < 5; ++i) {
                check.add(new ArrayList<>());
            }

            total = 0;
            critical = 0;
            early = 0;
            late = 0;
            miss = 0;
            combo = 0;
            comboMax = 0;
            idx = 0;
            y = 0;

            FileReader fr = new FileReader(fumenPath);
            BufferedReader br = new BufferedReader(fr);
            bpm = Integer.parseInt(br.readLine());
            spf = (long) ((1000000 * 15.0 / bpm / (double) (distance / deltaY)) * 1000);

            for (int i = 0; i < 4; ++i) {
                lAE[i] = new JLabel();
                lAE[i].setOpaque(false);
                lAE[i].setBounds(111 * i + 14, 15, 100, 80);
                lAE[i].addKeyListener(this);
                lAE[i].setFocusable(true);
                pCL.add(lAE[i]);
            }

            lCL = new JLabel(cl);
            lCL.setBounds(0, 0, 460, 100);
            pCL.add(lCL);
            pCL.setBounds(410, 600, 460, 100);
            pg.add(pCL);

            try {
                GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
                ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("images/consola.ttf")));
            } catch (Exception ex) {
                System.out.println(ex);
            }
            Font textFont = new Font("Consolas", Font.BOLD, 100);

            wordCombo.setBounds(900, 100, 400, 120);
            wordCombo.setForeground(c.white);
            wordCombo.setFont(textFont);
            pg.add(wordCombo);

            showCombo.setBounds(900, 220, 400, 120);
            showCombo.setForeground(c.white);
            showCombo.setFont(textFont);
            pgTemp.add(showCombo);
            cache = new ArrayList<>();
            int[] bounds= {423 - 422,533 - 422 ,645 - 422, 756 - 422,458 - 422};
            while (br.ready()) {
                String s = br.readLine();
                if (s.charAt(0) != '*') {
                    int a = Integer.parseInt(s);
                    cache.add(a);
                    for(int i = 0 ; i < 5 ; i++) {
                        if(((a>>i)&1) == 1 ){
                            if(i != 4) {
                                note = new JLabel(bt);
                                note.setBounds(bounds[i], y, 100, 40);
                            }else {
                                note = new JLabel(fx);
                                note.setBounds(bounds[i], y, 350, 40);
                            }
                            pFumen.add(note);
                            check.get(i).add(y);
                            total++;
                        }
                    }
                    /*int a = Integer.parseInt(s);
                    if( (a&1) == 1 ){
                        note = new JLabel(bt);
                        note.setBounds(, y, 100, 40);
                        pFumen.add(note);
                        check.get(0).add(y);
                        total++;
                    }*/
                    /*
                    if (s.toCharArray()[0] == '-') {
                        note = new JLabel(bt);
                        note.setBounds(423 - 422, y, 100, 40);
                        pFumen.add(note);
                        check.get(0).add(y);
                        total++;
                    }

                    if (s.toCharArray()[1] == '-') {
                        note = new JLabel(bt);
                        note.setBounds(533 - 422, y, 100, 40);
                        pFumen.add(note);
                        check.get(1).add(y);
                        total++;
                    }

                    if (s.toCharArray()[2] == '-') {
                        note = new JLabel(bt);
                        note.setBounds(645 - 422, y, 100, 40);
                        pFumen.add(note);
                        check.get(2).add(y);
                        total++;
                    }

                    if (s.toCharArray()[3] == '-') {
                        note = new JLabel(bt);
                        note.setBounds(756 - 422, y, 100, 40);
                        pFumen.add(note);
                        check.get(3).add(y);
                        total++;
                    }

                    if (s.toCharArray()[4] == '-') {
                        note = new JLabel(fx);
                        note.setBounds(458 - 422, y, 350, 40);
                        pFumen.add(note);
                        check.get(4).add(y);
                        total++;
                    }
                    */
                    y += distance;
                }
            }

            pFumen.setBounds(422, -y, 860 - 422, y - 125);
            pg.add(pFumen);
            pFumen.setOpaque(false);
            pg.repaint();
            pg.revalidate();

            pg.addKeyListener(this);
            pg.setFocusable(true);
            pg.requestFocusInWindow();

            for (int i = 0; i < 5; ++i) {
                checkSize[i] = check.get(i).size();
            }

            br.close();
            fr.close();
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

    public void setInfo(int song, int difficulty) {
        info = ("" + song + "" + difficulty + "");
    }

    public void setMusic(String filePath) {
        music = new AudioPlayer(filePath);
    }

    public void setBanner(String filePath) {
        lbanner = new JLabel(new ImageIcon(filePath));
        lbanner.setBounds(0, 0, 410, 720);
        pg.add(lbanner);
    }

    public void setDelay(int delay, int initY) {
        this.delay = delay;
        this.initY = initY;
    }

    @Override
    public void run() {
        long startConstruct = System.currentTimeMillis();
        System.out.println("Ready");
        int sizeY = y - distance;
        int[] counter = new int[]{-1, -1, -1, -1, -1};

        while (System.currentTimeMillis() - startConstruct < 2000) {
        }
        System.out.println("Go");

        long startTime = System.nanoTime();
        music.musicPlay();
        while (y > -720 - deltaY * 200) {
            while (System.nanoTime() - startTime < spf) {
            }
            startTime += spf;
            pFumen.setBounds(422, -y - deltaY * initY, 860 - 422, sizeY);
            y -= deltaY;

            for (int i = 0; i < 4; i++) {
                if (checkSize[i] >= 1) {
                    if (check.get(i).get(checkSize[i] - 1) - (y + delay) > nearTime) {
                        synchronized (this) {
                            lAE[i].setIcon(aeR);
                            checkSize[i]--;
                            check.get(i).remove(checkSize[i]);
                            counter[i] = 5;
                            miss++;
                            if (combo > comboMax) {
                                comboMax = combo;
                            }
                            combo = 0;
                            showCombo.setText(String.format("%4s", "0"));
                        }
                    } else if (counter[i] == 0 || checkSize[i] == 0) {
                        synchronized (this) {
                            lAE[i].setIcon(null);
                            counter[i]--;
                        }
                    } else if (counter[i] > 0) {
                        counter[i]--;
                    }
                }
            }
            if (checkSize[4] >= 1) {
                if (check.get(4).get(checkSize[4] - 1) - (y + delay) > nearTime) {
                    synchronized (this) {
                        lAE[1].setIcon(aeR);
                        lAE[2].setIcon(aeR);
                        checkSize[4]--;
                        check.get(4).remove(checkSize[4]);
                        counter[4] = 5;
                        miss++;
                        if (combo > comboMax) {
                            comboMax = combo;
                        }
                        combo = 0;
                        showCombo.setText(String.format("%4s", "0"));
                    }
                } else if (counter[4] == 0 || checkSize[4] == 0) {
                    synchronized (this) {
                        lAE[1].setIcon(null);
                        lAE[2].setIcon(null);
                        counter[4]--;
                    }
                } else if (counter[4] > 0) {
                    counter[4]--;
                }
            }
        }

        if (combo > comboMax) {
            comboMax = combo;
        }

        f.remove(pg);
        f.add(pe);
        pe.setValue(total, critical, early, late, miss, comboMax, info, cache);
        f.repaint();
        f.revalidate();

        pg.removeKeyListener(this);
        pg.setFocusable(false);
    }

    @Override
    public void keyTyped(KeyEvent ke) {

    }

    @Override
    public void keyPressed(KeyEvent ke) {
        for (int i = 0; i < 4; ++i) {
            if (ke.getKeyCode() == key[i]) {
                if (checkSize[i] >= 1) {
                    int deltaT = check.get(i).get(checkSize[i] - 1) - (y + delay);
                    if (Math.abs(deltaT) <= criticalTime) {
                        synchronized (this) {
                            lAE[i].setIcon(aeY);
                            checkSize[i]--;
                            check.get(i).remove(checkSize[i]);
                            critical++;
                            combo++;
                            showCombo.setText(String.format("%4s", combo));
                        }
                    } else if (deltaT > criticalTime && deltaT <= nearTime) {
                        synchronized (this) {
                            lAE[i].setIcon(aeG);
                            checkSize[i]--;
                            check.get(i).remove(checkSize[i]);
                            late++;
                        }
                    } else if (deltaT < -criticalTime && deltaT >= -nearTime) {
                        synchronized (this) {
                            lAE[i].setIcon(aeB);
                            checkSize[i]--;
                            check.get(i).remove(checkSize[i]);
                            early++;
                        }
                    } else {
                        lAE[i].setIcon(aeW);
                    }
                } else {
                    lAE[i].setIcon(aeW);
                }
            }
        }

        if (ke.getKeyCode() == key[4]) {
            if (checkSize[4] >= 1) {
                int deltaT = check.get(4).get(checkSize[4] - 1) - (y + delay);
                if (Math.abs(deltaT) <= criticalTime) {
                    synchronized (this) {
                        lAE[1].setIcon(aeY);
                        lAE[2].setIcon(aeY);
                        checkSize[4]--;
                        check.get(4).remove(checkSize[4]);
                        critical++;
                        combo++;
                        showCombo.setText(String.format("%4s", combo));
                    }
                } else if (deltaT > criticalTime && deltaT <= nearTime) {
                    synchronized (this) {
                        lAE[1].setIcon(aeG);
                        lAE[2].setIcon(aeG);
                        checkSize[4]--;
                        check.get(4).remove(checkSize[4]);
                        late++;
                    }
                } else if (deltaT < -criticalTime && deltaT >= -nearTime) {
                    synchronized (this) {
                        lAE[1].setIcon(aeB);
                        lAE[2].setIcon(aeB);
                        checkSize[4]--;
                        check.get(4).remove(checkSize[4]);
                        early++;
                    }
                } else {
                    lAE[1].setIcon(aeW);
                    lAE[2].setIcon(aeW);
                }
            } else {
                lAE[1].setIcon(aeW);
                lAE[2].setIcon(aeW);
            }
        }
    }

    @Override
    public void keyReleased(KeyEvent ke) {
        for (int i = 0; i < 4; ++i) {
            if (ke.getKeyCode() == key[i]) {
                lAE[i].setIcon(null);
            }
        }

        if (ke.getKeyCode() == key[4]) {
            lAE[1].setIcon(null);
            lAE[2].setIcon(null);
        }
    }
}
