#include <LGSM.h>

String initializeBuffer;
String message;
String recipient = "Please enter the ID of the person you want to send SMS to:";
String messageConfirm = "What do you want to send?";
String confirmSend = "Do you want to send the SMS (Yes or No)?";
String confirmReply;

const int numOfContacts = 3;
const int numOfColumns = 3; 
const char* phoneNum[3][3] = {
  {"1","Mahmood"  , "0504745888"},
  {"2","Ali"      , "0501444929"},
  {"3","Abdulla" , "0502780340"}
};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  while (Serial.available() == 0) {}
  initializeBuffer = Serial.readString();

  Serial.println("Starting Send SMS!");
  while (!LSMS.ready())
  {
    delay(1000);
  }
  Serial.println("Sim initialized");
  
  displayContacts();

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(recipient);
  while (Serial.available() == 0) {}
  int contactID = Serial.parseInt();
      
  LSMS.beginSMS(phoneNum[contactID - 1][2]);

  Serial.println(phoneNum[contactID - 1][2]);
  
  Serial.println(messageConfirm);
  while (Serial.available() == 0) {}
  message = Serial.readString();

  LSMS.print(message);

  Serial.println(confirmSend);
  while (Serial.available() == 0) {}
  confirmReply = Serial.readString();

  if (confirmReply == "Yes") {
    if (LSMS.endSMS())
    {
      Serial.println("SMS is sent");
    }
    else
    {
      Serial.println("SMS is not sent");
    }
  }
  else {
    Serial.println("SMS sending cancelled by user");
  }
  Serial.println("");
}

void displayContacts() {
  
  Serial.println("ID\tName\tNumber");
  Serial.println("----------------------------------------");
  
  // Displaying the Contacts for the user
  for (int i = 0; i < numOfContacts; i++) {
    
    for (int j = 0; j < numOfColumns; j++) {
    
      Serial.print(phoneNum[i][j]);
      Serial.print("\t");
    
    };
   
   Serial.println("");
        
  };  
}
