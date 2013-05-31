/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */
 
 // el import de la libreria
import oscP5.*;
import netP5.*;

// El motor OSC
OscP5 oscP5;
// el objeto para envir datos
NetAddress gamuzaLocation;

// receiving variables
float alpha = 0.0;
float radius = 0.0;

void setup() {
  size(400,400);
  // start oscP5, listening for incoming messages at port 8000
  // here we will receive data from GAmuza
  oscP5 = new OscP5(this,9666);
  
  // here we will send to GAmuza, it means GAmuza will receive at port 9000
  gamuzaLocation = new NetAddress("127.0.0.1",8997);
}


void draw() {
  background(0);  
  
  sendCustomOSC();
  
  fill(255,alpha);
  ellipse(width/2,height/2,radius,radius);
}

// send the mouse position to GAmuza while the mouse ios moving
void sendCustomOSC() {
  // creamos mensajes osc con etiqueta "/mousePosX" y "/mousePosY"
  OscMessage mousePosX = new OscMessage("/mouseX");
  OscMessage mousePosY = new OscMessage("/mouseY");
  
  // añadimos datos al mensaje
  mousePosX.add(mouseX);
  mousePosY.add(mouseY);

  // send the messages
  oscP5.send(mousePosX, gamuzaLocation);
  oscP5.send(mousePosY, gamuzaLocation);
}


// esta función se encarga de estar a la escuche de cualquier mensaje en entrada
void oscEvent(OscMessage theOscMessage) {
  // filtrado de etiquetas
  if(theOscMessage.checkAddrPattern("/alpha")==true) {
    // filtrado de tipo de dotos (int float o string, i - f - s)
    // para comunicar con GAmuza hay que usar datos de tipo String
    if(theOscMessage.checkTypetag("f")) {
      alpha = theOscMessage.get(0).floatValue();
      return;
    }
  }else if(theOscMessage.checkAddrPattern("/diameter")==true){
    if(theOscMessage.checkTypetag("f")) {
      radius = theOscMessage.get(0).floatValue();
      return;
    }
  }
}
