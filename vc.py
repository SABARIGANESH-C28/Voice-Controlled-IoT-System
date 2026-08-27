import speech_recognition as sr
import requests

# ESP32 server IP (replace with your ESP32 IP shown in Serial Monitor)
ESP32_IP = "http://192.168.1.50"  

def send_command(command):
    try:
        url = f"{ESP32_IP}/{command}"
        response = requests.get(url)
        print("ESP32 Response:", response.text)
    except Exception as e:
        print("Error sending command:", e)

def listen_and_control():
    recognizer = sr.Recognizer()
    mic = sr.Microphone()

    print("Listening... Say 'turn on' or 'turn off'")
    while True:
        with mic as source:
            recognizer.adjust_for_ambient_noise(source)
            audio = recognizer.listen(source)

        try:
            text = recognizer.recognize_google(audio).lower()
            print("You said:", text)

            if "turn on" in text or "light on" in text:
                send_command("on")
            elif "turn off" in text or "light off" in text:
                send_command("off")
            else:
                print("Command not recognized.")
        except sr.UnknownValueError:
            print("Could not understand audio.")
        except sr.RequestError as e:
            print("Speech recognition error:", e)

if __name__ == "__main__":
    listen_and_control()
