/*
Nicholas Bequette
03/17/23
Clock display
*/

#include <iostream>
#include <cstring>
using namespace std;

//Declare some global variables 
unsigned int hour;
unsigned int minute;
unsigned int second;

//Method that formats input as two digits
string twoDigitString(unsigned int n) {
    //Set boundaries for adding a leading 0. Input cannot be negative so set between 0 ansd 9.
    if (n >= 0 && n < 10) {
        //Return a leading 0 plus the initial int converted to a string
        return "0" + to_string(n);
    }
    else if (n >= 10 && n <= 59) {
        //else return initial int as a string as is
        return to_string(n);
    }
    else {
        return 0;
    }
  
}


//Method that repeats * to format output
string nCharString(size_t n, char c = '*') {
    //Declare empty string which will store our result
    string result;
    
    //Iterates over the size of n and appends c to our result n amount of times
    for (size_t i = 0; i < n; ++i) {
        result += c;
    }
    //result is returned
    return result;
}


//Method that formats input in hh:mm:ss form
string formatTime24(int h, int m, int s) {
  hour = h;
  minute = m;
  second = s;
    //return time in hh:mm:ss form by calling twoDigitString method and using user input to output the time
  return twoDigitString(hour) + ":" + twoDigitString(minute) + ":" + twoDigitString(second);
}


//Method that formats input as a 12 hour clock
string formatTime12(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
    //Declare empty string to store result
    string twelveHourTime;

    //var hour to convert to 12 hours using mod operator
    unsigned int hour = h % 12;
    
    //if statement to account for an input of 0
    if (hour == 0) {
        hour = 12;
    }

    //Concatenate the time to the empty string and add a space at the end 
    twelveHourTime += twoDigitString(hour) + ":" + twoDigitString(minute) + ":" + twoDigitString(second) + " ";
    /* Looked up a shorthand command for if-else statement via https://www.w3schools.com/cpp/cpp_conditions_shorthand.asp
    If expression is true, AM is appended, otherwise PM is appended to the string */
    twelveHourTime += (h < 12) ? "A M" : "P M";
    //String is returned
    return twelveHourTime;
}


//Method that prints menu 
void printMenu(char * strings[], unsigned int numStrings, unsigned char width) {
    
    // first print width *'s followed by an endl
    cout << nCharString(width, '*') << endl;

    //for loop that iterates over the array of strings
    for (unsigned int i = 0; i < numStrings; ++i) {
        //calculate number of spaces needed
        unsigned int numSpaces = width - strlen(strings[i]) - 7;
        //print necessary info to the screen
        cout << "* " << i + 1 << " - " << strings[i] << nCharString(numSpaces, ' ') << "*" << endl;
        //if it is not the last line, we end each line
        if (i != numStrings-1) {
            cout << endl;
        }
    }
    //bottom border
    cout << nCharString(width, '*') << endl;
}


//Method to make sure user's choice is valid and returns their choice
unsigned int getMenuChoice(unsigned int maxChoice) {
    //Declare a userChoice input
    unsigned int userChoice = 0;
    //Set bool to false
    bool validChoice = false;
  
  //While not false, make user enter their choice
    while (!validChoice) {
        cout << "Please enter your choice (1-" << maxChoice << "): ";
        cin >> userChoice;
    
    //If user choice is in valid boundaries, bool is set to true
    if (userChoice >= 1 && userChoice <= maxChoice) {
      validChoice = true;
    }
  }
  //Users choice is returned
  return userChoice;
}


//Method to display clocks concurrently
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
    cout << nCharString(27,'*') << "   " << nCharString(27,'*') << endl;
    cout << "*      12-HOUR CLOCK      *" << "   " << "*      24-HOUR CLOCK      *" << endl;
    cout << endl;
    cout << "*      " << formatTime12(h, m, s) << "       *" << "   " << "*        " << formatTime24(h, m, s) << "         *" << endl;
    cout << nCharString(27,'*') << "   " << nCharString(27,'*') << endl;
}

//Methods that set the hour, minute, and second based on the time input
int setHour(int h) {
  if (h >= 0 && h <= 23) {
    hour = h;
    return 0;
  }
  else {
    return -1;
  }
}

int setMinute(int  m) {
  if (m >= 0 && m <= 59) {
    minute = m;
    return 0;
  }
  else {
    return -1;
  }
}

int setSecond(int s) {
  if (s >= 0 && s <= 59) {
    second = s;
    return 0;
  }
  else {
    return -1;
  }
}


//Methods that get the hour, minute, and second so that it can be manipulated
unsigned int getHour() {
  return hour;
}

unsigned int getMinute() {
  return minute;
}

unsigned int getSecond() {
    return second;
}


//Method that allows user to add an hour to the time
void addOneHour() {
    //if hours is less than 23, add 1 hour to time
    if (getHour() >= 0 && getHour() < 23) { 
        setHour(getHour() + 1); 
    } 
    // if hours is 23 set hours to 0
    else if (getHour() == 23) { 
        setHour(0); 
    }
}


//Method that allows user to add a minute to the time
void addOneMinute() {
    // if minutes is less than 59 then add 1 minute to time
    if (getMinute() >= 0 && getMinute() < 59) { 
        setMinute(getMinute() + 1);
    } 
    //else if minutes is 59 then set minutes to zero and add 1 hour
    else if (getMinute() == 59) { 
        setMinute(0); 
        addOneHour(); 
    }
}


//Method that allows user to add a second to the time
void addOneSecond() {
    // if seconds is less than 59 add 1 second
    if (getSecond() >= 0 && getSecond() < 59) { 
        setSecond(getSecond() + 1); 
    } 
    //else if seconds is 59 set seconds to 0 and add a minute
    else if (getSecond() == 59) { 
        setSecond(0); 
        addOneMinute();
    } 
}





//Main method that handles what the user would like to do
int main() {
  unsigned int choice = 0;
  // Declare integers and take user input for the current time
  int hour;
  int minute;
  int second;
  cout << "Please type the time as HH MM SS" << endl;
  cin >> hour >> minute >> second;
  
  //While choice is not 4 each of the fuctions will be called depending on user input
    while (choice != 4) { 
      displayClocks(hour, minute, second);
      cout << "***************************\n";
      
      cout << "* 1 - Add One Hour *\n";

      cout << "* 2 - Add One Minute *\n";

      cout << "* 3 - Add One Second *\n";

      cout << "* 4 - Exit Program *\n";

      cout << "***************************\n";
       //set choice to getMenuChoice method
      choice = getMenuChoice(4);
      
        switch (choice) { 
            case 1: 
                addOneHour();
              //overwrite hour after adding hour
                hour = getHour();
                break; 
            case 2: 
                addOneMinute();
              //overwrite minute after adding minute
                minute = getMinute();
                break; 
            case 3: 
                addOneSecond();
              //overwrite second after adding second
                second = getSecond();
                break; 
            case 4:
                break;
        }
    } 

  return 0;
} 