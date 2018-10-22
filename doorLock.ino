

#include <Keypad.h> //Includes the keypad library
#define Password_Lenght 4 // Define the password length (It's your password +1 because of the NULL value)


const int lockDelay = 3000; // The amount of time in milliseconds you want the lock to stay unlocked
int greenLed = 13; // Used for debugging Green
int redLed = 12; // Used for debugging Red
int buttonState = 0; // The state of the lock.(1 = Locked, 0 = Unlocked)
const int switchPin = 11; // The Switch is connected to pin 5
char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123"; // Master password
byte data_count = 0, master_count = 0; // Byte that sotres the
char customKey; // char that stores the key you input

const byte ROWS = 4; // Define the number of Rows
const byte COLS = 4; // Define the number of Cols
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {
  2,3,4,5}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {
  10,9,8,7}; // connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad 

void setup()
{
  pinMode(greenLed, OUTPUT); // Used for debugging
  pinMode(redLed, OUTPUT); // Used for debugging
  pinMode(switchPin, INPUT); // Sets the pin mode for the button
}

// The clearData() function clears the data count array 
void clearData()
{
  while(data_count !=0)
  {   // This can be used for any array size, 
    Data[data_count--] = 0; // clear array for new data
  }
  return;
}

// The Close() function locks the door
void Close()
{
  digitalWrite(redLed, HIGH); // Used for debugging
  digitalWrite(greenLed, LOW); // Used for debugging
}

// The compare() function compares the Data array to the Master array
void compare() // Compares the input with the master, if true open, else clear the data char, and make sure the lock is closed
{
  if(strcmp(Data, Master) == 0){ // If Data char is == Master char (MUST BE ZERO TO COMPARE)
    digitalWrite(greenLed, HIGH); // Used for debugging
    digitalWrite(redLed, LOW); // Used for debugging
    delay(lockDelay); // The amount of time in milliseconds you want the lock to stay unlocked
    Close(); // Calls the Close() function 
    clearData(); // Calls the clearData() function 
}
  else
  {
    digitalWrite(redLed, HIGH); // Used for debugging
    digitalWrite(greenLed, LOW); // Used for debugging
    clearData(); // Calls the clearData() function 
    Close(); // Calls the Close() function 
  }
}


void loop()
{
  if (digitalRead(switchPin) == HIGH) // If statement check to see if the button has been pushed
  {
    buttonState = 1; // Sets the button state to 1 i.e unlocked
    digitalWrite(greenLed, HIGH); // Used for debugging
    digitalWrite(redLed, LOW); // Used for debugging
    delay(lockDelay); // The amount of time in milliseconds you want the lock to stay unlocked
    buttonState = 0; // Sets the button state back to 0 i.e locked
  } else
  {
    Close(); // Calls the Close() function 
  }
  customKey = customKeypad.getKey();
  if (customKey != NO_KEY) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
    
  }

  if(data_count == Password_Lenght -1) // if the array index is equal to the number of expected chars, compare data to master
  {
    compare(); // Calls the compare() function 
  }
}
