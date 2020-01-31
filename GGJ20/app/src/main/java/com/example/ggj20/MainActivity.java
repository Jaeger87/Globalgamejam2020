package com.example.ggj20;

import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.TextView;

import com.example.ggj20.utilities.Constants;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Click;
import org.androidannotations.annotations.EActivity;
import org.androidannotations.annotations.ViewById;

import java.io.File;
import java.io.IOException;
import java.util.Set;

@EActivity(R.layout.activity_main)
public class MainActivity extends AppCompatActivity {


    @ViewById(R.id.nowplay)
    TextView nowPlayText;

    private MediaPlayer player = null;
    private MediaPlayer soundPlayer = null;

    private static final String TAG = "MainGGJ20";

    //From Renato
    private BluetoothConnectionService mBluetoothConnectionHead;
    private BluetoothAdapter mBluetoothAdapter;
    private BluetoothDevice mBTDeviceBox;




    BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String text = intent.getStringExtra("Message");

            if(text.contains("ALI"))
                return;

        }
    };


    @AfterViews
    void AfterViews() {

        LocalBroadcastManager.getInstance(this).registerReceiver(mReceiver, new IntentFilter((Constants.incomingMessageIntent)));
        connectionBluetooth();
    }


    private void connectionBluetooth()
    {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        for(BluetoothDevice bt : pairedDevices)
        {
            Log.d(TAG, bt.getAddress());

            if (bt.getAddress().equals(Constants.macBoxBT)) {
                Log.d(TAG, bt.getName());

                mBTDeviceBox = bt;
                mBluetoothConnectionHead = new BluetoothConnectionService(MainActivity.this, Constants.HeadID);
                startBTConnection(mBTDeviceBox, mBluetoothConnectionHead);
            }

        }
    }

    public void startBTConnection(BluetoothDevice device, BluetoothConnectionService connection)
    {
        connection.startClient(device);
    }


    // Create a BroadcastReceiver for ACTION_FOUND
    private final BroadcastReceiver mBroadcastReceiver1 = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            // When discovery finds a device
            if (action.equals(mBluetoothAdapter.ACTION_STATE_CHANGED)) {
                final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE, mBluetoothAdapter.ERROR);

                switch(state){
                    case BluetoothAdapter.STATE_OFF:
                        Log.d(TAG, "onReceive: STATE OFF");
                        break;
                    case BluetoothAdapter.STATE_TURNING_OFF:
                        Log.d(TAG, "mBroadcastReceiver1: STATE TURNING OFF");
                        break;
                    case BluetoothAdapter.STATE_ON:
                        Log.d(TAG, "mBroadcastReceiver1: STATE ON");
                        break;
                    case BluetoothAdapter.STATE_TURNING_ON:
                        Log.d(TAG, "mBroadcastReceiver1: STATE TURNING ON");
                        break;
                }
            }
        }
    };


    @Click({R.id.button})
    void bismarkGianni() {
        nowPlayText.setText("Bismark");
        try {
            AssetFileDescriptor afd = getAssets().openFd("Gianni Bismark, Franco126 Università (320).mp3");
            startPlaying(afd);
        }
        catch (Exception e)
        {
            Log.d(TAG, e.getMessage());
        }
    }


    @Click({R.id.button2})
    void playThunder() {
        nowPlayText.setText("Thunder");
        try {
            AssetFileDescriptor afd = getAssets().openFd("thunder.wav");
            startSound(afd);
        }
        catch (Exception e)
        {
            Log.d(TAG, e.getMessage());
        }
    }

    private void startPlaying(AssetFileDescriptor afd) {

        if(player == null) {
            player = new MediaPlayer();
            try {
                player.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(),afd.getLength());
                player.prepare();


                player.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                    @Override
                    public void onCompletion(MediaPlayer mp) {


                        // stop streaming vocal note
                        if (player != null) {
                            stopPlaying();
                        }
                    }
                });

            } catch (IOException e) {
                Log.e(TAG, "prepare() failed");
            }
        }

        player.start();
    }

    public void stopPlaying() {
        if(player != null) {
            player.stop();
            player.release();
            player = null;
        }
    }


    private void startSound(AssetFileDescriptor afd) {

        if(soundPlayer == null) {
            soundPlayer = new MediaPlayer();
            try {
                soundPlayer.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(),afd.getLength());
                soundPlayer.prepare();


                soundPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                    @Override
                    public void onCompletion(MediaPlayer mp) {


                        // stop streaming vocal note
                        if (soundPlayer != null) {
                            stopSound();
                        }
                    }
                });

            } catch (IOException e) {
                Log.e(TAG, "prepare() failed");
            }
        }

        soundPlayer.start();
    }

    public void stopSound() {
        if(soundPlayer != null) {
            soundPlayer.stop();
            soundPlayer.release();
            soundPlayer = null;
        }
    }
}