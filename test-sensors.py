from websocket import WebSocketApp
import time
import json
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

STANDBY, WAITING, GESTURING, END = range(4)
state = STANDBY

last_time = None

N_VALUES = 128
acceleration_values = []

velocity = [0.0, 0.0, 0.0]
position = [0.0, 0.0, 0.0]
trajectory = []   

action_delay = 0.1
action_timeout = 2
peak_threshold = 5
release_length = 1
in_peak = False

tick = 0

def plot_trajectory(trajectory):
    """Plot the 3D trajectory of the controller with equal axis scale."""
    if not trajectory:
        print("No trajectory data to plot.")
        return

    xs = [pos[0] for pos in trajectory]
    ys = [pos[1] for pos in trajectory]
    zs = [pos[2] for pos in trajectory]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(xs, ys, zs, marker='o')
    ax.set_title("Controller Trajectory")
    ax.set_xlabel("X Position")
    ax.set_ylabel("Y Position")
    ax.set_zlabel("Z Position")

    # Ensure all axes have the same scale
    min_val = min(min(xs), min(ys), min(zs))
    max_val = max(max(xs), max(ys), max(zs))
    ax.set_xlim([min_val, max_val])
    ax.set_ylim([min_val, max_val])
    ax.set_zlim([min_val, max_val])

    plt.show()


def on_message(ws, message):
    global state, tick, last_time, acceleration_values, in_peak, release_length
    global velocity, position, trajectory

    peak_detected = False

    current_time = time.time()
    if last_time is None:
        period = 0.01  # Small default period to avoid zero division.
    else:
        period = current_time - last_time
    last_time = current_time

    # Only count time ticks when in an active gesture.
    if state in (WAITING, GESTURING):
        tick += period

    data = json.loads(message)
    values = data['values']
    x = values[0]
    y = values[1]
    z = values[2]
    length = math.sqrt(x*x + y*y + z*z)

    # Peak detection to trigger state changes.
    if length > peak_threshold:
        if not in_peak:
            in_peak = True
    else:
        if in_peak:
            if release_length == 0:
                peak_detected = True
                release_length = 1
                in_peak = False
            else:
                release_length -= 1

    if len(acceleration_values) > N_VALUES:
        acceleration_values = []
    acceleration_values.append(length)

    # Update integration only when a gesture is in progress.
    if state in (WAITING, GESTURING):
        # Simple Euler integration for velocity and position.
        velocity[0] += x * period
        velocity[1] += y * period
        velocity[2] += z * period

        position[0] += velocity[0] * period
        position[1] += velocity[1] * period
        position[2] += velocity[2] * period

        # Append a copy of the current position.
        trajectory.append(position.copy())

    if peak_detected:
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
 
connect("ws://137.194.156.142:8080/sensor/connect?type=android.sensor.orientation")
