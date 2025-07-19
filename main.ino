#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
 
// Define RX and TX pins for DFPlayer Mini
SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
 
// Button pins
const int button1 = 1; // Play track 1
const int nextButton = 2; // Next track
const int volUpButton = 6; // Volume Up
const int volDownButton = 7; // Volume Down
const int restartButton = 4; // Restart Song
const int tempoIncButton = 12; // Increase tempo
const int tempoDecButton = 13; // Decrease tempo

// Function Prototypes for each Song
void LetItBe();
void ComeOnLetsGo();
void LaBamba();

// Function Pointer Array
void (*songList[])() = { LetItBe, ComeOnLetsGo, LaBamba };

// Global Variables
const int numSongs = sizeof(songList) / sizeof(songList[0]);
int currentSongIndex = 0;
int volume = 30;
int tempo = 1000;
int tempoStep = 50;
static long currentTempo = 0;
const int maxTempo = 300;  // Smaller delay = faster tempo
const int minTempo = 2000; // Bigger delay = slower tempo
volatile bool restartSong = false;

// FILES
int C = 1;
int G = 3;
int Am = 5;
int F = 7;
int A = 9;
int D = 11;
int E = 13;
int blank = 15;
int songRestarting = 17;
int down = 19;
int up = 21;
int one = 23;
int two = 25;
int three = 27;
int now_playing = 29;
int let_it_be = 31;
int la_bamba = 33;
int come_on_lets_go = 35;
int strumming = 37;

// Main helper function
void playNoteAndCheck(int track) {
  // Play track
  myDFPlayer.play(track);
  delay(50);

  // Constantly scan for input
  unsigned long startTime = millis();
  while (millis() - startTime < tempo) {
    handleTempo();
    handleVolume();
    handleRestart();
    handleNextSong();
    if (restartSong) {
      return; // Exit function early to restart song
    }
  }
}

// Tempo helper function
void handleTempo() {
  static long lastTempoChange = 0;
  const unsigned long tempoDebounce = 200;
  if (millis() - lastTempoChange > tempoDebounce) {
    if ((digitalRead(tempoIncButton) == LOW) && tempo > maxTempo) {
      tempo -= tempoStep;
      lastTempoChange = millis();
      Serial.println("Tempo Increased (Delay Lowered) " + String(tempo));
    }

    if ((digitalRead(tempoDecButton) == LOW) && tempo < minTempo) {
      tempo += tempoStep;
      lastTempoChange = millis();
      Serial.println("Tempo Decreased (Delay Increased) " + String(tempo));
    }
  }
}

// Volume helper function
void handleVolume() {
  static long lastVolumeChange = 0;
  const unsigned long VolumeDebounce = 200;
  if (millis() - lastVolumeChange > VolumeDebounce) {
    if ((digitalRead(volUpButton) == LOW) && volume < 30) {
      volume++;
      myDFPlayer.volume(volume);
      lastVolumeChange = millis();
      Serial.println("Volume Increased: " + String(volume));
    }

    if ((digitalRead(volDownButton) == LOW) && volume > 0) {
      volume--;
      myDFPlayer.volume(volume);
      lastVolumeChange = millis();
      Serial.println("Volume Decreased: " + String(volume));
    }
  }
}

// Restart helper function
void handleRestart() {
  static long lastRestart = 0;
  const unsigned long restartDebounce = 200;
  if (millis() - lastRestart > restartDebounce) {
    if (digitalRead(restartButton) == LOW) {
      restartSong = true;
      lastRestart = millis();
    }
  }
}

// Next song helper function (if user gets trigger happy)
void handleNextSong() {
  static long lastSongChange = 0;
  const unsigned long songChangeDebounce = 200;
  if (millis() - lastSongChange > songChangeDebounce) {
    if (digitalRead(nextButton) == LOW) {
      currentSongIndex = (currentSongIndex + 1) % numSongs;
      Serial.println("Successful song change");
      Serial.println(currentSongIndex);
      lastSongChange = millis();
      songList[currentSongIndex]();
    }
  }
}

// SONGS
 
// NOTE: THE FUNCTIONS INCREMENT BY 2
// 0001 = 1, 0002 = 3, 0003, = 5, etc
void LetItBe() {
  tempo = 1644;
  restartSong = false;
  
  int letItBe[] = {now_playing, let_it_be, strumming, blank};

  for(int i = 0; i < 4; i++) {
    playNoteAndCheck(letItBe[i]);
    if(restartSong) return;
  }


  tempo = 822; // Adjusted for strumming pattern demo
  // Demonstrate strumming pattern
  Serial.println("Let It Be Strumming Pattern:");
  Serial.println("Down Down Up Up Down Up");
  
  int letItBeStrumming[] = {down, down, down, down, down, down, down, down};
  for(int i = 0; i < 8; i++) {
    playNoteAndCheck(letItBeStrumming[i]);
    if(restartSong) return;
  }
  
  tempo = 1644; // Reset to song tempo
  int letItBeNotes[] = {blank, C, G, Am, F, C, G, F, C, C, G, Am, F, C, G, F, C, Am, G, F, C, C, G, F, C, C, G, Am, F, C, G, F, C, C, G, Am, F, C, G, F, C, Am, G, F, C, C, G, F, C, Am, G, F, C, C, G, F, C, C, G, Am, F, C, G, F, C, C, G, Am, F, C, G, F, C, Am, G, F, C, C, G, F, C, Am, G, F, C, C, G, F, C};
  int num_notes = (sizeof(letItBeNotes) / sizeof(letItBeNotes[0]));
  for (int i = 0; i < num_notes; i++) {
    playNoteAndCheck(letItBeNotes[i]);
    if (restartSong) {
      return;
    }
  }
}

