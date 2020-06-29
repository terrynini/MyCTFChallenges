package Control;

import java.io.File;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;

public class AudioPlayer {

    // The music to play.
    File music;
    Clip clip;

    public AudioPlayer(String filePath) {
        music = new File(filePath);
    }

    public void musicPlay() {
        try {
            clip = AudioSystem.getClip();
            clip.open(AudioSystem.getAudioInputStream(music));
            clip.start();
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

    public void musicStop() {
        clip.stop();
    }

    public void musicLoop() {
        try {
            clip = AudioSystem.getClip();
            clip.open(AudioSystem.getAudioInputStream(music));
            clip.loop(Clip.LOOP_CONTINUOUSLY);
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }
}
