

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
  int hauteur;
  int largeur;
};
typedef struct image Image;

//  MATRICE LOGO YOUTUBE
const CRGB logo_youtube[6][7] = {   {CRGB(0,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(0,0,0)},
                                    {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0)},
                                    {CRGB(255,0,0),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,0,0)},
                                    {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,255,255),CRGB(255,0,0),CRGB(255,0,0)},
                                    {CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,255,255),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0)},
                                    {CRGB(0,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(255,0,0),CRGB(0,0,0)}  };
                            
Image img_YT = {6, 7};


//  =========================== PRIMITIVES UTILES ============================================

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

CRGB getRandomLedColor() {
  return CRGB(random(20, 255), random(20, 255), random(20, 255));        
}

void fill_random() {
  for(int i=0;i<NUM_LEDS;i++)
        leds[i] = getRandomLedColor();
}

void clear_screen() {
  for(int i=0;i<NUM_LEDS;i++)
        leds[i] = CRGB(0,0,0);
}

void animationBalayageRandom() {
  for(int y=0;y<HAUTEUR;y++) {
    for (int x=0;x<LARGEUR;x++) {
        leds[posPixel(x, y)] = getRandomLedColor();
        delay(100);
        FastLED.show();
    }
  }
  
}

void TranslateX(int e) {
  for(int y=0;y<HAUTEUR;y++) {
    Serial.println("--------------------------------"); Serial.println("");
      for (int x=0;x<LARGEUR;x++) { //pour chaque pixel
        
        if(x == LARGEUR-1) {
          Serial.println("Le pixel de coordonnées : "); Serial.print(LARGEUR+e); Serial.print(" ; "); Serial.print(y); Serial.print (" prend la valeur du pixel "); Serial.print(0); Serial.print(" ; "); Serial.print(y);
          leds[posPixel(x, y)] = leds[posPixel(x-LARGEUR-1, y)];
        }else {
          leds[posPixel(x, y)] = leds[posPixel(x+1, y)];
        }
          
          
      }
    }
}

void scrollLeft() {
  int nb_scroll = 300;
  int delay_2_scroll = 200;
  
  for(int i=0; i<nb_scroll;i++) {
    TranslateX(-1);
    
    FastLED.show();
    delay(delay_2_scroll);
  }
}

void appliquer_logo_YT(Point origine) {
  int t_x = 6, t_y = 7;     //  TAILLE DE L'IMAGE (LARGEUR /HAUTEUR)    
  for(int x=0; x<t_x;x++) {
    for(int y=0; y<t_y;y++) {
      SetPixelColor({x+origine.x, y+origine.y}, logo_youtube[x][y]);
      //leds[posPixel(x+origine.x, y+origine.y)] = logo_youtube[x][y];
      //Serial.print("x="); Serial.print(x); Serial.print(" - y="); Serial.print(y); Serial.print(" - i = "); Serial.print(posPixel(x, y)); Serial.print(" --- logo= "); Serial.println(logo_youtube[x][y]); 
    }
  }  
}



//  =========================== INITIALISATION ECRAN ============================================
void screenSystem_Setup() {
  Serial.print("Initialisation ScreenSystem...........");
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(LUMINOSITE);


  

  //scrollLeft();
  /*
  for(int y=0; y<HAUTEUR; y++) {
    for(int x=0; x<LARGEUR;x++) { 
      Serial.print("x="); Serial.print(x); Serial.print(" - y="); Serial.print(y); Serial.print(" - i = "); Serial.println(posPixel(x, y)); 
      leds[posPixel(x, y)] = CRGB(255,0,0);   
      FastLED.show();
      delay(50);
    }
  }
  return;
  */
  for(int a=-6;a<=LARGEUR;a++) {
    clear_screen();
    appliquer_logo_YT({a,0});
    FastLED.show();
    delay(250);
  }
  Serial.print("[DONE]");
  Serial.println();
}




void displayRandomPixelScreen() {
  for(int y=0;y<HAUTEUR;y++) {
    for (int x=0;x<LARGEUR;x++) {
        leds[posPixel(x, y)] = getRandomLedColor();        
    }
  }
  FastLED.show();
}
