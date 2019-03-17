#include <TFT.h>
#include <SPI.h>


#define TFT_CS     10
#define TFT_RST    9  
#define TFT_DC     8

#define TFT_SCLK 52   
#define TFT_MOSI 51   

TFT screen=TFT(TFT_CS,TFT_DC,TFT_RST);//mise en place de l'écran

void setup() {
  screen.begin();//allume l'écran
  screen.background(0,0,0);//met le fond en noir
  
}

void loop() {
  screen.stroke(255,0,0);//définir la couleur du tracet en bleu
  for(int i=2;i<screen.width();i=i+2){
    for(int j=2;j<screen.height();j=j+2)
    screen.rect(i,j,2,2);
  }
  screen.line(10,100,100,100);//dessine un trait du point (10,100) au point (100,100)


}
