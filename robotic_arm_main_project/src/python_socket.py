import socket

# --- config ---
UDP_IP = "xxx.xxx.x.xx" # <--- Add your NodeMCU IP
UDP_PORT = XXXX # <--- Add your NodeMCU UDP PORT
# ---------------------

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"--- UDP Control for ({UDP_IP}) Robotic arm ---")
print("Write an angle between (0-180) and press enter.")
print("write 'q' for exit.")

while True:
    user_input = input("Servo 1 angle > ")
    
    if user_input.lower() == 'q':
        break
        
    try:
        angle = int(user_input)
        if 0 <= angle <= 180:
            # Protocol: [ID_SERVO, ANGLE]
            # ID Servo 1 = 0x01. THis will be updatred with more servos
            packet = bytes([0x01, angle])
            
            sock.sendto(packet, (UDP_IP, UDP_PORT))
            print(f"   [TX] Sent: ID=1 Angle={angle}")
        else:
            print("   [ERROR] Angle must be between 0 and 180")
            
    except ValueError:
        print("   [ERROR] Please, enter an int value.")

sock.close()