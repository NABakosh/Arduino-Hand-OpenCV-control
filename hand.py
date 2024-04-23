import cv2
import mediapipe as mp
import serial

camera = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils

portNo = "COM3"

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
                print(handLms.landmark)
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

            msg = ''
            #закрыть
            if not (finger[0]) and not finger[1] and not finger[2] and not (finger[3]) and not (finger[4]):
                msg = '@' + str(width) + ';'
            #только указательный
            if not (finger[0]) and  finger[1] and not finger[2] and not(finger[3]) and not(finger[4]):
                msg = '!' + str(width) + ';'
            #указательный с средний
            if not (finger[0]) and  finger[1] and  finger[2] and not(finger[3]) and not(finger[4]):
                msg = '#' + str(width) + ';'
            #указательный, средний и безьимянный
            if not (finger[0]) and  finger[1] and  finger[2] and (finger[3]) and not(finger[4]):
                msg = '%' + str(width) + ';'
            #указатьельный,средний,безьимянный,мезинец
            if not (finger[0]) and  finger[1] and  finger[2] and (finger[3]) and (finger[4]):
                msg = ':' + str(width) + ';'
            #указательный с безьимяным и мезинцем
            if not (finger[0]) and  finger[1] and  not finger[2] and (finger[3]) and (finger[4]):
                msg = '?' + str(width) + ';'
            #указательный средним с мезинцем
            if not (finger[0]) and  finger[1] and  finger[2] and not(finger[3]) and (finger[4]):
                msg = '*' + str(width) + ';'
            #koza
            if not (finger[0]) and  finger[1] and  not finger[2] and not(finger[3]) and (finger[4]):
                msg = '(' + str(width) + ';'
            #указательный с безьимянным
            if not (finger[0]) and  finger[1] and  not finger[2] and (finger[3]) and not (finger[4]):
                msg = ')' + str(width) + ';'
            #средний
            if not (finger[0]) and  not finger[1] and  finger[2] and not(finger[3]) and not(finger[4]):
                msg = 'q' + str(width) + ';'
            #средний с безьимянный
            if not (finger[0]) and not finger[1] and  finger[2] and (finger[3]) and not(finger[4]):
                msg = 'w' + str(width) + ';'
            #средний с мезинцем
            if not (finger[0]) and not finger[1] and  finger[2] and not(finger[3]) and (finger[4]):
                msg = 'e' + str(width) + ';'
            #средний с безьимянный с мезинцем
            if not (finger[0]) and not finger[1] and  finger[2] and (finger[3]) and (finger[4]):
                msg = 'r' + str(width) + ';'
            #безьяимянный
            if not (finger[0]) and not finger[1] and not finger[2] and (finger[3]) and not(finger[4]):
                msg = 't' + str(width) + ';'
            #безьимянный с мезинцем
            if not (finger[0]) and not finger[1] and not finger[2] and (finger[3]) and (finger[4]):
                msg = 'y' + str(width) + ';'
            #мезинец
            if not (finger[0]) and not finger[1] and not finger[2] and not(finger[3]) and (finger[4]):
                msg = 'u' + str(width) + ';'



            if msg != '':
                msg = bytes(str(msg), 'utf-8')
                print(msg)

    cv2.imshow("Image", img)
    if cv2.waitKey(1) == ord('q'):
        break

camera.release()
cv2.destroyAllWindows()
