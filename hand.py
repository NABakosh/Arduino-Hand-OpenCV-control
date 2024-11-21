import cv2
import mediapipe as mp
import serial

camera = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils

portNo = "COM3"
uart = serial.Serial(portNo, 9600)

p = [0 for i in range(21)]
finger = [0 for i in range(10)]

def distance(point1, point2):
    return abs(point1 - point2)

while True:
    good, img = camera.read()
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

    results = hands.process(imgRGB)
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS)

            for id, point in enumerate(handLms.landmark):
                width, height, color = img.shape
                width, height = int(point.x * height), int(point.y * width)
                p[id] = height

                if id == 8:
                    cv2.circle(img, (width, height), 5, (255, 0, 255), cv2.FILLED)
                if id == 12:
                    cv2.circle(img, (width, height), 5, (0, 0, 255), cv2.FILLED)
                if id == 16:
                    cv2.circle(img, (width, height), 5, (192, 192, 192), cv2.FILLED)
                if id == 4:
                    cv2.circle(img, (width, height), 5, (192, 1, 0), cv2.FILLED)
                if id == 20:
                    cv2.circle(img, (width, height), 5, (0, 255, 0), cv2.FILLED)
                if id == 4:
                    cv2.circle(img, (width, height), 5, (0, 0, 0), cv2.FILLED)
                if id == 17:
                    cv2.circle(img, (width, height), 5, (0, 0, 0), cv2.FILLED)

            distanceGood = distance(p[0], p[5]) + (distance(p[0], p[5]) / 2)
            finger[1] = 1 if distance(p[0], p[8]) > distanceGood else 0
            finger[2] = 1 if distance(p[0], p[12]) > distanceGood else 0
            finger[3] = 1 if distance(p[0], p[16]) > distanceGood else 0
            finger[4] = 1 if distance(p[0], p[20]) > distanceGood else 0
            finger[0] = 1 if distance(p[4], p[17]) > distanceGood else 0

            msg = [0, 0, 0, 0, 0]
            for i in range(0, 5):
                if finger[i]:  # Проверка на значение в списке finger[i]
                    msg[i] = 1
            if msg != [0,0,0,0,0]:
                message = ','.join(map(str, msg))  # Преобразуем массив в строку "1,0,1,1,0"
                portNo.write((message + '\n').encode())
    cv2.imshow("Image", img)
    if cv2.waitKey(1) == ord('q'):
        break

camera.release()
cv2.destroyAllWindows()
