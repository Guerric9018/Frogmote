from websocket import WebSocketApp
import time
import json
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

STANDBY, WAITING, GESTURING, END = range(4)
state = STANDBY

last_time = None
last_value = [0, 0, 0]
no_rotation_periods = 0
rotation_periods = 0

N_VALUES = 128

action_delay = 0.1
action_timeout = 2
peak_threshold = 5
release_length = 1
in_peak = False

tick = 0

def on_message(ws, message):
    global state, tick, last_time, in_peak, release_length, last_value, no_rotation_periods, rotation_periods

    peak_detected = False

    current_time = time.time()
    if last_time is None:
        period = 0.001
    else:
        period = max(0.001, current_time - last_time)
    last_time = current_time

    data = json.loads(message)
    new_value = data['values']

    detection = math.sqrt((new_value[0] - last_value[0]) ** 2 + (new_value[1] - last_value[1]) ** 2 + (new_value[2] - last_value[2]) ** 2)

    if state == STANDBY:
        if detection > 0.002 / period:
            rotation_periods += 1
        else:
            rotation_periods = 0
        if rotation_periods == 2:
            print("Detected")
            state = GESTURING
            rotation_periods = 0
    if state == GESTURING:
        if detection < 0.01 / period:
            no_rotation_periods += 1
        else:
            no_rotation_periods = 0
        if no_rotation_periods == 10:
            print("Done")
            state = STANDBY
            no_rotation_periods = 0


    last_value = new_value

    if False:
        if state == STANDBY:
            print("Gesture started")
            state = WAITING
            tick = 0
            acceleration_values = []
            # Reset integration values at gesture start.
            velocity = [0.0, 0.0, 0.0]
            position = [0.0, 0.0, 0.0]
            trajectory.clear()
        elif state == GESTURING:
            print("Gesture Ending")
            tick = 0
            state = END
            acceleration_values = []

    if state == WAITING:
        tick += period
        state = GESTURING
        tick = 0
    elif state == END:
        tick += period
        if tick > 5 * action_delay:
            print("Gesture Done")
            # Plot the trajectory of the controller.
            plot_trajectory(trajectory)
            state = STANDBY
            tick = 0
            # Optionally reset integration values after plotting.
            velocity = [0.0, 0.0, 0.0]
            position = [0.0, 0.0, 0.0]
            trajectory.clear()
    elif state == GESTURING and tick > action_timeout:
        print("Gesture rejected")
        state = STANDBY
        tick = 0

def on_error(ws, error):
    print("error occurred ", error)
    
def on_close(ws, close_code, reason):
    print("connection closed : ", reason)
    
def on_open(ws):
    print("connected")
    
def connect(url):
    ws = WebSocketApp(url,
                      on_open=on_open,
                      on_message=on_message,
                      on_error=on_error,
                      on_close=on_close)
    ws.run_forever()
 
connect("ws://137.194.156.142:8081/sensor/connect?type=android.sensor.orientation")
