/*
 *  YT Counter Project By Cédric MILLET
 *  Tous droits réservés
 *  Type de carte employée : Wemos D1 R1
 *  Telecharger la librairie ArduinoJson en version 5.X 
 *  Config serveur web : pas de SSL, pas de rewriting URI, pas de redirection
 *  Config ScreenLEd : le PIN I2C pour les leds WS2812B est D4
 * */

//  Librairies Communication Réseau
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>    //  Pour emettre des requetes GET
ESP8266WebServer server(80);      //  Serveur WEB sur port 80

//  Librairies Diverses
#include <ArduinoJson.h>

//  Librairies matrice de LEDS adressables en I2C
#include <FastLED.h>

#import "index.h"                 //  Contient le code HTML retourné par le serveur WEB
#import "ScreenSystem_WS2812B.h"  //  Contient les fonctions de manipulation de l'écran LED
#import "SoundSystem.h"           //  Contient les fonctions de manipulation du BUZZER

//#define WEB_API_ENDPOINT  "http://ytproject.cedricmillet.fr/api/index.php?UID=782D-A2DC8-A7E1-A79D1"
#define WEB_API_ENDPOINT  "http://192.168.0.43:8082/api/example"
#define SOCIAL_DATA_REFRESH_FREQUENCY   120 //en seconde


int timer = 0;
bool isInitialisationReady = false;

struct socialdata {
  int nb_subscribers;
  int timestamp_lastupdate;
};
typedef struct socialdata SocialData;

SocialData s_youtube = {-1, -1};
SocialData s_instagram = {-1, -1};
SocialData s_facebook = {-1, -1};


void initialisation() {
  //  Lancement du serveur Web
  setupWifiServer();
  //  Lancement de l'écran LED
  screenSystem_Setup();
  //  Connexion au réseau WIFI
  setupWifiClient("FREEBOX_MILLET", "Mkanad45-1203");
  //  Screen
  SetBackgroundColor(CRGB(255,255,255));
  AppliquerImage(img_YT, {0,0});
  SetNumberToDisplay( 0 );
  FastLED.show();
  //  Emit Sound
  SetupSoundSystem();
  
}



void setup() {
  isInitialisationReady = false;
  
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("\n---------------------------------");
  Serial.println("\tLANCEMENT");
  Serial.println("---------------------------------");

  initialisation();

  delay(500);
  Serial.println("------------------------------------------");
  Serial.println("\tINITIALISATION TERMINEE");
  Serial.println("------------------------------------------");  

  
  //  Premiere requete avant les premieres iteration de la loop()
  //updateSocialDatasFromAPI();
  isInitialisationReady = true;

  updateSocialDatasFromAPI();
}



void updateSocialDatasFromAPI()
{
  if(!isWifiStatusConnected()) {
    Serial.println("Impossible d'emettre une requete HTTP avant d'etre connecté à un réseau Internet.");
    return;
  }
  Serial.print("updateSocialDatasFromAPI()_______");
  HTTPClient httpClient;
  String reponse = "";
  httpClient.begin(WEB_API_ENDPOINT);  
  //  Envoie de la requete
  int httpCode = httpClient.GET();
  if (httpCode > 0)
    reponse = httpClient.getString();   //response payload
  httpClient.end();   //Close connection
  //  Traitement de la réponse
  if(!reponse.isEmpty() && reponse.length() > 0) {
    //  Conversion en JSON
    DynamicJsonBuffer jsonBuffer;
    JsonObject& jsonSocialData = jsonBuffer.parseObject(reponse);

    //  Mise a jour des variables globales
    s_youtube.nb_subscribers = (int)jsonSocialData[String("youtube")];
    s_instagram.nb_subscribers = (int)jsonSocialData[String("instagram")];
    s_facebook.nb_subscribers = (int)jsonSocialData[String("facebook")];

    Serial.println("[OK]");
  } else { 
    Serial.println("[HTTP RESPONSE ERROR] !");
    Serial.println(reponse);
  }

  debugData();
  update_screen();
}

void debugData() {
  Serial.println("debugData()\n");
  
  Serial.println("=== YOUTUBE ===");
  Serial.print("Subscribers : ");
  Serial.println(s_youtube.nb_subscribers);
  Serial.println("=== INSTAGRAM ===");
  Serial.print("Subscribers : ");
  Serial.println(s_instagram.nb_subscribers);
  Serial.println("=== FACEBOOK ===");
  Serial.print("Subscribers : ");
  Serial.println(s_facebook.nb_subscribers);
}


void update_screen() {
  SetBackgroundColor(CRGB(0,0,0));
  AppliquerImage(img_YT, {0,0});
  Serial.println("Affichage YT, nbAbonnes = "); Serial.print((int)s_youtube.nb_subscribers);
  SetNumberToDisplay( (int)s_youtube.nb_subscribers );
  FastLED.show();
}

void loop() {
  
  //  Traiter les quetes HTTP entrantes
  server.handleClient();

  
  if(!isWifiStatusConnected() || !isInitialisationReady) return;

  

  

  //  Mise a jour des données sociales
  if(timer >= SOCIAL_DATA_REFRESH_FREQUENCY*10) {
    timer = 0;
    updateSocialDatasFromAPI();
  }
  timer ++;
  delay(100);
  
}



void setupWifiClient(const char* ssidclient, const char* passclient) {
  Serial.println();
  WiFi.begin(ssidclient, passclient);
  Serial.print("Connexion au réseau WIFI : ");
  Serial.print(ssidclient);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("[CONNECTED]");
  Serial.println("");
  Serial.print("Serveur Web disponible sur le réseau à l'adresse : ");
  Serial.println(WiFi.localIP()); //Adresse IPv4 attribuée par le DHCP
  WiFi.printDiag(Serial);
  Serial.println("--- CONNEXION AU RESEAU WIFI REUSSIE ---");
}


void setupWifiServer() {
  Serial.print("Preparation du serveur web............");
  server.on("/", [](){
    Serial.println("[WEB_SERVER] - Client sur la route /");
    String html = MAIN_page; // Recupération du contenu HTML depuis le fichier index.h
    server.send(200, "text/html", html);
    Serial.println("[WEB_SERVER] - Client sur la route /");
    //test
    fill_solid( leds, NUM_LEDS, getRandomLedColor());
    FastLED.show();
  });

  // on démarre le serveur web 
  server.begin();
  
  Serial.println("[DONE]");
}

bool isWifiStatusConnected() {
  return (bool)(WiFi.status() == WL_CONNECTED);
}
