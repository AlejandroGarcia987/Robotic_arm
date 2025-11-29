import socket

# --- config ---
UDP_IP = "xxx.xxx.x.xx" # <--- Add your NodeMCU IP
UDP_PORT = xxxx # <--- Add your NodeMCU UDP PORT
# ---------------------

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"--- UDP Control for ({UDP_IP}) Robotic arm ---")
print("Write an angle between (0-180) and press enter.")
print("write 'q' for exit.")

while True:
    user_input = input("Servo (id,angle) > ")
    
    if user_input.lower() == 'q':
        break
        
    try:
        parts = [p.strip() for p in user_input.split(',')]
        if len(parts) != 2:
            print("   [ERROR] Use format: id,angle (e.g. 2,120)")
            continue
        servo_id = int(parts[0])
        angle = int(parts[1])
        if not (1<= servo_id <=5):
            print("   [ERROR] id must be between 1 and 5")
            continue
        if not (0 <= angle <= 180):
            print("   [ERROR] Angle must be between 0 and 180")
            continue
        
        packet = bytes([servo_id, angle])
        sock.sendto(packet, (UDP_IP, UDP_PORT))
        print(f"   [TX] Sent: ID={servo_id} Angle={angle}")
    except ValueError:
        print("   [ERROR] Please, enter an int value.")

sock.close()