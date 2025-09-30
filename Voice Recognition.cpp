#include <iostream>
#include <string>

using namespace std;

class voicePrint{
    public:
        string audio;
        double pitch;
        double volume;
        double tone;
        bool IsVoice(){
            int count = 0;

            if(audio == "Hello") count++;
            if(pitch <= 120.0 && pitch >= 115.5) count++;
            if(volume <= 80.0 && volume >= 76.7) count++;
            if(tone <= 25.8 && tone >= 23.5) count++;

            return (count == 4);
        }
};

int main(){
    voicePrint prototype;

    cout << "Enter The Word (Hello): ";
    cin >> prototype.audio;
    cout << "Enter The Pitch: ";
    cin >> prototype.pitch;
    cout << "Enter The Volume: ";
    cin >> prototype.volume;
    cout << "Enter The Tone: ";
    cin >> prototype.tone;
    cout << endl;

    if(prototype.IsVoice()){
        cout << "Hello, Jomoo" << endl;
    }
    else{
        cout << "Voice Not Recognized." << endl;
    }
    return 0;
}
