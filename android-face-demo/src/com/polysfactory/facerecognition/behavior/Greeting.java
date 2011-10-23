package com.polysfactory.facerecognition.behavior;

import android.util.Log;

import com.polysfactory.facerecognition.App;

/**
 * あいさつの振る舞い<br>
 * @author $Author$
 * @version $Revision$
 */
public class Greeting extends Behavior {

    @Override
    public void execute() {
        Log.d(App.TAG, "Greeting::action");
        mUsbCommander.lightLed(0, 0, 3);
        sleep(100);
        mUsbCommander.rotateRightHand(50);
        sleep(300);
        mUsbCommander.lightLed(0, 3, 0);
        sleep(100);
        mUsbCommander.rotateRightHand(32);
        sleep(300);
        mUsbCommander.lightLed(0, 0, 0);
    }

}