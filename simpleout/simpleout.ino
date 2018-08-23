//Simple Audio In
//by Amanda Ghassaei
//http://www.instructables.com/id/Arduino-Audio-Input/
//Sept 2012

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

int incomingAudio;
void setup(){
}

void loop(){
  incomingAudio = analogRead(A0);
  digitalWrite(A2, incomingAudio);//read input from A0
  //do stuff with the variable "incomingAudio"
}
