package Control;

import Visual.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;

public class Frame extends JFrame implements ActionListener {

    PanelMenu pMenu = new PanelMenu();
    PanelHelp pHelp = new PanelHelp();
    PanelHell pHell = new PanelHell();
    PanelHighScore pHighScore = new PanelHighScore();
    PanelGaming pGaming;
    PanelEnding pEnding = new PanelEnding();
    GameControl gc;

    AudioPlayer apImSoHappy = new AudioPlayer("songs/I'm so Happy/I'm so Happy.wav");
    AudioPlayer apGekkou = new AudioPlayer("songs/gekkou/gekkou.wav");
    AudioPlayer titleBGM = new AudioPlayer("songs/titleBGM.wav");

    boolean trialL = false;
    boolean trialR = false;

    public Frame(String s) {
        super(s);

        pMenu.btnStart.addActionListener(this);
        pMenu.btnHighScore.addActionListener(this);
        pMenu.btnHelp.addActionListener(this);
        pMenu.btnExit.addActionListener(this);
        add(pMenu);

        pHelp.btnBack.addActionListener(this);
        pHelp.btnHell.addActionListener(this);

        pHighScore.btnBack.addActionListener(this);

        pHell.btnBack.addActionListener(this);
        pHell.btnHell.addActionListener(this);

        pEnding.btnBack.addActionListener(this);
        titleBGM.musicPlay();
    }

    @Override
    public void actionPerformed(ActionEvent ae) {
        // Menu buttons
        if (ae.getSource() == pMenu.btnStart) {
            if (titleBGM.clip != null && titleBGM.clip.isRunning()) {
                titleBGM.musicStop();
            }
            remove(pMenu);
            add(pHell);
            repaint();
            revalidate();
        } else if (ae.getSource() == pMenu.btnHighScore) {
            remove(pMenu);
            add(pHighScore);
            try {
                pHighScore.readRecord();
            } catch (Exception ex) {
                System.out.println(ex);
            }
            repaint();
            revalidate();
        } else if (ae.getSource() == pMenu.btnHelp) {
            remove(pMenu);
            add(pHelp);
            repaint();
            revalidate();
        } else if (ae.getSource() == pMenu.btnExit) {
            if (titleBGM.clip != null && titleBGM.clip.isRunning()) {
                titleBGM.musicStop();
            }
            dispose();
        }

        // Help button
        if (ae.getSource() == pHelp.btnBack) {
            remove(pHelp);
            add(pMenu);
            repaint();
            revalidate();
        } else if (ae.getSource() == pHelp.btnHell) {
            if (titleBGM.clip != null && titleBGM.clip.isRunning()) {
                titleBGM.musicStop();
            }
            remove(pHelp);
            add(pHell);
            try {
                pHell.readRecord();
            } catch (Exception ex) {
                System.out.println(ex);
            }
            repaint();
            revalidate();
        }

        // Hell button
        if (ae.getSource() == pHell.btnBack) {
            remove(pHell);
            add(pMenu);
            titleBGM.musicPlay();
            repaint();
            revalidate();
        } else if (ae.getSource() == pHell.btnHell) {
            pGaming = new PanelGaming();
            remove(pHell);
            add(pGaming);
            repaint();
            revalidate();

            gc = new GameControl(this, pEnding, pGaming, "songs/gekkou/hell.txt");
            gc.setInfo(1, 2);
            gc.setMusic("songs/gekkou/gekkou_hell.wav");
            gc.setBanner("songs/gekkou/banner.png");
            gc.setDelay(560, -5);
            gc.start();
        }

        // HighScore buttons
        if (ae.getSource() == pHighScore.btnBack) {
            remove(pHighScore);
            add(pMenu);
            repaint();
            revalidate();
        }

        // Ending Button
        if (ae.getSource() == pEnding.btnBack) {
            remove(pEnding);
            pEnding.close();
            add(pHell);
            repaint();
            revalidate();
        }
    }
}
