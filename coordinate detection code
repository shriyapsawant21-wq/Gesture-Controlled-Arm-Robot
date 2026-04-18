import cv2
import mediapipe as mp
import time

# Initialize MediaPipe
mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

last_print_time = 0  # To control print frequency

with mp_hands.Hands(
        max_num_hands=1,
        min_detection_confidence=0.7,
        min_tracking_confidence=0.7) as hands:

    while True:
        success, img = cap.read()
        if not success:
            break

        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        results = hands.process(imgRGB)

        if results.multi_hand_landmarks:
            for handLms in results.multi_hand_landmarks:

                h, w, c = img.shape

                # Index finger tip (landmark 8)
                lm = handLms.landmark[8]

                cx = int(lm.x * w)
                cy = int(lm.y * h)
                z_value = lm.z

                # Draw circle at fingertip
                cv2.circle(img, (cx, cy), 10, (0, 255, 0), cv2.FILLED)

                # Display X, Y, Z on screen
                cv2.putText(img, f"X: {cx}", (10, 50),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

                cv2.putText(img, f"Y: {cy}", (10, 90),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

                cv2.putText(img, f"Z: {format(z_value, '.6f')}", (10, 130),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

                # Print Z once per second
                current_time = time.time()
                if current_time - last_print_time > 1:
                    print("Z value:", format(z_value, ".6f"))
                    last_print_time = current_time

                # Draw hand landmarks
                mp_draw.draw_landmarks(
                    img, handLms, mp_hands.HAND_CONNECTIONS)

        cv2.imshow("Hand Position Detection", img)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()