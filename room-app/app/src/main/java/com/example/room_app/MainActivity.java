package com.example.room_app;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.Switch;

public class MainActivity extends AppCompatActivity {
    private Switch ledSwitch;
    private SeekBar servoBar;

    public static final int REQUEST_ENABLE_BT=1;
    ListView lv_paired_devices;
    Set<BluetoothDevice> set_pairedDevices;
    ArrayAdapter adapter_paired_devices;
    BluetoothAdapter bluetoothAdapter;
    public static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    public static final int MESSAGE_READ=0;
    public static final int MESSAGE_WRITE=1;
    public static final int CONNECTING=2;
    public static final int CONNECTED=3;
    public static final int NO_SOCKET_FOUND=4;


    String bluetooth_message="00";


    @SuppressLint("HandlerLeak")
    Handler mHandler=new Handler()
    {
        @Override
        public void handleMessage(Message msg_type) {
            super.handleMessage(msg_type);

            switch (msg_type.what){
                case MESSAGE_READ:

                    byte[] readbuf=(byte[])msg_type.obj;
                    String string_recieved=new String(readbuf);

                    //do some task based on recieved string

                    break;
                case MESSAGE_WRITE:

                    if(msg_type.obj!=null){
                        ConnectedThread connectedThread=new ConnectedThread((BluetoothSocket)msg_type.obj);
                        connectedThread.write(bluetooth_message.getBytes());

                    }
                    break;

                case CONNECTED:
                    Toast.makeText(getApplicationContext(),"Connected",Toast.LENGTH_SHORT).show();
                    break;

                case CONNECTING:
                    Toast.makeText(getApplicationContext(),"Connecting...",Toast.LENGTH_SHORT).show();
                    break;

                case NO_SOCKET_FOUND:
                    Toast.makeText(getApplicationContext(),"No socket found",Toast.LENGTH_SHORT).show();
                    break;
            }
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.ledSwitch = findViewById(R.id.ledSwitch);
        this.servoBar = findViewById(R.id.servoBar);
        this.BA = BluetoothAdapter.getDefaultAdapter();
    }
    @Override
    protected void onStart() {
        super.onStart();
        this.ledSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                // do something, the isChecked will be
                // true if the switch is in the On position
            }
        });
        this.servoBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,boolean fromUser) {
                // TODO Auto-generated method stub
            }
        });
    }

}