void ComeOnLetsGo() {
  tempo = 1644;
  restartSong = false;
  
  int comeOnLetsGo[] = {now_playing, come_on_lets_go, strumming, blank};

  for(int i = 0; i < 4; i++) {
    playNoteAndCheck(comeOnLetsGo[i]);
    if(restartSong) return;
  }

  tempo = 350;
  
  // Demonstrate strumming pattern
  Serial.println("Come On Let's Go Strumming Pattern:");
  Serial.println("Down Up Down Up");
  
  int comeOnStrumming[] = {down, up, down, up, down, up, down, up, down, up, down, up, down, up, down, up};
  for(int i = 0; i < 16; i++) {
    playNoteAndCheck(comeOnStrumming[i]);
    if(restartSong) return;
  }
  
  tempo = 1000; // Reset to song tempo
  int ComeOnLetsGoNotes[] = {blank, blank, A, blank, D, E, A, blank, D, E, A, blank, D, E, A, blank, blank, blank, A, blank, D, E, A, blank, D, E, A, blank, D, E, A, blank, D, E, A, blank, D, E, A, blank, D, E, A, blank, D, E};
  int num_notes = (sizeof(ComeOnLetsGoNotes) / sizeof(ComeOnLetsGoNotes[0]));
  for (int i = 0; i < num_notes; i++) {
    playNoteAndCheck(ComeOnLetsGoNotes[i]);
    if (restartSong) {
      return;
    }
  }
}

void LaBamba() {
  tempo = 1644;
  restartSong = false;
  
  int laBamba[] = {now_playing, la_bamba, strumming, blank};

  for(int i = 0; i < 4; i++) {
    playNoteAndCheck(laBamba[i]);
    if(restartSong) return;
  }

  tempo = 508; // Adjusted for strumming pattern demo
  
  // Demonstrate strumming pattern
  Serial.println("La Bamba Strumming Pattern:");
  Serial.println("Down Up Down Down Up Up Down Up");
  
  int laBambaStrumming[] = {down, blank, down, blank, down, blank, down, blank, down, blank, down, up, down, up, down};
  for(int i = 0; i < 15; i++) {
    playNoteAndCheck(laBambaStrumming[i]);
    if(restartSong) return;
  }
  
  tempo = 810;
  int LaBambaNotes[] = {blank, blank, C, F, G, C, F, G, C, F, G, C, F, G};
  int num_notes = (sizeof(LaBambaNotes) / sizeof(LaBambaNotes[0]));
  for (int i = 0; i < num_notes; i++) {
    if (LaBambaNotes[i] == F) {
      tempo = 405+203;
    } else if (LaBambaNotes[i] == G) {
      tempo = 1620 + 203;
    } else if (LaBambaNotes[i] == C) {
      tempo = 810;
    }

    playNoteAndCheck(LaBambaNotes[i]);
    if (restartSong) {
      return;
    }
  }
}

void setup() {
  mySerial.begin(9600);
  Serial.begin(115200);
  
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini not detected!");
    while (true);
  }
  Serial.println("DFPlayer Mini ready.");
  Serial.println(myDFPlayer.readFileCounts());
  
  myDFPlayer.volume(volume);

  pinMode(button1, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);
  pinMode(volUpButton, INPUT_PULLUP);
  pinMode(volDownButton, INPUT_PULLUP);
  pinMode(restartButton, INPUT_PULLUP);
  pinMode(tempoIncButton, INPUT_PULLUP);
  pinMode(tempoDecButton, INPUT_PULLUP);
}
 
void loop() {
  if (restartSong) {
    Serial.println("Successfully restarted song");
    myDFPlayer.play(songRestarting);
    delay(1000);
    myDFPlayer.play(blank);
    delay(1000);
    restartSong = false;           // Reset the boolean after restarting
    songList[currentSongIndex]();  // Restart the current song
  }

  if (digitalRead(button1) == LOW) {
    songList[0]();
  }
  
  if (digitalRead(nextButton) == LOW) {
    currentSongIndex = (currentSongIndex + 1) % numSongs;
    Serial.println("Successful song change");
    Serial.println(currentSongIndex);
    songList[currentSongIndex]();
    delay(200);
  }

  if ((digitalRead(volUpButton) == LOW) && volume < 30) {
    volume++;
    myDFPlayer.volume(volume);
    Serial.println("Volume Increased: " + String(volume));
  }

  
  if ((digitalRead(volDownButton) == LOW) && volume > 0) {
    volume--;
    myDFPlayer.volume(volume);
    Serial.println("Volume Decreased: " + String(volume));
  }

  if ((digitalRead(tempoIncButton) == LOW) && tempo > maxTempo) {
    tempo -= tempoStep;
    Serial.println("Tempo Increased (Delay Lowered), Delay = " + String(tempo));
  }

  if ((digitalRead(tempoDecButton) == LOW) && tempo < minTempo) {
    tempo += tempoStep;
    Serial.println("Tempo Decreased (Delay Increased), Delay = " + String(tempo));
  }

}