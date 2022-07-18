package com.example.fan_project;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;

public class manual extends AppCompatActivity {

   MainActivity.ConnectedBluetoothThread mmThreadConnectedBluetooth;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_manual);

        Button stop = (Button) findViewById(R.id.stop);
        Button low = (Button) findViewById(R.id.low);
        Button middle = (Button) findViewById(R.id.middle);
        Button high = (Button) findViewById(R.id.high);
        Button manual_turn_start = (Button) findViewById(R.id.manual_turn_start);
        Button manual_turn_stop = (Button) findViewById(R.id.manual_turn_stop);




        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mmThreadConnectedBluetooth != null) {
                    if(mmThreadConnectedBluetooth != null) {

                        synchronized (this) {
                            mmThreadConnectedBluetooth.write("9");
                        }

                    }
                }
            }
        });

        low.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mmThreadConnectedBluetooth != null) {
                    synchronized (this) {
                        mmThreadConnectedBluetooth.write("6");
                    }
                }
            }
        });

        middle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mmThreadConnectedBluetooth != null) {
                    synchronized (this) {
                        mmThreadConnectedBluetooth.write("7");
                    }
                }

            }
        });

        high.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mmThreadConnectedBluetooth != null) {
                    synchronized (this) {
                        mmThreadConnectedBluetooth.write("8");
                    }
                }
            }
        });

        manual_turn_start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mmThreadConnectedBluetooth != null) {
                    synchronized (this) {
                        mmThreadConnectedBluetooth.write("3");
                    }
                }
            }
        });

        manual_turn_stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mmThreadConnectedBluetooth != null) {
                    synchronized (this) {
                        mmThreadConnectedBluetooth.write("4");
                    }
                }
            }
        });

    }

}