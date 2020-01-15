

#define LED_PIN     4       //  PIN I2C (PIN D4 pour carte D1R1 et PIN D5 pour les cartes ARDUINO MEGA 2560)
#define HAUTEUR     8       //  NBRE DE LEDS SUR L'AXE Y
#define LARGEUR     32      //  NBRE DE LEDS SUR L'AXE X
#define LUMINOSITE  1       //  LUMINOSITE DES LEDS (entre 1 et  255) (avec 60mA/LED i.e. (20mA *3 : R-G-B) * 8*32 = 15 Ampères !) -- NE PAS DEPASSER 5 / 255 DE LUMINOSITE

const int NUM_LEDS = HAUTEUR*LARGEUR;
CRGB leds[NUM_LEDS];

struct point {
  int x;
  int y;
};
typedef struct point Point;

struct image {
  int largeur;
  int hauteur;
  const CRGB pixel[8][6];
};
typedef struct image Image;

//  MATRICE LOGO YOUTUBE                                   
Image img_YT = {6, 8, {   
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0)},
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,255,255),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0)},
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,0,0),CRGB(255,0,0)},
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,0,0)},
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,0,0),CRGB(255,0,0)},
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,255,255),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0)},
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0)},
                          {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0)}
                        }};
                        
//  MATRICE LOGO FACEBOOK
Image img_FB = {6, 8, {   
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)}
                        }};

//  MATRICE LOGO INSTA
Image img_INSTA = {6, 8, {   // bug !!! Lorsque R/G/B < 100 couleur invisible ! Verifier intensité nécéssaire et augmenter BRIGHTNESS !
                          {CRGB(74,41,236),CRGB(91,38,232),CRGB(100,100,231),CRGB(118,100,224),CRGB(133,80,212),CRGB(143,80,226)},
                          {CRGB(143,27,186),CRGB(194,103,178),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(255,255,255),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)},
                          {CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178),CRGB(66,103,178)}
                        }};


const int digits[10][8][4] =       {
                                    {   
                                    {1,1,1,1},    //0
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,1,1,1}
                                  },  
                                  {   
                                    {0,0,0,1},    //1
                                    {0,0,1,1},
                                    {0,1,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1}
                                  },
                                  {   
                                    {1,1,1,1},    //2
                                    {1,0,0,1},
                                    {0,0,0,1},
                                    {1,1,1,1},
                                    {1,0,0,0},
                                    {1,0,0,0},
                                    {1,0,0,0},
                                    {1,1,1,1}
                                  },
                                  {   
                                    {1,1,1,1},    //3
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {1,1,1,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {1,1,1,1}
                                  },
                                  {   
                                    {1,0,0,1},    //4
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,1,1,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1}
                                  },
                                  {   
                                    {1,1,1,1},    //5
                                    {1,0,0,0},
                                    {1,0,0,0},
                                    {1,1,1,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {1,1,1,1}
                                  }, 
                                  {   
                                    {1,1,1,1},    //6
                                    {1,0,0,0},
                                    {1,0,0,0},
                                    {1,1,1,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,1,1,1}
                                  },
                                  {   
                                    {1,1,1,1},    //7
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {0,0,1,0},
                                    {0,0,1,0},
                                    {0,1,0,0},
                                    {0,1,0,0},
                                    {1,0,0,0}
                                  },
                                  {   
                                    {1,1,1,1},    //8
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,1,1,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,1,1,1}
                                  },
                                  {   
                                    {1,1,1,1},    //9
                                    {1,0,0,1},
                                    {1,0,0,1},
                                    {1,1,1,1},
                                    {0,0,0,1},
                                    {0,0,0,1},
                                    {1,0,0,1},
                                    {1,1,1,1}
                                  },
                                };

//  =========================== PRIMITIVES UTILES ============================================

int getNbrInRange(int n, int min, int max) {
  if(n<min)
    n=min;
  if(n>max)
    n=max;
  return (int)n;
}

//  Pour un pixel de coordonnée (x,y), retourne son indice dans le tableau
int posPixel(int x, int y) {
  if(x%2==0)  //  Parcours vertical inferieur
    return (x*HAUTEUR+y);
  else  // verticalsup
    return (x*HAUTEUR+(HAUTEUR-y-1));
}

void SetPixelColor(Point pixel, CRGB color) {
  //  Aucun affichage si pixel en dehors de l'intervalle de l'écran (8x32)
  if(pixel.x<0 || pixel.y<0 || (pixel.x)-1>LARGEUR || (pixel.y)-1>HAUTEUR) return;
  leds[posPixel(pixel.x, pixel.y)] = color; //update du CRGB de la matrice
}

void SetBackgroundColor(CRGB bgcolor) {
  fill_solid( leds, NUM_LEDS, bgcolor);
}

CRGB getRandomLedColor() {
  return CRGB(random(20, 255), random(20, 255), random(20, 255));        
}

void fill_random() {
  for(int i=0;i<NUM_LEDS;i++)
        leds[i] = getRandomLedColor();
}

void clear_screen() {
  fill_solid( leds, NUM_LEDS, CRGB(0,0,0));
}

void AppliquerImage(Image img, Point pos) {
  //Check point origine dans l'intervalle
  pos.x = getNbrInRange(pos.x, 0, LARGEUR-1);
  pos.y = getNbrInRange(pos.y, 0, HAUTEUR-1);

  //Application du logo à la matrice de LEDS
  for(int y=0; y<img.hauteur;y++) {
    for(int x=0; x<img.largeur;x++) {
      SetPixelColor({x+pos.x, y+pos.y}, img.pixel[y][x]);
    }
  }  
}

//  Afficher un nombre (matrice de taille 4x8), à une position donnée, une couleur donnée.
void fill_digit(int n, Point pos, CRGB fontColor) {
  n = getNbrInRange(n, 0, 9);
  
  int largeur_digit = 4, hauteur_digit = 8; 
  
  for(int y=0; y<hauteur_digit;y++) {
    for(int x=0; x<largeur_digit;x++) {
      if(digits[n][y][x]>0)
        SetPixelColor({x+pos.x, y+pos.y}, fontColor);
      /*else
        SetPixelColor({x+pos.x, y+pos.y}, CRGB(0,0,0));*/
    }
  }  
}

void SetNumberToDisplay(int n) {
  n = getNbrInRange(n, 0, 99999);
  int placement_digits[5] = {7, 12, 18, 23, 28};
  int padding = 0;
  if(n<=9)
    padding = 4;
  else if(n<=99)
    padding = 3;
  else if(n<=999)
    padding = 2;
  else if(n<=9999)
    padding = 1;

  for(int i=padding;i<5;i++) {
    fill_digit((int)( String(String(n, DEC).charAt(i-padding)).toInt()  ), {placement_digits[i],0}, CRGB(0,0,255));
  }

}

//  =========================== INITIALISATION ECRAN ============================================
void screenSystem_Setup() {
  Serial.print("Initialisation ScreenSystem...........");
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(LUMINOSITE);
  clear_screen();
  SetPixelColor({0,0}, CRGB(255,255,0));
  FastLED.show();
  Serial.print("[DONE]");
  Serial.println();
} // !!! AUCUN EANIMATION DANS CETTE FONCTION POUR NE PAS FAIRE ATTENDRE ESP8266, SE MET EN ERREUR EN CAS DE TIMEOUT / DELAY




void displayRandomPixelScreen() {
  for(int y=0;y<HAUTEUR;y++) {
    for (int x=0;x<LARGEUR;x++) {
        leds[posPixel(x, y)] = getRandomLedColor();        
    }
  }
  FastLED.show();
}
