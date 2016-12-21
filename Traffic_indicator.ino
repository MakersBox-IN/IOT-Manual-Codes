/*
 
Traffic Indicator

Project that helps you calculate the ETA (estimated time arrival) between to fixed points (origins,destination) given to the Http request 
returing back the time according to the traffic conditions.

Returned ETA is calculated according to the GMT timing so make sure to check your local timing refered by GMT.
*/

#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_SHIELD
#define INCLUDE_TERMINAL_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>
/* Create an Http request with discatncematrix api url. */
/* It's important to be created here as a global object. */
HttpRequest request("https://maps.googleapis.com/maps/api/distancematrix/json?origins=30.0678184,31.3313650&destinations=30.0659340,31.4604450&departure_time=now&key=YOUR_API_KEY");

/* Set a RGB LED on pin 11,10 and 9. */
int red = 11;
int green = 10;
int blue = 9;

void setup() 
{
  /* Start communication. */
  OneSheeld.begin();
  /* Subscribe to success callback for the request. */
  request.setOnSuccess(&onSuccess);
  /* Subscribe to json value replies. */
  request.getResponse().setOnJsonResponse(&onJsonReply);
  /* Subscribe to response errors. */
  request.getResponse().setOnError(&onResponseError);
  /* Subscribe to Internet errors. */
  Internet.setOnError(&onInternetError);  
  /* LED pin modes OUTPUT.*/
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(blue, OUTPUT); 
}

void loop()
{
  /* Perform the request get action. */
  Internet.performGet(request);
  /* Wait for 5 minutes. */
  OneSheeld.delay(60000*5); 
}

void onSuccess(HttpResponse & response)
{
  /* Using the response to query the Json chain till the required value. */
  response["rows"][0]["elements"][0]["duration_in_traffic"]["value"].query();
}

void onJsonReply(JsonKeyChain & hell,char * output)
{
  /* Getting the value and transform it to integer to deal with. */
  int eta = atoi(output);
  int mins = eta/60;

  /* Checking the ETA "estimated time of arrival" to the destination. */
  if(mins>=30) 
  {
    redLightsOn();
  }
  else if(mins<30)
  {
    greenLightsOn();delay(1000);lightsOff();delay(1000);
    greenLightsOn();delay(1000);lightsOff();delay(1000);
    greenLightsOn();delay(1000);lightsOff();delay(1000);
    greenLightsOn();
  }
  /* Terminal line for debugging. */
  Terminal.println(eta/60);
}

void greenLightsOn()
{
  digitalWrite(red,LOW);digitalWrite(blue,LOW);digitalWrite(green,HIGH);
}

void redLightsOn()
{
  digitalWrite(red,HIGH);digitalWrite(blue,LOW);digitalWrite(green,LOW);
}

void lightsOff()
{
  digitalWrite(red,LOW);digitalWrite(blue,LOW);digitalWrite(green,LOW);
}

/* Error handling functions. */
void onResponseError(int errorNumber)
{
  /* Print out error Number.*/
  Terminal.print("Response error:");
  switch(errorNumber)
  {
    case INDEX_OUT_OF_BOUNDS: Terminal.println("INDEX_OUT_OF_BOUNDS");break;
    case RESPONSE_CAN_NOT_BE_FOUND: Terminal.println("RESPONSE_CAN_NOT_BE_FOUND");break;
    case HEADER_CAN_NOT_BE_FOUND: Terminal.println("HEADER_CAN_NOT_BE_FOUND");break;
    case NO_ENOUGH_BYTES: Terminal.println("NO_ENOUGH_BYTES");break;
    case REQUEST_HAS_NO_RESPONSE: Terminal.println("REQUEST_HAS_NO_RESPONSE");break;
    case SIZE_OF_REQUEST_CAN_NOT_BE_ZERO: Terminal.println("SIZE_OF_REQUEST_CAN_NOT_BE_ZERO");break;
    case UNSUPPORTED_HTTP_ENTITY: Terminal.println("UNSUPPORTED_HTTP_ENTITY");break;
    case JSON_KEYCHAIN_IS_WRONG: Terminal.println("JSON_KEYCHAIN_IS_WRONG");break;
  }
}

void onInternetError(int requestId, int errorNumber)
{
  /* Print out error Number.*/
  Terminal.print("Request id:");
  Terminal.println(requestId);
  Terminal.print("Internet error:");
  switch(errorNumber)
  {
    case REQUEST_CAN_NOT_BE_FOUND: Terminal.println("REQUEST_CAN_NOT_BE_FOUND");break;
    case NOT_CONNECTED_TO_NETWORK: Terminal.println("NOT_CONNECTED_TO_NETWORK");break;
    case URL_IS_NOT_FOUND: Terminal.println("URL_IS_NOT_FOUND");break;
    case ALREADY_EXECUTING_REQUEST: Terminal.println("ALREADY_EXECUTING_REQUEST");break;
    case URL_IS_WRONG: Terminal.println("URL_IS_WRONG");break;
  }
}

