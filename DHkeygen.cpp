#include "Arduino.h"
#include "Utility/Entropy.h"
#include "DHkeygen.h"

unsigned long DHkeygen::calc_y(unsigned long b, unsigned long e, unsigned long m) //B.E.M. function - root function for modular arithmetics of DH Algorithm
{ 
  int i;
  unsigned long r = 1;
  for ( i=0; i<e; i++)
  { 
    r = r * b % m; 
  } 
  return r; 
}

unsigned long DHkeygen::randum() // returns a random number based on entropy.//for DH algo; dont call explicitly
{
  Entropy.Initialize();

  random_int = Entropy.random(WDT_RETURN_WORD);
  return random_int;  
}

void DHkeygen::randgen() //generate secret values
{
  _xa[0]=randum();
  _xa[1]=randum();
}

unsigned long DHkeygen::calculation_y(unsigned long x) // DH algorithm public keying routine
{
  return calc_y(_a, x ,_p);
}

void DHkeygen::publickey_calc() //container to call calculation_y twice to calculate own public key
{
  // calculation of own public values  
  _ya[0]=calculation_y(_xa[0]);

  _ya[1]=calculation_y(_xa[1]);
}

double DHkeygen::genpart(double y, unsigned long x);//was calc_k - called to generate key whenever public or private values vary
{
  return /*_t_k =*/ calc_y(y,x,_prime);
  //return _t_k; 
}

void DHkeygen::genkey(void* data) //container - generates common secret key by calling genpart twice
{
  memcpy(_yb,data,16 /* 2*sizeof(double) */ ); //REPLACE SIZEOF DATA WITH KEYLENGTH 128BIT
  _k[0]=genpart( _yb[0], _xa[0] );
  _k[0]=genpart( _yb[1], _xa[1] );
}

void DHkeygen::DH_Pub();// calling this function calculates the node's own public value
{
  //serial.print("Diffie Hellman Key exhange. Creating the public value\n");
  
  // generates the secret numbers that represent our private key
  randgen();
  publickey_calc();
  
}

void DHkeygen::formatkey(uint8_t *key)//was set_key - converts the key to the format required by the AES algorithm. Called automatically by the genkey function
{
  memcpy(key,_k,sizeof(_k));
}

//CLASS CONSTRUCTOR
DHkeygen::DHkeygen()
{
//needed?
}


